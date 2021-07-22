#include<iostream>
#include "../src/filter/filter.hpp"

// test Low-Pass and High-Pass filters

int main() {
    NUMTYPE x[10] = {0,10,0,10,0,10,0,10,0,10};
    LowPassFilter l;
    HighPassFilter h;
    HighPassFilter f;
    f.LoadData(x,10);
    f.ApplyFilter(10, 100);
    //vector<NUMTYPE> d = f.GetData();
    vector<NUMTYPE> d = HighPassFilter::ApplyFilter(x,10,10,100);
    
    for (auto it = d.begin(); it != d.end(); it++) 
        cout << * it << " ";
    cout << endl;
    
    return 0;
}
