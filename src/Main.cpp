#include <string>

#include "Start.hpp"

#ifndef COMPILE_TEST
int main(int argc, char **argv, const char **env) {
  (void)argc;
  (void)argv;

  Start s(env);

  s.startTheProgram();

  return 0;
}
#endif