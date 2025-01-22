#include <string>

#include "Start.hpp"

int main(int argc, char **argv, const char **env) {
  (void)argc;
  (void)argv;

  Start s(env);

  s.startTheProgram();

  return 0;
}