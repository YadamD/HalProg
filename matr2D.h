#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

using namespace std;

namespace detail
{
	template<typename M1, typename M2, typename F>
	void transform_matrix1(M1 const& m1, M2& m2, F f)
	{
		std::transform(m1.cbegin(), m1.cend(), m2.begin(), f);
	}

	template<typename M1, typename M2, typename M3, typename F>
	void transform_matrix2(M1 const& m1, M2 const& m2, M3& m3, F f)
	{
		std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m3.begin(), f);
	}
}

inline auto add = [](auto const& x, auto const& y){ return x + y; };
inline auto sub = [](auto const& x, auto const& y){ return x - y; };


template<typename T>
vector<T> matmul(vector<T> const& m1, vector<T> const& m2, int l){
    int const len=static_cast<int>(m1.size());
    T sum=0;
    vector<T> u(len);
    if(size!=static_cast<int>(m2.size()) || n!=size){
        cout<<"Multiplication error"<<endl;
        return u;
    }
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++){
            sum=0;
            for(int k=0; k<l; k++){
                sum+=(m[i*l+k])*(m2[k*l+j]);
            }
            u[i*l+j]=sum;
        }
    }
    return u;
}

template<typename T>
class smatrix
{
	int l;
    vector<T> data;

    public:
        smatrix(): l{1}, d{{0.0}}{};
        smatrix(int i): l(i), data(i*i, 0){};
        smatrix(int i, vector<T> const& v){
            if(l*l!=static_cast<int>(v.size())){
                cout<<"Parameter error!"<<endl;
            }
            else{
                data=v;
            }
        }
        
        smatrix<T>(smatrix<T> const& copy): l{copy.l}, data{copy.data}{
            if(l!=copy.l){
                cout<<"Error"<<endl;
                exit(-1);
            }
        }

        T & operator[](int i){return data[i];}
        T & operator()(int i, int j){return data[l*i+j];}
        
        T const& operator[](int i) const {return data[i];}
        T const& operator()(int i, int j)const {return data[l*i+j];}

        smatrix<T>& operator=(smatrix<T>&&)=default;
        
        smatrix<T>& operator+=(smatrix<T> const& m){
            detail::transform_matrix2((*this).data, m.data, (*this).data, add);
            return *this;
        }
        smatrix<T>& operator-=(smatrix<T> const& m){
            detail::transform_matrix2((*this).data, m.data, (*this).data, sub);
            return *this;
        }
        smatrix<T>& operator*=(T const& c){
            detail::transform_matrix1((*this).data, (*this).data, [=](T const& x){return x*c});
            return *this;
        }
        smatrix<T>& operator/=(T const& c){
            detail::transform_matrix1((*this).data, (*this).data, [=](T const& x){return x/c});
            return *this;
        }
        smatrix<T>& operator*=(smatrix<T> const& m){
           vector<T> u=matmul((*this).data, m.data, (*this).l);
           (*this).data.swap(u);
           return *this;
        }


}

template<typename T>
smatrix<T> operator+(smatrix<T> const& m1, smatrix<T> const& m2){
    smatrix<T> result(m1.dimension());
    detail::transform_matrix2(m1, m2, result, add);
    return result;
}

template<typename T>
smatrix<T> operator-(smatrix<T> const& m1, smatrix<T> const& m2){
    smatrix<T> result(m1.dimension());
    detail::transform_matrix2(m1, m2, result, sub);
    return result;
}

template<typename T>
smatrix<T> operator*(smatrix<T> const& c, smatrix<T> const& m){
    smatrix<T> result(m.dimension());
    detail::transform_matrix2(m, result, [c](T const& x){return c*x;});
    return result;
}