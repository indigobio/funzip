require 'funzip'
require 'tmpdir'
require 'etc'

describe Funzip do
  describe '::unzip' do
    context 'when the destination directory exists' do
      it 'unzips the zip file' do
        %w(test windows).each do |name|
          Dir.mktmpdir do |dir|
            Funzip.unzip(zip_path(name), dir)
            verify_unzipped_contents(dir)
          end
        end
      end
    end
    context 'when the destination directory does not exist' do
      it 'unzips the zip file anyway' do
        %w(test windows).each do |name|
          Dir.mktmpdir do |dir|
            non_exist_dir = File.join(dir, 'non_existent_dir')
            Funzip.unzip(zip_path(name), non_exist_dir)
            verify_unzipped_contents(non_exist_dir)
          end
        end
      end
    end

    # Unable to run the following scenario on the build server (which is root by default)
    unless File.writable?('/root')
      context 'when the destination directory is not owned by process' do
        it 'raises an error' do
          expect do
            Funzip.unzip(zip_path('test'), '/root')
          end.to raise_error StandardError, 'failed to open output file: /root/a.txt'
        end
      end
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

    def verify_unzipped_contents(dir)
      expect(content_of(dir, 'a.txt')).to eql 'a'
      expect(content_of(dir, 'b/c.txt')).to eql 'c'
      expect(Dir.exist?(File.join(dir, 'd/e/f'))).to be_truthy
    end
  end
end
