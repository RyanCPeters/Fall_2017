//
// Created by R.Peters on 10/1/2017.
//

#include <iostream>
#include <cmath>

using namespace std;

#include <iostream>
#include <cmath>

int unbiasedRounding(double roundMe);

/* int main()
 * The objectives of this functin:
 * 1. Clearly and definitively show how the various conversion
 * methods from floating point to integers handle floating point numbers halfway
 * between integers, i.e., which end in ".5".
 *
 * 2. To avoid bias in rounding, floating point numbers that end in ".5" should be
 * rounded to even numbers. This will result in rounding up half the time and rounding
 * down the other half, and so there won't be a systematic bias in rounding. Write a
 * function that rounds in this manner and write a program that demonstrates that it
 * works properly.
 * @return
 */
int main() {
    // val_array will hold 21 values from .5 to 20.5
    double val_array [21];

    for (int i = 0; i < 21; ++i) {
        val_array[i] = .5 + i;
    }

    for(double ele : val_array){
        cout
                << "for an input value of " << ele
                << "\n\tthe rounded value should be " << unbiasedRounding(ele)
                << endl;
    }


}
/* int unbiasedRounding(double roundMe)
 *
 * This function will take the given parameter and use the static_cast<> keyword to
 * use it with the modulus operator in checking for even/odd values.
 *
 * It then uses a bit of return zen and the ternary operator to cleanly produce a return
 * value that will always be even.
 *
 * @param roundMe   the fractional value that is expected to be any mixed number that is
 *                  a multiple of .5
 * @return the rounded int type even value.
 */
int unbiasedRounding(double roundMe){
    return static_cast<int>(((static_cast<int>(roundMe - .5)) % 2 == 0.0)? roundMe - 0.5 : roundMe + 0.5 );
}