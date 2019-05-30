#include<cmath>
#include<vector>
#include<iostream>
#include"vector2.h"


int main(){

    double const err=1e-14;

    Vector2<double> v;
    v.x=1.0;
    v.y=0.0;

    Vector2<double> u;
    u.x=1.5;
    u.y=1.5;

    Vector2<double> sum;
    sum.x=2.5;
    sum.y=1.5;

    Vector2<double> dif;
    dif.x=-0.5;
    dif.y=-1.5;

    Vector2<double> mul;
    mul.x=2.0;
    mul.y=0.0;

    Vector2<double> div;
    div.x=0.5;
    div.y=0.5;


    if(vecnoteq((v+u),sum,err))     {std::cout<<" Addition error "<<std::endl;      }
    if(vecnoteq((v-u),dif,err))     {std::cout<<" Subtraction error "<<std::endl;   }
    if(std::abs(dot(v,u)-1.5)>err)  {std::cout<<" Dot product error "<<std::endl;   }
    if(vecnoteq((v*2.0),mul,err))   {std::cout<<" Multiplication error "<<std::endl;}
    if(vecnoteq((u/3.0),div,err))   {std::cout<<" Division error "<<std::endl;      }

    Vector2<double> v_or=v;
    if(vecnoteq(v,v_or,err))        {std::cout<<" = error "<<std::endl;             }
    v+=u;
    if(vecnoteq(v,sum,err))         {std::cout<<" += error "<<std::endl;            }
    v-=u;
    if(vecnoteq(v,v_or,err))        {std::cout<<" -= error "<<std::endl;            }
    v*=2;
    if(vecnoteq(v,mul,err))         {std::cout<<" *= error "<<std::endl;            }
    v/=2;
    if(vecnoteq(v,v_or,err))        {std::cout<<" /= error "<<std::endl;            }

}