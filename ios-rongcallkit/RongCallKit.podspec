# coding: utf-8
#
#  Be sure to run `pod spec lint RongRTCLib.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see https://guides.cocoapods.org/syntax/podspec.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

#zipfile = "/tmp/RongCallKit.zip"

Pod::Spec.new do |spec|

  # ―――  Spec Metadata  ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  These will help people to find your library, and whilst it
  #  can feel like a chore to fill in it's definitely to your advantage. The
  #  summary should be tweet-length, and the description more in depth.
  #

  spec.name         = "RongCallKit"
  spec.version      = "0.0.1"
  spec.summary      = "A short description of RongCallKit."

  # This description is used to generate tags and improve search results.
  #   * Think: What does it do? Why did you write it? What is the focus?
  #   * Try to keep it short, snappy and to the point.
  #   * Write the description between the DESC delimiters below.
  #   * Finally, don't worry about the indent, CocoaPods strips it!
#  spec.description  = <<-DESC
#                   DESC
  spec.description = 'test a test'

  spec.homepage     = "http://EXAMPLE/RongCallKit"
  # spec.screenshots  = "www.example.com/screenshots_1.gif", "www.example.com/screenshots_2.gif"


  # ―――  Spec License  ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  Licensing your code is important. See https://choosealicense.com for more info.
  #  CocoaPods will detect a license file if there is a named LICENSE*
  #  Popular ones are 'MIT', 'BSD' and 'Apache License, Version 2.0'.
  #

  # spec.license      = "MIT (example)"
  spec.license      = { :type => "MIT", :file => "FILE_LICENSE" }


  # ――― Author Metadata  ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  Specify the authors of the library, with email addresses. Email addresses
  #  of the authors are extracted from the SCM log. E.g. $ git log. CocoaPods also
  #  accepts just a name if you'd rather not provide an email address.
  #
  #  Specify a social_media_url where others can refer to, for example a twitter
  #  profile URL.
  #

  spec.author             = { "jiangchunyu" => "jiangchunyu@rongcloud.cn" }
  # Or just: spec.author    = "jiangchunyu"
  # spec.authors            = { "jiangchunyu" => "jiangchunyu@rongcloud.cn" }
  # spec.social_media_url   = "https://twitter.com/jiangchunyu"

  # ――― Platform Specifics ――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  If this Pod runs only on iOS or OS X, then specify the platform and
  #  the deployment target. You can optionally include the target after the platform.
  #

  # spec.platform     = :ios
  # spec.platform     = :ios, "5.0"

  #  When using multiple platforms
  # spec.ios.deployment_target = "5.0"
  # spec.osx.deployment_target = "10.7"
  # spec.watchos.deployment_target = "2.0"
  # spec.tvos.deployment_target = "9.0"
  spec.platform     = :ios, "9.0"


  # ――― Source Location ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  Specify the location from where the source should be retrieved.
  #  Supports git, hg, bzr, svn and HTTP.
  #

#  system("rm -rf #{zipfile} && zip -r #{zipfile} #{__dir__} > /dev/null")

#  spec.source       = { :git => "http://test/RongCallKit.git", :tag => "#{spec.version}" }
  spec.source       = { :http => "file://x" }


  # ――― Source Code ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  CocoaPods is smart about how it includes source code. For source files
  #  giving a folder will include any swift, h, m, mm, c & cpp files.
  #  For header files it will include any header in the folder.
  #  Not including the public_header_files will make all headers public.
  #

  spec.source_files  = "RongCallKit/**/*.{h,hpp,m,mm,cpp}"

  spec.exclude_files = "Classes/Exclude"

  #spec.public_header_files = "Classes/**/*.h"
  spec.public_header_files = "RongCallKit/RongCallKit.h", "RongCallKit/RCMultiCallInviteNewUserDelegate.h", "RongCallKit/RCCall.h", "RongCallKit/Controller/RCCallSelectMemberViewController.h", "RongCallKit/Controller/RCCallBaseViewController.h", "RongCallKit/Controller/RCCallSingleCallViewController.h", "RongCallKit/Controller/RCCallAudioMultiCallViewController.h", "RongCallKit/Controller/RCCallVideoMultiCallViewController.h", "RongCallKit/Utility/RCCallFloatingBoard.h", "RongCallKit/Utility/RCCallTextButton.h", "RongCallKit/Cell/RCCallMultiCallUserCell.h", "RongCallKit/Cell/RCCallDetailMessageCell.h", "RongCallKit/Cell/RCCallTipMessageCell.h", "RongCallKit/Model/RCCallUserCallInfoModel.h"


  # ――― Resources ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  A list of resources included with the Pod. These are copied into the
  #  target bundle with a build phase script. Anything else will be cleaned.
  #  You can preserve files from being cleaned, please don't preserve
  #  non-essential files like tests, examples and documentation.
  #

  # spec.resource  = "icon.png"
  # spec.resources = "Resources/*.png"

  # spec.preserve_paths = "FilesToSave", "MoreFilesToSave"


  # ――― Project Linking ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  Link your library with frameworks, or libraries. Libraries do not include
  #  the lib prefix of their name.
  #

  # spec.framework  = "SomeFramework"
  # spec.frameworks = "SomeFramework", "AnotherFramework"

  # spec.library   = "iconv"
  # spec.libraries = "iconv", "xml2"
#  spec.frameworks  = "RongIMLib", "RongIMKit", "RongCallLib"
  spec.frameworks  = "RongIMLib", "RongIMKit"


  # ――― Project Settings ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  If your library depends on compiler flags you can set them in the xcconfig hash
  #  where they will only apply to your library. If you depend on other Podspecs
  #  you can include multiple dependencies to ensure it works.

  spec.requires_arc = true

  # spec.xcconfig = { "HEADER_SEARCH_PATHS" => "$(SDKROOT)/usr/include/libxml2" }
  # spec.dependency "JSONKit", "~> 1.4"
#  spec.xcconfig = {'HEADER_SEARCH_PATHS' => ['"${SRCROOT}/libs/"']}
#  spec.xcconfig = {'USER_HEADER_SEARCH_PATHS' => ['"${SRCROOT}/libs/"/**']}
  spec.xcconfig = {'FRAMEWORK_SEARCH_PATHS' => ['"$(SRCROOT)/framework/"']}
#  spec.dependency "RongChatRoom", "5.1.0"
  spec.dependency "RongCloudIM", "5.1.0"
#  spec.dependency "RongCloudRTC/RongCallLib", "5.1.0"
#  spec.vendored_frameworks = "RongCallKit.framework"
  spec.static_framework = false

  spec.ios.deployment_target = '9.0'

end
