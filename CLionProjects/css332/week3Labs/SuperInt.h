/*
 * SuperInt.h
 *
 * This is a class that acts like an int, but outputs various useful
 * stuff. You can add to this to experiment!
 *
 * Created by Michael Stiber on 1/31/14
 */
#include <string>

class SuperInt {
 public:
  // Name helps us see which variable
  SuperInt(int init, const char *name);

  ~SuperInt();

  // Post-increment
  int operator++(int);

  // For demonstrating lvalues
  const int& theValue(void) const;

 private:
  int myValue;
  std::string myName;

  // Neat trick: making this private prevents creating unitialized
  // objects
  SuperInt();

};



