//
//  SizeofDemo.cpp
//
//  Modified by Michael Stiber 4/3/14, from code in Stroustrup, 3rd edition.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// IMPORTANT: follow step by step instructions as stated in Student Guide and
// be sure to explain any fixes you make.

void increment(int &a) {
    a++;
}

void onePlus(int a) {
    a++;
}

struct Pair {
    string name;
    int val;
};

vector<Pair> pairs;

int& value(const string &s) {
    for (int i = 0; i < pairs.size(); i++) {
        if (s == pairs[i].name) return pairs[i].val;
    }
    Pair p = {s, 0};
    pairs.push_back(p);

    return pairs[pairs.size() - 1].val;
}

int main() {
    int i = 1;
    int &r = i;
    int x = r;

    cout << "Basic reference manipulations:" << endl;
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;

    r = 2;

    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;

//  the reference declaration required an initialization target at declaration.
    int &xr = x;

    cout << "Addresses of i, r, and x: " << &i << " " << &r << " " << &x << endl;

    cout << "\n\nPass by value:" << endl;
    onePlus(i);
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;
    onePlus(r);
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;
    onePlus(x);
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;

    cout << "\n\nPass by reference:" << endl;
    increment(i);
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;
    increment(r);
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;
    increment(x);
    cout << "Values of i, r, and x: " << i << " " << r << " " << x << endl;

    cout << "\n\nReference as lvalue:" << endl;
    value("aa")++;
    value("bb")++;
    value("bb")++;
    value("aa")++;
    value("aa")++;
    value("bb")++;
    value("aa")++;
    value("aa")++;

    for (auto &pair : pairs) {
        cout << pair.name << ": " << pair.val << endl;
    }
}

