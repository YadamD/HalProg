#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

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

auto add = [](auto const& x, auto const& y){ return x + y; };
auto sub = [](auto const& x, auto const& y){ return x - y; };

/*
template<typename T>
std::vector<T> matmul(std::vector<T> const& m1, std::vector<T> const& m2, int l){
    int const len=static_cast<int>(m1.size());
    T sum=0;
    int n=l*l;
    std::vector<T> u(len);
    if(len!=static_cast<int>(m2.size()) || n!=len){
        std::cout<<"Multiplication error"<<std::endl;
        return u;
    }
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++){
            sum=0;
            for(int k=0; k<l; k++){
                sum+=(m1[i*l+k])*(m2[k*l+j]);
            }
            u[i*l+j]=sum;
        }
    }
    return u;
}
*/



template<typename T>
class smatrix
{
	

    public:
        
        int l;
        std::vector<T> data;

        smatrix(): l{1}, data{{0}}{};
        smatrix(int i): l(i), data(i*i, 0){};
        smatrix(int i, std::vector<T> const& v){
            if(i*i!=static_cast<int>(v.size())){
                std::cout<<"Parameter error!"<<std::endl;
            }
            else{
                l=i;
                data=v;
            }
        }
        
        smatrix<T>(smatrix<T> const& copy): l{copy.l}, data{copy.data}{
            if(l!=copy.l){
                std::cout<<"Error with copying"<<std::endl;
                exit(-1);
            }
        }

        T & operator[](int i){return data[i];}
        T & operator()(int i, int j){return data[l*i+j];}
        
        T const& operator[](int i) const {return data[i];}
        T const& operator()(int i, int j)const {return data[l*i+j];}

        smatrix<T>& operator=(smatrix<T>&&)=default;
        smatrix<T>(smatrix<T>&& o) noexcept : l(std::exchange(o.l, 0)), data(std::move(o.data)) {}
        
        smatrix<T>& operator=(const smatrix<T> &)=default;

        
        
        smatrix<T>& operator+=(smatrix<T> const& m){
            detail::transform_matrix2((*this).data, m.data, (*this).data, add);
            return *this;
        }
        smatrix<T>& operator-=(smatrix<T> const& m){
            detail::transform_matrix2((*this).data, m.data, (*this).data, sub);
            return *this;
        }
        smatrix<T>& operator*=(T const& c){
            detail::transform_matrix1((*this).data, (*this).data, [=](T const& x){return x*c;});
            return *this;
        }
        smatrix<T>& operator/=(T const& c){
            detail::transform_matrix1((*this).data, (*this).data, [=](T const& x){return x/c;});
            return *this;
        }
        /*smatrix<T>& operator*=(smatrix<T> const& m){
           std::vector<T> u=matmul((*this).data, m.data, (*this).l);
           (*this).data.swap(u);
           return *this;
        }*/

        smatrix<T>& operator*=(smatrix<T> const& m);

        int size() const{
            return l*l;
        }
        
        int dimension() const{
		return l;
        }

        auto begin(){
		return data.begin();
        }

        auto cbegin() const{
            return data.cbegin();
        }

        auto end(){
            return data.end();
        }

        auto cend() const{
            return data.cend();
        }

        std::vector<T> dat() const&{
		return data;
	    }


};

template<typename T>
smatrix<T> matmul(smatrix<T> const& m1, smatrix<T> const& m2, int l){
    //int const len=static_cast<int>(m1.size());
    T sum=0;
    int n=l*l;
    smatrix<T> u(l);
    if(static_cast<int>(m2.dimension())!=static_cast<int>(m1.dimension())){
        std::cout<<"Multiplication error"<<std::endl;
        return u;
    }
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++){
            sum=0;
            for(int k=0; k<l; k++){
                sum+=(m1(i,k))*(m2(k,j));
            }
            u(i,j)=sum;
        }
    }
    return u;
}


//Addition

template<typename T>
smatrix<T> operator+(smatrix<T> const& m1, smatrix<T> const& m2){
    smatrix<T> result(m1.dimension());
    detail::transform_matrix2(m1, m2, result, add);
    return result;
}

template<typename T>
smatrix<T>&& operator+( smatrix<T>&& m1, smatrix<T>const& m2){
    detail::transform_matrix2(m1,m2,m1,add);
    return std::move(m1);
}

template<typename T>
smatrix<T>&& operator+( smatrix<T>const& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m2,add);
    return std::move(m2);
}

template<typename T>
smatrix<T>&& operator+( smatrix<T>&& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m1,add);
    return std::move(m1);
}

//Subtraction

template<typename T>
smatrix<T> operator-(smatrix<T> const& m1, smatrix<T> const& m2){
    smatrix<T> result(m1.dimension());
    detail::transform_matrix2(m1, m2, result, sub);
    return result;
}

template<typename T>
smatrix<T>&& operator-( smatrix<T>&& m1, smatrix<T>const& m2){
    detail::transform_matrix2(m1,m2,m1,sub);
    return std::move(m1);
}

template<typename T>
smatrix<T>&& operator-( smatrix<T>const& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m2,sub);
    return std::move(m2);
}

template<typename T>
smatrix<T>&& operator-( smatrix<T>&& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m1,sub);
    return std::move(m1);
}

//Scalar Multiplication
template<typename T>
smatrix<T> operator*(T const& c, smatrix<T> const& m){
    smatrix<T> result(m.dimension());
    detail::transform_matrix2(m, result, [c](T const& x){return c*x;});
    return result;
}

