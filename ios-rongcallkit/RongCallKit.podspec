
Pod::Spec.new do |spec|

  spec.name         = "RongCallKit"
  spec.version      = "0.0.1"
  spec.summary      = "RongCloud CallKit SDK for iOS - 融云音视频通话SDK"
  spec.description  = <<-DESC
  RongCallKit is a comprehensive CallKit SDK for iOS that provides audio and video calling capabilities.
  This SDK includes features for single and multi-party calls, video conferencing, and call management.
  DESC
  spec.homepage     = "http://www.rongcloud.cn"
  spec.license      = { :type => "MIT", :file => "LICENSE" }
  spec.author       = { "RongCloud" => "www.rongcloud.cn" }
  spec.platform     = :ios, "9.0"
  spec.source       = { :git => "https://github.com/rongcloud/callkit-ios.git", :tag => "#{spec.version}" }
  
  spec.public_header_files = "RongCallKit/Header/*.h"
  
  spec.source_files  = "RongCallKit/**/*.{h,hpp,m,mm,cpp,swift}"
  
  spec.resources = "RongCallKit/Resources/**"

  spec.dependency 'RongCloudRTC/RongCallLib'
  spec.dependency 'RongCloudOpenSource/IMKit'
  
  spec.requires_arc = true
  spec.static_framework = false
  spec.ios.deployment_target = '9.0'
  
end
