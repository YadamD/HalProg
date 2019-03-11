#include <iostream>
#include <cmath>

double sqrt_newton(double num, double x0){
    double xnew=x0;
    double delta=1;
    int k=1;
    while(delta>0.001 and k<21){
        double xold=xnew;
        xnew=xnew-(xnew*xnew-num)/(2*xnew);
        delta=(xold-xnew)*(xold-xnew);
        k++;

    }
    return xnew;
}

double sqrt_newton_for(double num, double x0){
    double xnew=x0;
    for(int i=0; i<5; i++){
        xnew=xnew-(xnew*xnew-num)/(2*xnew);
    }
    return xnew;

}

template<typename F1, typename F2, typename T>
T sqrt_type(F1 fun, F2 der, T x0){
    double xnew=x0;
    double delta=1;
    int k=1;
    while(delta>0.001 and k<21){
        double xold=xnew;
        xnew=xnew-(fun(xnew))/der(xnew);
        delta=(xold-xnew)*(xold-xnew);
        k++;

    }
    return xnew;

}

int main(int, char**) {
    double root=sqrt_type([](double x){ return x*x-612.0;   },[](double x){ return 2.0*x; }, 10.0);
    double dif=24.7386337-root;
    std::cout<<"The root is: "<<root<<"\n";
    std::cout<<"Difference: "<<dif;
}
