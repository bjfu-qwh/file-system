#include "include/config.h"

#include <fstream>

#include "cassert"
#include "cstdio"
#include "include/exception.h"

namespace FileSystem {
auto fetchDiskLocation() -> char * {
  FILE *config = fopen(CONFIG_PATH, "r");
  assert(config != nullptr);
  char *path = new char[PATH_LIMIT];
  fgets(path, PATH_LIMIT, config);
  return path;
}
}  // namespace FileSystem
