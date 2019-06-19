#include "mocker.h"

int Mocker::generateRandomInt (int min_val, int max_val) {
  std::uniform_int_distribution <std::mt19937::result_type> distribution(min_val, max_val);
  return distribution(rng);
}

char Mocker::generateRandomChar () {
  int increment = generateRandomInt() % 26;
  return 'a' + increment;
}
