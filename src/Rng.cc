#include "Rng.h"
#include <x86intrin.h>

static const char kCharacterTable[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

uint64_t GetRngSeed() {
  uint64_t x = __rdtsc();
  uint64_t z = (x += UINT64_C(0x9E3779B97F4A7C15));
  z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
  z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
  return z ^ (z >> 31);
}

void RngInit(RngState *state, uint64_t seed) {
  state->s[0] = seed;
  state->s[1] = seed;
}

uint64_t RngNext(RngState *state) {
  const uint64_t s0 = state->s[0];
  uint64_t s1 = state->s[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  state->s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
  state->s[1] = rotl(s1, 36);

  return result;
}

void RandomString(char *out, size_t length) {
  RngState state;
  RngInit(&state, GetRngSeed());

  for (size_t i = 0; i < length; i++) {
    out[i] = kCharacterTable[RngNext(&state) % (sizeof(kCharacterTable) - 1)];
  }
}

uint64_t RandomU64() {
  RngState state;
  RngInit(&state, GetRngSeed());
  return RngNext(&state);
}

uint32_t RandomU32() { return (uint32_t)RandomU64(); }
