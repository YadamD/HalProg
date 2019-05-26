#include <iostream>
#include "matr2D.h"
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <cmath>
#include <iterator>

using namespace std;

smatrix<double> rand_mat(int l, normal_distribution<double> distr, mt19937 gen){
    vector<double> v(l*l);
    generate(v.begin(),v.end(), [&]{return distr(gen); });
    smatrix<double> m(l,v);
    return m;
}

int main(int, char**) {
    
    mt19937 gen(42);
    normal_distribution<double> distr(100,20);

    vector<double> time_mul;

    for(int i=5;i<1206;i+=20){
        auto t0 = chrono::high_resolution_clock::now();
        smatrix<double> m1=rand_mat(i, distr, gen);
        smatrix<double> m2=rand_mat(i, distr, gen);
        auto t1 = chrono::high_resolution_clock::now();
        smatrix<double> mul=m1*m2;
        auto t2 = chrono::high_resolution_clock::now();

        cout <<i<< " Allocation took: " << chrono::duration_cast<chrono::microseconds>(t1-t0).count() << " microseconds." << endl;
        cout << "Multiplication took: " << chrono::duration_cast<chrono::microseconds>(t2-t1).count() << " microseconds." << endl;

        time_mul.push_back(chrono::duration_cast<chrono::microseconds>(t2-t1).count());

        ofstream output_file("./times.txt");
        ostream_iterator<double> output_iterator(output_file, "\n");
        copy(time_mul.begin(), time_mul.end(), output_iterator);

    }

}
