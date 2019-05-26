#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
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
		transform(m1.cbegin(), m1.cend(), m2.begin(), f);
	}

	template<typename M1, typename M2, typename M3, typename F>
	void transform_matrix2(M1 const& m1, M2 const& m2, M3& m3, F f)
	{
		transform(m1.cbegin(), m1.cend(), m2.cbegin(), m3.begin(), f);
	}
}

auto add = [](auto const& x, auto const& y){ return x + y; };
auto sub = [](auto const& x, auto const& y){ return x - y; };


template<typename T>
vector<T> matmul(vector<T> const& m1, vector<T> const& m2, int l){
    int const len=static_cast<int>(m1.size());
    T sum=0;
    int n=l*l;
    vector<T> u(len);
    if(len!=static_cast<int>(m2.size()) || n!=len){
        cout<<"Multiplication error"<<endl;
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

template<typename T>
class smatrix
{
	

    public:
        
        int l;
        vector<T> data;

        smatrix(): l{1}, data{{0}}{};
        smatrix(int i): l(i), data(i*i, 0){};
        smatrix(int i, vector<T> const& v){
            if(i*i!=static_cast<int>(v.size())){
                cout<<"Parameter error!"<<endl;
            }
            else{
                l=i;
                data=v;
            }
        }
        
        smatrix<T>(smatrix<T> const& copy): l{copy.l}, data{copy.data}{
            if(l!=copy.l){
                cout<<"Error with copying"<<endl;
                exit(-1);
            }
        }

        T & operator[](int i){return data[i];}
        T & operator()(int i, int j){return data[l*i+j];}
        
        T const& operator[](int i) const {return data[i];}
        T const& operator()(int i, int j)const {return data[l*i+j];}

        smatrix<T>& operator=(smatrix<T>&&)=default;
        smatrix<T>(smatrix<T>&& o) noexcept : l(exchange(o.l, 0)), data(move(o.data)) {}
        
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

        vector<T> dat() const&{
		return data;
	    }


};

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
    return move(m1);
}

template<typename T>
smatrix<T>&& operator+( smatrix<T>const& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m2,add);
    return move(m2);
}

template<typename T>
smatrix<T>&& operator+( smatrix<T>&& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m1,add);
    return move(m1);
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
    return move(m1);
}

template<typename T>
smatrix<T>&& operator-( smatrix<T>const& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m2,sub);
    return move(m2);
}

template<typename T>
smatrix<T>&& operator-( smatrix<T>&& m1, smatrix<T>&& m2){
    detail::transform_matrix2(m1,m2,m1,sub);
    return move(m1);
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
    return move(m);
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
    return move(m);
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
    return move(m);
}


template<typename T>
int matmul2(smatrix<T>& m1, smatrix<T>& m2, int hlp){
    int n = m1.dimension();
    vector<T> temp(n);
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
smatrix<T> operator*(smatrix<T> const& m1, smatrix<T> const& m2){
    vector<T> v(m1.size());
    v = matmul(m1.dat(), m2.dat(), m1.dimension());
    smatrix<T> temp(m1.dimension(), v);
    return temp;
}

template<typename T>
smatrix<T>&& operator*(smatrix<T> && m1, smatrix<T> & m2){
    if(matmul2(m1, m2, 1) != 0){
        cout<<"Matrix multiplication error!"<<endl;
    }
    return move(m1);
}

template<typename T>
smatrix<T>&& operator*(smatrix<T> & m1, smatrix<T>&& m2){
    if(matmul2(m1, m2, 2) != 0){
        cout<<"Matrix multiplication error!"<<endl;
    }
    return move(m2);
}

template<typename T>
smatrix<T>&& operator*(smatrix<T> && m1, smatrix<T>&& m2){ 
    if(matmul2(m1, m2, 1) != 0){
        cout<<"Matrix multiplication error!"<<endl;
    }
    return move(m1);
}

template<typename T>
ostream& operator<<(ostream& o, smatrix<T> const& m){
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
istream& operator>>(istream& s, smatrix<T>& m){
    auto rewind = [state = s.rdstate(), pos = s.tellg(), &s](){s.seekg(pos); s.setstate(state);};
    string temp_string;
    getline(s, temp_string);
    if(!s){rewind(); cout<<"Read error!"<<endl; return s;}
    stringstream ss(temp_string);
    if(!ss){rewind(); cout<<"Read error!"<<endl; return s;}
    getline(ss, temp_string, ';');
    if(static_cast<int>(temp_string.size()) > 0){
        int dim = stoi(temp_string);
        vector<T> temp_vec;
         for(int i = 0; i < dim * dim; i++){
            getline(ss, temp_string, ',');
            if(static_cast<int>(temp_string.size()) > 0){
                stringstream temp_ss(temp_string);
                T temp;
                temp_ss >> temp;
                temp_vec.push_back(temp);
            }
            else{
                rewind();
                cout<<"Dimension error!1"<<endl;
                return s;
            }
        }
        if(dim * dim == static_cast<int>(temp_vec.size())){
            m.data = move(temp_vec);
            m.l = dim;
        }
        else{
            rewind();
            cout<<"Dimension error!2"<<endl;
        }
    }
    else{
        rewind();
        cout<<"Dimension error!3"<<endl;
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
            if(abs(m1[i]-m2[i])>err){
                return true;
            }
        }
        return false;

    }