
Pod::Spec.new do |spec|

  spec.name         = "RongCallKit"
  spec.version      = "0.0.1"
  spec.summary      = "A short description of RongCallKit."
  spec.description  = 'Debug for RongCallKit source code'
  spec.homepage     = "http://www.rongcloud.cn"
  spec.author       = { "RongCloud" => "www.rongcloud.cn" }
  spec.platform     = :ios, "9.0"
  spec.source       = { :http => "file://x" }
  
  spec.public_header_files = "RongCallKit/Header/*.h"
  
  spec.source_files  = "RongCallKit/**/*.{h,hpp,m,mm,cpp}"
  
  spec.resources = "RongCallKit/Resources/**"

  spec.dependency 'RongCloudRTC/RongCallLib'
  spec.dependency 'RongCloudOpenSource/IMKit'
  
  spec.requires_arc = true
  spec.static_framework = false
  spec.ios.deployment_target = '9.0'
  
end