template<typename T>
smatrix<T>&& operator*(T const& c, smatrix<T>&& m){
    detail::transform_matrix1(m, m, [c](T const& x){return c*x;});
    return std::move(m);
}

template<typename T>
smatrix<T> operator*(smatrix<T> const& m, T const& c){
    smatrix<T> result(m.dimension());
    detail::transform_matrix2(m, result, [c](T const& x){return c*x;});
    return result;
}

template<typename T>
smatrix<T>&& operator*(smatrix<T>&& m, T const& c){
    detail::transform_matrix1(m, m, [c](T const& x){return c*x;});
    return std::move(m);
}


//Division

template<typename T>
smatrix<T> operator/(smatrix<T> const& m, T const& c){
    smatrix<T> result(m.dimension());
    detail::transform_matrix1(m, result, [c](T const& x){return x/c;});
    return result;
}

template<typename T>
smatrix<T>&& operator/(smatrix<T>&& m, T const& c){
    detail::transform_matrix1(m.data, m.data, [c](T const& x){return x/c;});
    return std::move(m);
}


template<typename T>
int matmul2(smatrix<T>& m1, smatrix<T>& m2, int hlp){
    int n = m1.dimension();
    std::vector<T> temp(n);
    if(hlp == 1){
        for(int i = 0; i <  n; i++){
            for(int j = 0; j < n; j++){
                double temp_d  = 0;
                for(int k = 0; k < n; k++){
                    temp_d += m1(i, k) * m2(k, j);
                }
                temp[j] = temp_d;
            }
            for(int j = 0; j < n; j++){
                m1(i, j) = temp[j];
            }
        }
        return 0;
    }
    else if(hlp == 2){
        for(int i = 0; i <  n; i++){
            for(int j = 0; j < n; j++){
                double temp_d  = 0;
                for(int k = 0; k < n; k++){
                    temp_d += m1(j, k) * m2(k, i);
                }
                temp[j] = temp_d;
            }
            for(int j = 0; j < n; j++){
                m2(j, i) = temp[j];
            }
        }
        return 0;
    }
    return -1;
}

//Matrix Multiplication

template<typename T>
smatrix<T>& smatrix<T>::operator*=(smatrix<T> const& m){
           smatrix<T> u=matmul(*this, m, m.dimension());
           *this=u;
           return *this;
}

template<typename T>
smatrix<T> operator*(smatrix<T> const& m1, smatrix<T> const& m2){
    smatrix<T> v = matmul(m1, m2, m1.dimension());
    return v;
}

template<typename T>
smatrix<T>&& operator*(smatrix<T> && m1, smatrix<T> & m2){
    if(matmul2(m1, m2, 1) != 0){
        std::cout<<"Matrix multiplication error!"<<std::endl;
    }
    return std::move(m1);
}

template<typename T>
smatrix<T>&& operator*(smatrix<T> & m1, smatrix<T>&& m2){
    if(matmul2(m1, m2, 2) != 0){
        std::cout<<"Matrix multiplication error!"<<std::endl;
    }
    return std::move(m2);
}

template<typename T>
smatrix<T>&& operator*(smatrix<T> && m1, smatrix<T>&& m2){ 
    if(matmul2(m1, m2, 1) != 0){
        std::cout<<"Matrix multiplication error!"<<std::endl;
    }
    return std::move(m1);
}

template<typename T>
std::ostream& operator<<(std::ostream& o, smatrix<T> const& m){
    o<<m.dimension()<<';';
    int n={m.dimension()};
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            o<<m(i,j)<<',';
        }
    }
    return o;
}

template<typename T>
std::istream& operator>>(std::istream& s, smatrix<T>& m){
    auto rewind = [state = s.rdstate(), pos = s.tellg(), &s](){s.seekg(pos); s.setstate(state);};
    std::string temp_string;
    std::getline(s, temp_string);
    if(!s){rewind(); std::cout<<"Read error!"<<std::endl; return s;}
    std::stringstream ss(temp_string);
    if(!ss){rewind(); std::cout<<"Read error!"<<std::endl; return s;}
    std::getline(ss, temp_string, ';');
    if(static_cast<int>(temp_string.size()) > 0){
        int dim = std::stoi(temp_string);
        std::vector<T> temp_vec;
         for(int i = 0; i < dim * dim; i++){
            std::getline(ss, temp_string, ',');
            if(static_cast<int>(temp_string.size()) > 0){
                std::stringstream temp_ss(temp_string);
                T temp;
                temp_ss >> temp;
                temp_vec.push_back(temp);
            }
            else{
                rewind();
                std::cout<<"Dimension error!1"<<std::endl;
                return s;
            }
        }
        if(dim * dim == static_cast<int>(temp_vec.size())){
            m.data = std::move(temp_vec);
            m.l = dim;
        }
        else{
            rewind();
            std::cout<<"Dimension error!2"<<std::endl;
        }
    }
    else{
        rewind();
        std::cout<<"Dimension error!3"<<std::endl;
    }
    return s;
    
    }

    template<typename T>
    bool matr_not_eq(smatrix<T> const& m1, smatrix<T> const& m2, double err){
        int n=m1.dimension();
        if(n!=m2.dimension() || m1.size()!=n*n || m2.size() != n*n){
            return true;
        }
        for(int i=0; i<n*n; i++){
            if(std::abs(m1[i]-m2[i])>err){
                return true;
            }
        }
        return false;

    }