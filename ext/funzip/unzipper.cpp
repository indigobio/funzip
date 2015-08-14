#include <zip.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "unzipper.h"
#include "util.h"

using namespace std;

Unzipper::Unzipper(string archivePath) {
  archive = TRY(zip_open(archivePath.c_str(), ZIP_CHECKCONS, nullptr), "zip_open");
}

Unzipper::~Unzipper() {
  zip_close(archive);
}

void Unzipper::unzip(string destDir) {
  destDir = trimString(destDir, "/");
  zip_uint64_t numEntries = zip_get_num_entries(archive, 0);
  for (zip_uint64_t i=0; i<numEntries; i++)
    ZipEntry(archive, i).extract(destDir);
}

ZipEntry::ZipEntry(zip *archive, zip_uint64_t entryIdx) {
  entry = TRY(zip_fopen_index(archive, entryIdx, 0), "zip_fopen_index");
  name = string(TRY(zip_get_name(archive, entryIdx, 0), "zip_get_name"));
  std::replace(name.begin(), name.end(), '\\', '/');
}

ZipEntry::~ZipEntry() {
  zip_fclose(entry);
}

#define BUFFER_SIZE  16384

void ZipEntry::extract(const string& destDir) {
  string destPath = destDir + "/" + name;
  
  if (destPath.back() == '/') {
    mkdir_p(destPath);
  } else {
    mkdir_p(dirname(destPath));
    char buf[BUFFER_SIZE];
    ofstream outFile;
    outFile.open(destPath.c_str(), ofstream::out);
    if (!outFile.is_open())
      throw string("failed to open output file: " + destPath);
    
  readMore:
    zip_int64_t nRead = zip_fread(entry, &buf, BUFFER_SIZE);
    if (nRead == -1)
      throw string("error reading from zip file");
    else if (nRead > 0) {
      outFile.write(buf, (long int)nRead);
      goto readMore;
    }
  }
}

template<typename T>
T TRY(T value, std::string desc) {
  if (value == nullptr)
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
