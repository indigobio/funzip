#include <zip.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>

#include "unzipper.h"
#include "util.h"

using namespace std;

Unzipper::Unzipper() : archive(nullptr), entry(nullptr), outFile(nullptr) { }

Unzipper::~Unzipper() {
  if (entry != nullptr)
    zip_fclose(entry);
  if (archive != nullptr)
    zip_close(archive);
  if (outFile != nullptr)
    fclose(outFile);
}

void Unzipper::unzip(string archivePath, string destDir) {
  destDir = trimString(destDir, "/");
  archive = TRY(zip_open(archivePath.c_str(), ZIP_CHECKCONS, nullptr), "zip_open");
  auto numEntries = zip_get_num_entries(archive, 0);
  for (zip_int64_t i=0; i<numEntries; i++)
    extractEntry(i, destDir);
  TRY0(zip_close(archive), "zip_close");
  archive = nullptr;
}

#define BUFFER_SIZE  16384

void Unzipper::extractEntry(zip_uint64_t entryIdx, const string& destDir) {
  entry = TRY(zip_fopen_index(archive, entryIdx, 0), "zip_fopen_index");
  string fName = string(TRY(zip_get_name(archive, entryIdx, 0), "zip_get_name"));
  std::replace(fName.begin(), fName.end(), '\\', '/');
  string destPath = destDir + "/" + fName;
  if (destPath.back() == '/') { mkdir_p(destPath); return; }
  mkdir_p(dirname(destPath));
  
  outFile = TRY(fopen(destPath.c_str(), "w"), "fopen " + destPath);
  char buf[BUFFER_SIZE];
  
 readMore:
  zip_int64_t nRead = zip_fread(entry, &buf, BUFFER_SIZE);
  if (nRead == -1)
    throw string("error reading from zip file");
  else if (nRead > 0) {
    if (fwrite(&buf, 1, nRead, outFile) != (size_t)nRead)
      throw string("error writing to destination");
    goto readMore;
  }
  
  TRY0(fclose(outFile), "fclose");
  outFile = nullptr;
  TRY0(zip_fclose(entry), "zip_fclose");
  entry = nullptr;
}

template<typename T>
T Unzipper::TRY(T value, std::string desc) {
  if (value == nullptr)
    throw desc;
  else
    return value;
}

template<typename T>
T Unzipper::TRY0(T value, std::string desc) {
  if (value != 0)
    throw desc + " failed";
  else
    return value;
}
