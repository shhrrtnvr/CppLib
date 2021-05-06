#include <bits/stdc++.h>
using namespace std;

int main() {
    random_device rd; //true random generator, but slow
    mt19937 mt; //fast but generates same number everytime program runs

    uniform_int_distribution<int> dist(1, 99); //

    cout<<"Random device generates: "<<dist(rd)<<endl; 
    cout<<"Mersene twister generates: "<<dist(mt)<<endl;

    // To create mt generate random number everytime, give a random seed
    mt19937 mt2(rd()); //rd is a good option, because it generates random number every time
    cout<<"MT generates after random seed: "<<dist(mt2)<<" "<<dist(mt2)<<endl;

    //Dont use random_shuffle, insted use shuffle with a random generator like mt
    vector<int> v {1, 2, 3, 4, 5};
    shuffle(begin(v), end(v), mt2); 
    for (auto x : v) cout<<x<<" "; cout<<endl;
    
    return 0;
}