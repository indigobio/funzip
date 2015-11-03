require 'mkmf'
extension_name = 'funzip'
dir_config(extension_name)
have_library('zip', 'zip_open')
$CPPFLAGS += ' -Wall -Werror -Wno-format-security -std=c++11 -O3 -fno-strict-aliasing -flto -I/usr/local/lib/libzip/include'

create_makefile(extension_name)
