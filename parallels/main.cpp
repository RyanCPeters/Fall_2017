#include <iostream>
#include <chrono>


using namespace std;
static int SEEK = 45;
long fib_seq (long n) {
  if (n < 2) return n;
  else{
    long a, b;
    fork2([&] {
      a = fib_par(n-1);
    }, [&] {
      b = fib_par(n-2);
    });
    result = a + b;
  }
  
 
}


void setTimeAndUnits(const double &totalTime, double &myTime, string &units)
{
  
  if (totalTime > 1E+9) {
    myTime = totalTime / 1E+9;
    units = " seconds";
  } else if (totalTime > 1E+6) {
    myTime = totalTime / 1E+6;
    units = " milli-seconds";
  } else if (totalTime > 1E+3) {
    myTime = totalTime / 1E+3;
    units = " micro-seconds";
  } else {
    myTime = totalTime;
    units = " nano-seconds";
  }
  
}

int main() {
  
  auto tStart = chrono::high_resolution_clock::now();
  long theFib = fib_seq(SEEK);
  auto  tStop = chrono::high_resolution_clock::now();
  
  auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(tStop - tStart).count();
  double myTime;
  string units;
  setTimeAndUnits(elapsedTime,myTime,units);
  cout <<  "the fib number for " << SEEK << " is " << theFib << endl;
  cout << "sequential fib_seq time for " << SEEK << " was " << myTime << units << endl;
  return 0;
}