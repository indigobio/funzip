#include <zip.h>
#include <ruby.h>
#include <string>
#include "unzipper.h"

using namespace std;

void funzip(string fileName, string destDir) {
  try {
    Unzipper().unzip(fileName, destDir);
  } catch (string err) {
    rb_raise(rb_eStandardError, err.c_str());
  }
}

VALUE method_unzip(VALUE self, VALUE filename, VALUE dest_dir) {
  funzip(string(RSTRING_PTR(filename)), string(RSTRING_PTR(dest_dir)));
  return Qnil;
}

extern "C" void Init_funzip() {
  rb_define_singleton_method(rb_define_module("Funzip"),
                             "unzip",
                             (VALUE(*)(ANYARGS))method_unzip,
                             2);
}
