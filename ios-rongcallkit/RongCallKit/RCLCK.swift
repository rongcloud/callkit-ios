//
//  RCLiveCommunicationKit.swift
//  RongCallKit
//
//  Created by RongCloud on 2025/8/20.
//  Copyright © 2025 Rong Cloud. All rights reserved.
//

import Foundation
import AVFoundation
import LiveCommunicationKit
#if canImport(RongCloudOpenSource)
import RongCloudOpenSource.RongIMKit
#else
import RongIMKit
#endif

let kCallNewSession = Notification.Name(rawValue: "RCCallNewSessionCreation Notification")

@objc public protocol RCLCKCenterDelegate: NSObjectProtocol {
    @objc optional func didPerformJoinAction() -> Bool
    @objc optional func didPerformMuteAction(_ isAudioMuted: Bool)
    @objc optional func didPerformEndAction()
    @objc optional func didLogLCK(_ log: String)
    @objc optional func didLocalizedString(_ key: String) -> String
}

@available(iOS 17.4, *)
@objc public class RCLCKCenter : NSObject {
    @objc public static let shareInstance = RCLCKCenter()
    @objc public weak var delegate: RCLCKCenterDelegate?
    
    fileprivate let conversationManager: ConversationManager
    fileprivate var conversationUUID: UUID?
    fileprivate var isPerformJoinAction = false
    fileprivate var hasJoined = false
    
    private override init() {
        let configuration = ConversationManager.Configuration(ringtoneName: "RongCallKit.bundle/voip/voip_call.caf",
                                                              iconTemplateImageData: nil,
                                                              maximumConversationGroups: 1,
                                                              maximumConversationsPerConversationGroup: 1,
                                                              includesConversationInRecents: true,
                                                              supportsVideo: true,
                                                              supportedHandleTypes: [Handle.Kind.generic])
        self.conversationManager = ConversationManager(configuration: configuration)
        super.init()
        self.conversationManager.delegate = self
        NotificationCenter.default.addObserver(self,
                                               selector: #selector(handleCreateNewSession(_:)),
                                               name: kCallNewSession,
                                               object: nil)
        NotificationCenter.default.addObserver(self,
                                               selector: #selector(appWillEnterForeground),
                                               name: UIApplication.willEnterForegroundNotification,
                                               object: nil)
    }
    
    deinit {
        self.conversationManager.invalidate()
        NotificationCenter.default.removeObserver(self)
    }
    
    @objc private func handleCreateNewSession(_ notification: Notification) {
        if isPerformJoinAction && !hasJoined {
            hasJoined = delegate?.didPerformJoinAction?() ?? false
        }
    }
    
    @objc private func appWillEnterForeground() {
        delegate?.didLogLCK?("appWillEnterForeground")
        if let conversation = currentConversation() {
            conversationManager.reportConversationEvent(.conversationEnded(Date(), .joinedElsewhere), for: conversation)
        }
    }
    
    private func currentConversation() -> Conversation? {
        guard let uuid = conversationUUID else {
            return nil
        }
        
        let calls = conversationManager.conversations
        if let index = calls.firstIndex(where: {$0.uuid == uuid}) {
            return calls[index]
        } else {
            return nil
        }
    }
    
    private func reset() {
        conversationUUID = nil
        isPerformJoinAction = false
        hasJoined = false
    }
    
