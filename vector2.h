#include<cmath>
#include<vector>
#include<iostream>

template<typename T>
struct Vector2
{
    T x,y;

    Vector2<T>& operator+=( Vector2<T> const& v){
        x+=v.x; y+=v.y;
        return *this;
    }

    Vector2<T>& operator*=(T const& a){
        x*=a; y*=a;
        return *this;
    }

    Vector2<T>& operator/=(T const& a){
        x/=a; y/=a;
        return *this;
    }
};

template<typename T>
Vector2<T> operator+(Vector2<T> const& a, Vector2<T> const& b){
    return Vector2<T>{a.x+b.x, a.y+b.y};
}

template<typename T>
Vector2<T> operator*(Vector2<T> const& a, T const& b){
    return Vector2<T>{a.x*b, a.y*b};
}

template<typename T>
Vector2<T> operator*(T const& a, Vector2<T> const& b){
    return Vector2<T>{a*b.x, a*b.y};
}

template<typename T>
Vector2<T> operator/(Vector2<T> const& a, T const& b){
    return Vector2<T>{a.x/b, a.y/b};
}

template<typename T>
T dot(Vector2<T> const& u, Vector2<T> const& v){
    return u.x*v.x+u.y*v.y;
}

template<typename T>
double sqlen(Vector2<T> const& v){
    return v.x*v.x+v.y*v.y;
}

template<typename T>
double len(Vector2<T> const& v){
    return sqrt(sqlen(v));
}

template<typename T>
Vector2<T> normalize(Vector2<T> const& v){
    Vector2<T> u;
    u.x=v.x*1/len(v);
    u.y=v.y*1/len(v);
}

template<typename T>
std::ostream& operator<<(std::ostream& o, Vector2<T> const& v){
    o<<v.x <<"   "<<v.y;
    return o;
}

template<typename T>
std::istream& operator>>(std::istream& i, Vector2<T>& v){
    i>>v.x;i>>v.y;
    return i;
}


