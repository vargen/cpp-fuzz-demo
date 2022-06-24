#include <stdint.h>
#include <stddef.h>

#include <iostream>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_iso_in_DMY(char *input, int size);

// extern "C" int FUZZ_INIT_WITH_ARGS(int *argc, char ***argv) {
extern "C" int FUZZ_INIT() {

  // Add global setup code here - called once before fuzzing starts

  return 0;
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {

  // process fuzzer input (*Data) and setup local objects necessary to call the function under test

  print_iso_in_DMY((char*) Data, (int) Size);

  // reset state and free all locally allocated resources

  return 0;
}
