#include "FuzzedDataProvider.h"
#include <stdint.h>
#include <stddef.h>

#include <iostream>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * duplicate_str(char *input, int str_len, long duplicate_cnt);

// extern "C" int FUZZ_INIT_WITH_ARGS(int *argc, char ***argv) {
extern "C" int FUZZ_INIT() {

  // Add global setup code here - called once before fuzzing starts

  return 0;
}

extern "C" int FUZZ(const uint8_t *Data, size_t Size) {

FuzzedDataProvider fuzz_data_provider(Data, Size);
FuzzedDataProvider *fuzz_data = &fuzz_data_provider;

int duplicate_count = fuzz_data->ConsumeIntegral<int>();
std::vector<char> fuzz_data_0 = fuzz_data->ConsumeRemainingBytes<char>();

duplicate_str((char*)(&fuzz_data_0[0]), fuzz_data_0.size(), duplicate_count);

return 0;

}
