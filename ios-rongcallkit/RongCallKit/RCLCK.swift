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
import RongCloudOpenSource

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
                guard let uuid = UUID(uuidString: callId) else {
                    delegate?.didLogLCK?("Invalid callId format: \(callId)")
                    return
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
        // 验证传入的 UUID 格式
        guard UUID(uuidString: uuid) != nil else {
            delegate?.didLogLCK?("Invalid UUID format: \(uuid)")
            return
        }
        // 如果当前没有活跃的 LiveCommunicationKit 通话，直接返回
        guard let currentUUID = conversationUUID else {
            delegate?.didLogLCK?("No active conversation, ignoring hangup request")
            return
        }
        delegate?.didLogLCK?("Current conversation UUID: \(currentUUID.uuidString)")
        // 如果传入的 UUID 与当前 LiveCommunicationKit 通话的 UUID 不匹配
        if uuid != currentUUID.uuidString {
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
