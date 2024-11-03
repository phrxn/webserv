#include <string>

#include "Start.hpp"

#ifndef COMPILE_TEST
int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  Start s;

  s.startTheProgram();

  return 0;
}
#endif