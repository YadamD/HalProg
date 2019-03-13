#include<cmath>
#include<vector>
#include<iostream>
#include"vector2.h"


int main(){

    Vector2<double> v;
    v.x=1.0;
    v.y=0.0;

    Vector2<double> u;
    u.x=1.5;
    u.y=1.5;

    Vector2<double> w=u+v;
    std::cout<<"w: "<<w<<"\n";
}