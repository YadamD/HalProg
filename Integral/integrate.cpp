#include <iostream>
#include <string>
#include <cmath>

double fun(double x){
    	    return cos(x) * exp(-1*x*x);
    	}

double integrate(int n, double x0, double x1) {
	double ans=0;
	double h=(x1-x0)/n ;
	for(int i=0; i<n+1; i++){
    	double x_0=x0+i*h;
    	double x_1=x_0+h;
    	ans+=(fun(x_1)+fun(x_0))*h/2;
	}
	return ans;
}

int main() {
	double result;
	double x_0 = -1, x_1 = 3;
	std::cout.precision(16);
    for(int i = 0; i < 6; i++){
	    result = integrate(pow(10,i+2), x_0, x_1);
	    std::cout<<"n = "<<pow(10,i+2)<<'\n'<<result<<'\n';
    }
    std::cout << "Expected value: 1.346387956803450376698"<<'\n';
  return 0;
}
