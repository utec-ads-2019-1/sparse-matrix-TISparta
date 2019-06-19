#include <ostream>

namespace Color {
  enum Code {
    BLACK      = 30,
    RED        = 31,
    GREEN      = 32,
    YELLOW     = 33,
    BLUE       = 34,
    MAGENTA    = 35,
    CYAN       = 36,
    WHITE      = 37,
    DEFAULT    = 0,
    BOLD       = 1,
    UNDERLINE  = 4
  };
  class Modifier {
    Code code;
    public:
      Modifier(Code pCode) : code(pCode) {}
      friend std::ostream&
      operator << (std::ostream& os, const Modifier& mod) {
        return os << "\033[" << mod.code << "m";
      }
  };
  static Modifier black(BLACK);
  static Modifier red(RED);
  static Modifier green(GREEN);
  static Modifier yellow(YELLOW);
  static Modifier blue(BLUE);
  static Modifier magenta(MAGENTA);
  static Modifier cyan(CYAN);
  static Modifier white(WHITE);
  static Modifier normal(DEFAULT);
  static Modifier bold(BOLD);
  static Modifier underline(UNDERLINE);
}

