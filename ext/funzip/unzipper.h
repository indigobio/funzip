#ifndef _unzipper_h
#define _unzipper_h
#include <string>
#include <zip.h>

class Unzipper {
 public:
  Unzipper();
  void unzip(std::string archivePath, std::string destDir);
  ~Unzipper();

 private:
  struct zip *archive;
  struct zip_file *entry;
  FILE *outFile;
  static const int BUFFER_SIZE = 16384;
  char buf[BUFFER_SIZE];

  void extractEntry(zip_uint64_t entryIdx, const std::string& destDir);

  template<typename T>
  T TRY(T value, std::string desc) {
    if (value == NULL)
      throw desc;
    else
      return value;
  }

  template<typename T>
  T TRY0(T value, std::string desc) {
    if (value != 0)
      throw desc + " failed";
    else
      return value;
  }
};

#endif
