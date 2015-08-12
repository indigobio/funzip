require 'rspec'
require 'funzip'
require 'tmpdir'

describe Funzip do
  describe '::unzip' do
    it 'unzips' do
      %w(test windows).each do |name|
        Dir.mktmpdir do |dir|
          Funzip.unzip(zip_path(name), dir)
          expect(content_of(dir, 'a.txt')).to eql 'a'
          expect(content_of(dir, 'b/c.txt')).to eql 'c'
          expect(Dir.exists?(File.join(dir, 'd/e/f'))).to be_truthy
        end
      end
    end

    it 'raises an error on failure' do
      expect{Funzip.unzip(zip_path('test'), '/root')}.to raise_error StandardError, 'failed to open output file: /root/a.txt'
    end

    # it 'does not leak small' do
    #   10000000.times do
    #     Dir.mktmpdir do |dir|
    #       Funzip.unzip(zip_path('test'), dir)
    #     end
    #   end
    # end
    #
    # it 'does not leak big' do
    #   10000.times do
    #     Dir.mktmpdir do |dir|
    #       Funzip.unzip('/home/pwinton/Downloads/iamMANOLIS - Dayte.zip', dir)
    #     end
    #   end
    # end

    def zip_path(name)
      File.join(File.dirname(__FILE__), "fixtures/#{name}.zip")
    end

    def content_of(dir, file_path)
      strip_newline(File.read(File.join(dir, file_path)))
    end

    def strip_newline(s)
      s.gsub(/[\r\n]+$/m, '')
    end
  end
end
