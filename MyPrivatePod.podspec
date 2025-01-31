Pod::Spec.new do |s|
  s.name         = "MyPrivatePod"
  s.version      = "0.1.0"
  s.summary      = "MyPrivatePod iOS SDK"
  s.description  = "iOS library for Bugly Service. Sign up for a service at https://bugly.tds.qq.com."
  s.homepage     = "http://bugly.tds.qq.com/"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "v_caiaknglin" => "v_caiaknglin@duxiaoman.com" }
  s.source       = { :git => "https://github.com/fengqiyunyong2016/MyPrivatePod.git", :tag => "#{s.version}" }
#  s.requires_arc = true  
  s.platform     = :ios, "10.0"
  s.vendored_frameworks ='RiskManage.framework'
  s.resources = ['*.bundle']
  s.library = 'z','c++'
  end
