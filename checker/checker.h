#ifndef CHECKER_H
#define CHECKER_H

#include <string>

class Checker {
  public:
    Checker () {}
    void isEqual (int, int, std::string error_message);
  private:
    int number_correct_tests = 0;
    int number_incorrect_tests = 0;
};

#endif
