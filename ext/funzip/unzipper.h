#pragma once
#include <string>
#include <zip.h>

template<typename T> T TRY(T value, std::string desc);
template<typename T> T TRY0(T value, std::string desc);

class Unzipper {
 public:
  Unzipper(std::string archivePath);
  void unzip(std::string destDir);
  ~Unzipper();

 private:
  struct zip *archive;
};


class ZipEntry {
 public:
  ZipEntry(zip *archive, zip_uint64_t entryIdx);
  void extract(const std::string& destDir);
  ~ZipEntry();

 private:
  struct zip_file *entry;
  std::string name;
};
