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
  double const denominator=std::accumulate(x.begin(),x.end(), 0.0, f1);
  double numerator=0.0;
  for(int i=0; i<static_cast<int>(x.size()); i++){
    numerator+=(x[i]-xmean)*(y[i]-ymean);
  }
  if(denominator==0.0){
    std::cout << "Denominator can't be 0!" << '\n';
  }
  double const b=numerator/denominator;
  double const m=ymean-b*xmean;

  return {b, m};

}

int main(){
  std::vector<double> const v1={1,2,3,4};
  std::vector<double> const v2={4,6,8,10};
  std::array<double, 2> fit1=line_fit(v1,v2);
  std::array<double, 2> fit2=line_fit(v2,v1);
  std::array<double, 2> fit3=line_fit(v1,v1);
  std::cout << "Fit1: m="<<fit1[1]<<" b="<<fit1[0] << '\n';
  std::cout << "Fit2: m="<<fit2[1]<<" b="<<fit2[0] << '\n';
  std::cout << "Fit3: m="<<fit3[1]<<" b="<<fit3[0] << '\n';
  return 0;
}
