#include "include/config.h"

#include "cassert"
#include "cstdio"

namespace FileSystem {
auto fetchDiskLocation() -> char * {
  FILE *config = fopen(CONFIG_PATH, "r");
  assert(config != nullptr);
  char *path = new char[PATH_LIMIT];
  fgets(path, PATH_LIMIT, config);
  return path;
}
}  // namespace FileSystem