    /// 将 callId 转换为有效的 UUID，如果 callId 不是有效的 UUID，则生成一个新的 UUID
    /// - Parameter callId: 原始 callId 字符串
    /// - Returns: 有效的 UUID 对象和是否是新生成的标识
    private func normalizeCallIdToUUID(_ callId: String) -> (uuid: UUID, isGenerated: Bool) {
        // 首先尝试直接解析为 UUID
        if let uuid = UUID(uuidString: callId) {
            return (uuid, false)
        }
        
        // 如果 callId 不是有效的 UUID，尝试从字符串生成稳定的 UUID
        // 使用 MD5 哈希确保相同 callId 总是生成相同的 UUID
        let normalizedCallId = callId.trimmingCharacters(in: .whitespacesAndNewlines)
        
        // 如果 callId 为空，直接生成新的 UUID
        if normalizedCallId.isEmpty {
            let newUUID = UUID()
            delegate?.didLogLCK?("callId is empty, generated new UUID: \(newUUID.uuidString)")
            return (newUUID, true)
        }
        
        // 使用 callId 的哈希值生成稳定的 UUID
        let uuidString = generateUUIDFromString(normalizedCallId)
        if let uuid = UUID(uuidString: uuidString) {
            delegate?.didLogLCK?("callId '\(callId)' is not a valid UUID, generated stable UUID: \(uuidString)")
            return (uuid, true)
        }
        
        // 如果仍然失败，生成一个完全随机的 UUID
        let fallbackUUID = UUID()
        delegate?.didLogLCK?("Failed to generate UUID from callId '\(callId)', using random UUID: \(fallbackUUID.uuidString)")
        return (fallbackUUID, true)
    }
    
    /// 从字符串生成稳定的 UUID（使用字符串哈希）
    /// - Parameter string: 输入字符串
    /// - Returns: UUID 格式的字符串
    private func generateUUIDFromString(_ string: String) -> String {
        // 使用简单的哈希算法生成稳定的 UUID
        // 使用多个哈希值组合确保唯一性
        var hash1: UInt64 = 0
        var hash2: UInt64 = 0
        
        // 计算字符串的哈希值
        for (index, char) in string.utf8.enumerated() {
            let value = UInt64(char)
            hash1 = hash1 &* 31 &+ value
            hash2 = hash2 &* 37 &+ UInt64(index) &* value
        }
        
        // 使用字符串长度和内容生成第三个哈希值
        let hash3 = UInt64(string.count) &* 17 &+ hash1 &* 7
        
        // 将哈希值转换为十六进制字符串
        let hex1 = String(format: "%016llx", hash1)
        let hex2 = String(format: "%016llx", hash2)
        let hex3 = String(format: "%016llx", hash3)
        
        // 组合哈希值并格式化为 UUID 格式 (8-4-4-4-12)
        let combinedHex = (hex1 + hex2 + hex3).prefix(32)
        let uuidString = String(format: "%@-%@-%@-%@-%@",
                               String(combinedHex.prefix(8)),
                               String(combinedHex.dropFirst(8).prefix(4)),
                               String(combinedHex.dropFirst(12).prefix(4)),
                               String(combinedHex.dropFirst(16).prefix(4)),
                               String(combinedHex.dropFirst(20).prefix(12)))
        return uuidString
    }
    
    @objc public func reportIncomingCall(_ callId: String, inviterId: String, userIdList: [String], isGroup: Bool, isVideo: Bool) {
        let state = UIApplication.shared.applicationState
        delegate?.didLogLCK?("reportIncomingCall callId: \(callId) inviterId: \(inviterId) appState: \(state)")
        if (callId.count == 0 ||
            state == .active ||
            conversationUUID != nil) {
            return
        }
        Task {
            do {
                let inviterText = isGroup ? delegate?.didLocalizedString?("VoIPCall_invite_group_call") : delegate?.didLocalizedString?("VoIPCall_invite_signal_call")
                let inviterName: String = RCIM.shared().getUserInfoCache(inviterId)?.name ?? inviterId
                let handle = Handle(type: .generic, value: inviterName + (inviterText ?? ""), displayName: inviterName + (inviterText ?? ""))
                var update = Conversation.Update(members: [handle])
                if isVideo {
                    update.capabilities = [.playingTones, .video]
                } else {
                    update.capabilities = [.playingTones]
                }
                // 使用容错方法将 callId 转换为有效的 UUID
                let (uuid, isGenerated) = normalizeCallIdToUUID(callId)
                if isGenerated {
                    delegate?.didLogLCK?("callId '\(callId)' was normalized to UUID: \(uuid.uuidString)")
                }
                try await conversationManager.reportNewIncomingConversation(uuid: uuid, update: update)
                // 变量的设置在LiveCommunication展示之后，保证后续操作的状态正确
                self.conversationUUID = uuid
            } catch  {
                delegate?.didLogLCK?("Failed to reportNewIncomingConversation: \(error)")
            }
        }
        // sleep because of an Apple bug: https://developer.apple.com/forums/thread/774958
        Thread.sleep(forTimeInterval: 0.5)
    }
    
