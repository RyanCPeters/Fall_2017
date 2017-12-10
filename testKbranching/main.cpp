#include <iostream>
#include <vector>

using namespace std;

void deriveTwoToK(const int &vecSize, int &kRef){
  kRef = 0;
  while(vecSize/(1<<(kRef-1)) > 1)++kRef;
}

/**
 *
 * @param data
 * @param low
 * @param hi
 */
template <class Comparable>
void swap(vector<Comparable> &data, const int &low, const int &hi) {
  int tmp = data[low];
  data[low] = data[hi];
  data[hi] = tmp;
}

/**
 * if sub-array is short, then use insertion sort.
 */
template <class Comparable>
int insertionSort(vector<Comparable> &data, const int &first, const int &last) {
  for (auto i = first; i < last; ++i){
    auto smallest = i;
    for (auto j = i+1; j <= last; ++j ) if (data[j] >= 0 && data[j] < data[smallest]) smallest = j;
    if(smallest == i){
      continue;
    }
    // if smallest is not greater than i, then we have nothing to swap
    swap(data,smallest,i);
  }// end of for i
  return 1; // this return is only accessed if we end up using insertion sort.
}// end of combineArrays(data,first,last) function


int main() {
  vector<int> v = {8467, 41,  6334,  6500,  9169,  5724,  1478,  9358,  6962, 4464,  5705,  8145, 3281,  6827,  9961,   491,  2995,  1942,  4827,
                   5436,  2391,  4604,  3902,   153,   292,  2382,  7421,  8716,  9718, 9895,  5447,  1726,  4771,  1538,  1869,  9912,  5667,  6299, 7035,
                   9894,  8703,  3811,  1322,   333,  7673,  4664,  5141,  7711,  8253, 6868,  5547,  7644,  2662,  2757,    37,  2859,  8723,  9741,  7529,
                   778,  2316,  3035,  2190,  1842,   288,   106,  9040,  8942,  9264, 2648,  7446,  3805,  5890,  6729,  4370,  5350,  5006,  1101,  4393,
                   3548,  9629,  2623,  4084,  9954,  8756,  1840,  4966,  7376,  3931, 6308,  6944,  2439,  4626,  1323,  5537,  1538,  6118,  2082,  2929,
                   6541,  4833,  1115,  4639,  9658,  2704,  9930,  3977,  2306,  1673, 2386,  5021,  8745,  6924,  9072,  6270,  5829,  6777,  5573,  5097,
                   6512,  3986,  3290,  9161,  8636,  2355,  4767,  3655,  5574,  4031, 2052,  7350,  1150,  6941,  1724,  3966,  3430,  1107,   191,  8007,
                   1337,  5457,  2287,  7753,   383,  4945,  8909,  2209,  9758,  4221, 8588,  6422,  4946,  7506,  3030,  6413,  9168,   900,  2591,  8762,
                   1655,  7410,  6359,  7624,   537,  1548,  6483,  7595,  4041,  3602, 4350,   291,   836,  9374,  1020,  4596,  4021,  7348,  3199,  9668,
                   4484,  8281,  4734,    53,  1999,  6418,  7938,  6900,  3788,  8127, 467,  3728,  4893,  4648,  2483,  7807,  2421,  4310,  6617,  2813,
                   9514,  4309,  7616,  8935,  7451,   600,  5249,  6519,  1556,  2798, 303,  6224,  1008,  5844,  2609,  4989,  2702,  3195,   485,  3093,
                   4343,   523,  1587,  9314,  9503,  7448,  5200,  3458,  6618,   580, 9796,  4798,  5281,  9589,   798,  8009,  7157,   472,  3622,  8538,
                   2292,  6038,  4179,  8190,  9657,  7958,  6191,  9815,  2888,  9156, 1511,  6202,  2634,  4272,    55,   328,  2646,  6362,  4886,  8875,
                   8433,  9869,   142,  3844,  1416,  1881,  1998,   322,  8651,    21, 5699,  3557,  8476,  7892,  4389,  5075,   712,  2600,  2510,  1003,
                   6869,  7861,  4688,  3401,  9789,  5255,  6423,  5002,   585,  4182, 285,  7088,  1426,  8617,  3757,  9832,   932,  4169,  2154,  5721,
                   7189,  9976,  1329,  2368,  8692,  1425,   555,  3434,  6549,  7441, 9512,   145,  8060,  1718,  3753,  6139,  2423,  6279,  5996,  6687,
                   2529,  2549};
  int vSize= static_cast<int>( v.size());
  int myK = 0;
  deriveTwoToK(vSize,myK);
  auto shift = vSize/(1<<(myK-1));
  int low = 0, hi = 0,mid = 0;
  long double idx = 0;
  while(shift < vSize){
//    low = static_cast<long>
    hi = low+shift;
    if(shift < 10){
      insertionSort(v,low,hi);
    }
  }
  
  return 0;
}