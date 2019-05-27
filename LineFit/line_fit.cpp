#include <iostream>
#include <vector>
#include <array>
#include <numeric>


double sq(double x){
    return x*x;
}

std::array <double, 2> line_fit(std::vector<double> const& x, std::vector<double> const& y){
  if(static_cast<int>(x.size()) != static_cast<int>(y.size())){
      std::cout<<"Input error: x vector and y vector must have same size but have sizes "<<static_cast<int>(x.size())<<" and "<<static_cast<int>(y.size())<<"\n";
      return {0,0};
  }
  double const xmean=std::accumulate(x.begin(),x.end(),0.0)/static_cast<double>(x.size());
  double const ymean=std::accumulate(y.begin(),y.end(),0.0)/static_cast<double>(y.size());
  auto f1=[xmean](double x0, double xn){
    return x0+sq(xn-xmean);
  };
  auto f2=[xmean,ymean](double x, double y){
    return (x-xmean)*(y-ymean);
  };
  auto addup=[](double v1, double v2){
    return v1+v2;
  };
  double const denominator=std::accumulate(x.begin(),x.end(), 0.0, f1);
  double numerator=std::inner_product(x.begin(),x.end(),y.begin(),0.0,addup,f2);
  /*for(int i=0; i<static_cast<int>(x.size()); i++){
    numerator+=(x[i]-xmean)*(y[i]-ymean);
  }*/
  if(denominator==0.0){
    std::cout << "Denominator can't be 0!" << '\n';
  }
  double const m=numerator/denominator;
  double const b=ymean-m*xmean;

  return {m, b};

}

int main(){
  std::vector<double> const v1={1,2,3,4};
  std::vector<double> const v2={4,6,8,10};
  std::vector<double> const w1={1.0,2.0,3.0,4.0};
  std::vector<double> const w2={1.0,1.2,3.0,7.0};
  std::vector<double> const u1={1.32,4.56,4.99,6.15};
  std::vector<double> const u2={-1.01,-3.2,-3.42,-7.07};
  std::array<double, 2> fit1=line_fit(v1,v2);
  std::array<double, 2> fit2=line_fit(v2,v1);
  std::array<double, 2> fit3=line_fit(v1,v1);
  std::array<double, 2> fit4=line_fit(w1,w2);
  std::array<double, 2> fit5=line_fit(u1,u2);
  std::cout << "Fit1: m="<<fit1[0]<<" b="<<fit1[1] << '\n';
  std::cout << "Fit2: m="<<fit2[0]<<" b="<<fit2[1] << '\n';
  std::cout << "Fit3: m="<<fit3[0]<<" b="<<fit3[1] << '\n';
  std::cout << "Fit4: m="<<fit4[0]<<" b="<<fit4[1] << '\n';
  std::cout << "Fit4 difference with reference from internet: m_dif="<<fit4[0]-1.98<<" b_dif="<<fit4[1]+1.9<<'\n';
  std::cout << "Fit5: m="<<fit5[0]<<" b="<<fit5[1] << '\n';
  std::cout << "Fit5 difference with reference from internet: m_dif="<<fit5[0]+1.084472<<" b_dif="<<fit5[1]-0.9394304<<'\n';
  return 0;
}
