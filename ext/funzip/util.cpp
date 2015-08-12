#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <string>

#include "util.h"

using namespace std;

string trimString(string s, const char *chars) {
  size_t endpos = s.find_last_not_of(chars);
  if (string::npos == endpos)
    return s;
  else
    return s.substr(0, endpos+1);
}

string dirname(string path) {
  size_t last_slash = path.find_last_of("/");
  return path.substr(0, last_slash);
}

void mkdir_p(string dir) {
  int result = mkdir_p2(dir.c_str());
  if (result != 0)
    throw "failed: mkdir_p(" + dir + ")";
}

// son of a ...
// from stack overflow or something
int mkdir_p2(const char *dir) {
  char tmp[2048];
  char *p = nullptr;
  size_t len;
  mode_t mode = 0755;

  snprintf(tmp, sizeof(tmp), "%s", dir);
  len = strlen(tmp);
  if (tmp[len - 1] == '/')
    tmp[len - 1] = 0;
  for (p = tmp + 1; *p; p++)
    if (*p == '/') {
      *p = 0;
      if (_mkdir(tmp, mode))
        return -1;
      *p = '/';
    }

  return _mkdir(tmp, mode);
}

int _mkdir(const char *dir, mode_t mode) {
  struct stat info;
  if (stat(dir, &info) == 0 && info.st_mode & S_IFDIR)
    return 0; // already exists
  else
    return mkdir(dir, mode);
}
