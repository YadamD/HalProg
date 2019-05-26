#include <iostream>
#include <cmath>

double sq(double x){
    return x*x;
}
double sqrt_newton(double num, double x0){
    double xnew=x0;
    double delta=1;
    int k=1;
    while(delta>0.001 and k<21){
        double xold=xnew;
        xnew=xnew-(sq(xnew)-num)/(2*xnew);
        delta=sq(xold-xnew);
        k++;

    }
    return xnew;

double sqrt_newton_for(double num, double x0){
    double xnew=x0;
    for(int i=0; i<5; i++){
        xnew=xnew-(sq(xnew)-num)/(2*xnew);
    }
    return xnew;

}

int main(int, char**) {
    double root=sqrt_newton(612, 35.6);
    std::cout<<root;
}
