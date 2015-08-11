#ifndef _util_h
#define _util_h

#include <string>

std::string trimString(std::string s, const char *chars);
std::string dirname(std::string path);

void mkdir_p(std::string dir);
int mkdir_p2(const char *dir);
int _mkdir(const char *dir, mode_t mode);

#endif
