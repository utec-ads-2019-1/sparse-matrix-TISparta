#ifndef MOCKER_H
#define MOCKER_H

#include <random>
#include <type_traits>

const int MIN_VAL = 0;
const int MAX_VAL = 100;

class Mocker {
  public:
    Mocker () {
      rng.seed(std::random_device()());
    }

    template <typename T>
    T* generateRandomArray (unsigned int size) {
      T* elements = new T[size];
      for (int i = 0; i < size; i++) {
        if (std::is_same <T, int>::value) {
          elements[i] = generateRandomInt();
        } else if (std::is_same <T, char>::value) {
          elements[i] = generateRandomChar();
        }
      }
      return elements;
    }

  private:
    std::mt19937 rng;
    int generateRandomInt (int min_val = MIN_VAL, int max_val = MAX_VAL);
    char generateRandomChar ();
};

#endif
