#include <iostream>
#include <cmath>

template<typename T>
T sq(T x){
    return x*x;
}

double sqrt_newton(double num, double x0){
    double xnew=x0;
    double delta=1;
    int k=1;
    while(delta>0.01 and k<21){
        double xold=xnew;
        xnew=xnew-(sq(xnew)-num)/(2*xnew);
        delta=std::abs(xold-xnew);
        k++;

    }
    return xnew;
}

double sqrt_newton_for(double num, double x0){
    double xnew=x0;
    for(int i=0; i<5; i++){
        xnew=xnew-(sq(xnew)-num)/(2*xnew);
    }
    return xnew;

}

template<typename F1, typename F2, typename T>
T sqrt_type(F1 fun, F2 der, T x0){
    T xnew=x0;
    T delta=1;
    int k=1;
    while(delta>0.01 and k<21){
        T xold=xnew;
        xnew=xnew-(fun(xnew))/der(xnew);
        delta=std::abs(xold-xnew);
        k++;

    }
    return xnew;

}

int main(int, char**) {
    double root=sqrt_type([](double x){ return sq(x)-612.0;   },[](double x){ return 2.0*x; }, 10.0);
    double dif=24.7386337-root;
    std::cout<<"The root is: "<<root<<"\n";
    std::cout<<"Difference: "<<dif;
}
