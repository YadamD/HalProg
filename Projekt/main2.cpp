#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "matr2d.h"

using namespace std;

smatrix<double> arr(char* fname, int ax, int ay){
    ifstream file {fname};
    smatrix<double> m(ax);
    for(int i = 0; i < ax; i++)
            for(int j = 0; j < ay; j++)
                file >> m(i,j);
    return m;}

smatrix<int> addup(int x, int y, smatrix<int> a, smatrix<int> b){
    smatrix<int> sum(x);
    sum=a+b;
    return sum;
}

void write_arr(char* fname, int x, int y, smatrix<double> a){
    ofstream myfile (fname);
    if (myfile.is_open())
        {
            for(int i = 0; i < y; i++){
                for(int j = 0; j < x; j++){
                   myfile << a(i,j) << " " ;

                }
                myfile << endl;
        }
    myfile.close();
  }
  else cout << "Unable to open file";    
}

void write_arr_int(char* fname, int x, int y, smatrix<int> a){

    ofstream myfile (fname);
    if (myfile.is_open())
        {
            for(int i = 0; i < y; i++){
                for(int j = 0; j < x; j++){
                   myfile << a(i,j) << " " ;

                }
                myfile << endl;
        }
    myfile.close();
  }
  else cout << "Unable to open file";    
}

smatrix<int> binary(const int x, const int y, smatrix<double> a, double threshold){
    smatrix<int> newa(x);
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(a(i,j)<threshold){
                newa(i,j)=0;
            }
            else{
                newa(i,j)=1;
            }
        }
    }
    return newa;
}

smatrix<int> msquares(const int x, const int y, smatrix<int> a){
    smatrix<int> ms(x-1);
    for(int i=0; i<x-1; i++){
        for(int j=0; j<y-1; j++){
            ms(i,j)=8*a(i,j)+4*a(i+1,j)+2*a(i+1,j+1)+1*a(i,j+1);
            if(ms(i,j)==15){
                ms(i,j)=0;
            }
        }
    }
    return ms;
}

smatrix<int> combine(smatrix<double> a, int x, int y, vector<double> h){
    smatrix<int> test_comb(x-1);
    for(size_t i=0; i<h.size(); i++){
        smatrix<int> ms;
        ms=msquares(x,y,binary(x,y,a,h[i]));
        test_comb=(addup(x-1,y-1,test_comb,ms));
    }
    return test_comb;
}


vector<int> next_cell(int cellID, int inside){

    int ID2out[15][4] = {{-1,-1,-1,-1},{3,-1,-1,0},{-1,-1,3,2},{2,-1,0,-1},{-1,2,1,-1},{1,0,3,2},{-1,3,-1,1},{1,0,-1,-1},{1,0,-1,-1},{-1,3,-1,1},{3,2,1,0},{-1,2,1,-1},{2,-1,0,-1},{-1,-1,3,2},{3,-1,-1,0}};
    int outside;
    if(inside==-1){
        for(int i=0; i<4; i++){
            if(ID2out[cellID][i]>-1){
                outside=ID2out[cellID][i];
                break;
            }
        }
    }
    else{
        outside=ID2out[cellID][inside];
    }
    int delX[4]={-1,0,1,0};
    int delY[4]={0,1,0,-1};
    int out2in[4]={2,3,0,1};

    vector<int> r{delX[outside],delY[outside], out2in[outside]};
    
    return r;    
}

double wind(int x0, int y0, smatrix<int> a, int x, int y){

    int st=0;
    for(int i=x0; i<x; i++){        
        if(a(i,y0)!=0){
            st=i;
            break;
        }        
    }

    int j =st;
    int k=y0;
    int side=-1;
    vector<int> nxt;
    double deg=0.0;
    int prevx=j-x0;
    int prevy=k-y0;
    int dx,dy;
    double lena;
    double prevlen=j-x0;
    double ss;
    int is5=0;

    do{
        is5+=1;
        nxt=next_cell(a(j,k),side);
        j=j+nxt[0];
        k=k-nxt[1];
        side=nxt[2];
        if(is5==10){
            dx=j-x0;
            dy=k-y0;
            lena=sqrt((dx*dx)+dy*dy);
            ss=dx*prevx+dy*prevy;
            ss=ss/(lena*prevlen);
            deg+=acos(ss);
            prevlen=lena;
            prevx=j-x0;
            prevy=k-y0;
            is5=0;
        }


    }
    while(j!=st || k!=y0);


    return deg;
}


int main(int, char**) {

//smatrix<double> h=arr("hdata.txt",2244,1650);
smatrix<double> h2=arr("hdata2.txt",250,250);

smatrix<int> real_comb=combine(h2,250,250,{800.0,1000.0,1200.0,1400.0});

write_arr_int("h2_matr.txt", 249,249,real_comb);
write_arr("check_matr.txt", 250,250,h2);

double deg=wind(100,100,real_comb,249,249);
cout<<deg;

}