    @objc public func hangupIfNeedWithUUID(_ uuid: String) {
        delegate?.didLogLCK?("hangupIfNeedWithUUID called with UUID: \(uuid)")
        // 使用容错方法将 uuid 字符串转换为有效的 UUID
        let (normalizedUUID, isGenerated) = normalizeCallIdToUUID(uuid)
        if isGenerated {
            delegate?.didLogLCK?("UUID string '\(uuid)' was normalized to: \(normalizedUUID.uuidString)")
        }
        
        // 如果当前没有活跃的 LiveCommunicationKit 通话，直接返回
        guard let currentUUID = conversationUUID else {
            delegate?.didLogLCK?("No active conversation, ignoring hangup request")
            return
        }
        delegate?.didLogLCK?("Current conversation UUID: \(currentUUID.uuidString)")
        // 如果传入的 UUID 与当前 LiveCommunicationKit 通话的 UUID 不匹配
        if normalizedUUID != currentUUID {
            delegate?.didLogLCK?("Hanging up current call due to different UUID")
            endConversation()
        } else {
            delegate?.didLogLCK?("UUID matches current conversation, no action needed")
        }
    }
    
    @objc public func endConversation() {
        delegate?.didLogLCK?("endConversation called")
        if let conversation = currentConversation() {
            conversationManager.reportConversationEvent(.conversationEnded(Date(), .joinedElsewhere), for: conversation)
        }
        reset()
    }
}

@available(iOS 17.4, *)
extension RCLCKCenter: ConversationManagerDelegate {
    public func conversationManager(_ manager: ConversationManager, conversationChanged conversation: Conversation) {
        guard conversation.uuid == conversationUUID else {
            return
        }
    }
    
    public func conversationManagerDidBegin(_ manager: ConversationManager) {
    }
    
    public func conversationManagerDidReset(_ manager: ConversationManager) {
    }
    
    public func conversationManager(_ manager: ConversationManager, perform action: ConversationAction) {
        guard action.conversationUUID == conversationUUID else {
            action.fail()
            return
        }
        
        if let joinAction = action as? JoinConversationAction {
            do {
                try AVAudioSession.sharedInstance().setCategory(.playAndRecord, mode: .voiceChat, options: [.allowBluetooth, .allowBluetoothA2DP, .mixWithOthers])
            } catch {
                delegate?.didLogLCK?("Failed to configure audio session: \(error)")
            }
            isPerformJoinAction = true
            hasJoined = delegate?.didPerformJoinAction?() ?? false
            joinAction.fulfill()
        }
        else if let muteAction = action as? MuteConversationAction {
            delegate?.didPerformMuteAction?(muteAction.isMuted)
            muteAction.fulfill()
        }
        else if let endAction = action as? EndConversationAction {
            delegate?.didLogLCK?("EndConversationAction - User clicked hangup button")
            delegate?.didPerformEndAction?()
            reset()
            endAction.fulfill()
        }
        else {
            action.fail()
        }
    }
    
    public func conversationManager(_ manager: ConversationManager, timedOutPerforming action: ConversationAction) {
        reset()
    }
    
    public func conversationManager(_ manager: ConversationManager, didActivate audioSession: AVAudioSession) {
    }
     
    public func conversationManager(_ manager: ConversationManager, didDeactivate audioSession: AVAudioSession) {
    }
}
