#pragma once
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

  void extractEntry(zip_uint64_t entryIdx, const std::string& destDir);
  template<typename T> T TRY(T value, std::string desc);
  template<typename T> T TRY0(T value, std::string desc);
};
