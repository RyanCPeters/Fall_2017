#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <sstream>
#include <iterator>
#include <ctime>

using namespace std;

/**
 *
 * @param name
 * @param lowBound
 * @param hiBound
 */
void generateRandoIntFile(const string& name,const int &lowBound,const int &hiBound){
    ofstream myfile;
    myfile.open(name);
//    std::default_random_engine generator1;
//    std::uniform_int_distribution<int> distribution(lowBound,hiBound);
//    int burner = distribution(generator1);
//    myfile << distribution(generator1);
    int k = rand()%60 -30;
    myfile << "{ " << k;
    for(int i = 0; i < 200;++i){

        k = rand()%60 -30;
        myfile << "," << k;//distribution(generator1);
        myfile.flush();
    }

    myfile.close();
}
/**
 *
 * @param name
 * @return
 */
vector<int> readFromRandoIntFile( const string& name){
    ifstream file(name);
    vector<int> dest;
    if(file.is_open()){
        std::string tmp;
        while(getline(file,tmp,',')){
            stringstream ss(tmp);
            vector<int> line{ istream_iterator<int>(ss), istream_iterator<int>() };
            for(const auto &i : line)dest.push_back(i);

        }
    }
    return dest;

}

int findGreatestSum(const string &name,const bool &makenew){
    if (makenew) {
        generateRandoIntFile(name, -30, 30);
    }
    vector<int> test = readFromRandoIntFile(name);
//    cout << test.size();
//    printf("\n{\n% -5d", test[0]);
//
//    for (auto iter = test.begin() + 1; iter != test.end(); ++iter) {
//
//        printf("% -5d", *iter.operator->());
//    }
//    cout << " \n}\n\n";

    int l, r;
    l = 0, r = test.size() - 1;
    // check for positive values by starting at the ends of array and iterating inward to the center.
    // if one or fewer values are found, we can stop searching. The result is the convenience of being able to
    // reduce the total number of elements we need to consider in the rest of our search.
    while (l <= r) {
        if (test[l] < 0)++l;
        else if (test[r] < 0)--r;
        else break;
    }
    if (l == r)return test[l];
    else if (l > r)return 0;
    int curSum = 0;

    curSum = 0;
    // now we need to store the values of l and r  for comparison against any subsequent positive values found.
    int lSum = test[l];
    // we can alo try to further eliminate the number of values that we should consider by eliminating any positive values
    // that get cancelled by subsequent negative values that net sum to less than 0;
    while (l < r) {
        lSum = (lSum + test[++l] > 0) ? lSum + test[l] : 0;
        curSum = (curSum < lSum) ? lSum : curSum;
    }
    return curSum;
}


int main() {
    srand(time(0));
//    string name = R"(C:\Users\Peter\GitHub_remotes\Fall_UWB_2017\css_342\sampleProblems\RandomIntArraySample.txt)",
//    theIn;
//    cout << "Concerning what collection of random ints you want. \nType (y) to generate a new random collection\ntype (n) to use the old collection.\n\n";
//    cin >> theIn;
    bool makenew = true;
//    for(const char &c : theIn){
//        if(c == 'y'){
//            makenew = true;
//            break;
//        }
//    }
    vector<vector<int>> avgs;
    for(int k = 0; k < 100; ++ k) {
        vector<int> forK;
        forK.reserve(100);
        for (int i = 0; i < 100; ++i) {
            string name = R"(C:\Users\Peter\GitHub_remotes\Fall_UWB_2017\css_342\sampleProblems\RandomIntArraySample)";
            stringstream ss;
            ss << i;
            name += ss.str() + ".txt";
            ss.str(string());
            forK.push_back(findGreatestSum(name, true));
        }
        avgs.push_back(forK);
    }

    int sumsum = 0;
    for(const auto &vec:avgs){
        int sum = 0;
        for(const auto &i: vec)sum+=i;
        sum/=vec.size();
        sumsum+=sum;
    }
    sumsum/=avgs.size();
    cout << sumsum << endl;

    return 0;
}

