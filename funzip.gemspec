Gem::Specification.new do |s|
  s.name          = 'funzip'
  s.version       = '0.0.6'
  s.summary       = 'Simple native unzip'
  s.author        = 'Peter Winton'
  s.email         = %w(info@indigobio.com)
  s.description   = 'Uses libzip (native C) to unzip a zip file to a destination directory'
  s.homepage      = 'http://www.indigobio.com'

  s.files = Dir.glob('ext/**/*.{h,c,rb}') + Dir.glob('lib/**/*.rb')

  s.extensions << 'ext/funzip/extconf.rb'
  s.add_development_dependency 'rake-compiler', '~> 0'
  s.add_development_dependency 'rspec', '~> 3.0'
end
