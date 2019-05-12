#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



double **arr_gen(const int x, const int y){
    double **m;
    m=new double*[x];
    for(int i=0; i<x; i++){
        m[i]= new double[y];
    }
    return m;
}

int **arr_gen_int(const int x, const int y){
    int **m;
    m=new int*[x];
    for(int i=0; i<x; i++){
        m[i]= new int[y];
    }
    return m;
}

double **arr(char* fname, int ax, int ay){
    ifstream file {fname};
    double **myArray;
    myArray=arr_gen(ax,ay);
        for(int i = 0; i < ax; i++)
            for(int j = 0; j < ay; j++)
                file >> myArray[i][j];
    return myArray;    
}

int **addup(int x, int y, int **a, int **b){
    int **sum;
    sum=arr_gen_int(x,y);
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            sum[i][j]=a[i][j]+b[i][j];
        }
    }
    return sum;
}

void write_arr(char* fname, int x, int y, double** a){

    ofstream myfile (fname);
    if (myfile.is_open())
        {
            for(int i = 0; i < y; i++){
                for(int j = 0; j < x; j++){
                   myfile << a[i][j] << " " ;

                }
                myfile << endl;
        }
    myfile.close();
  }
  else cout << "Unable to open file";    
}


void write_arr_int(char* fname, int x, int y, int** a){

    ofstream myfile (fname);
    if (myfile.is_open())
        {
            for(int i = 0; i < y; i++){
                for(int j = 0; j < x; j++){
                   myfile << a[i][j] << " " ;

                }
                myfile << endl;
        }
    myfile.close();
  }
  else cout << "Unable to open file";    
}

int **binary(const int x, const int y, double **a, double threshold){
    int **newa;
    newa=arr_gen_int(x,y);
    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(a[i][j]<threshold){
                newa[i][j]=0;
            }
            else{
                newa[i][j]=1;
            }
        }
    }
    return newa;
}

int **msquares(const int x, const int y, int **a){
    int **ms;
    ms=arr_gen_int(x-1,y-1);
    for(int i=0; i<x-1; i++){
        for(int j=0; j<y-1; j++){
            ms[i][j]=8*a[i][j]+4*a[i+1][j]+2*a[i+1][j+1]+1*a[i][j+1];
            if(ms[i][j]==15){
                ms[i][j]=0;
            }
        }
    }
    return ms;
}


int **combine(double **a, int x, int y, vector<double> h, int l){
    int **test_comb;
    test_comb=arr_gen_int(x-1,y-1);
    for(int i=0; i<l; i++){
        int **ms;
        ms=msquares(x,y,binary(x,y,a,h[i]));
        test_comb=(addup(x-1,y-1,test_comb,ms));
    }
    return test_comb;
}


int *next_cell(int cellID, int inside){

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

    int *r;
    r=new int[3] {delX[outside],delY[outside], out2in[outside]};

    return r;    
}

double wind(int x0, int y0, int **a, int x, int y){

    int st=0;
    for(int i=x0; i<x; i++){        
        if(a[i][y0]!=0){
            st=i;
            break;
        }        
    }

    int j =st;
    int k=y0;
    int side=-1;
    int *nxt;
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
        nxt=next_cell(a[j][k],side);
        //cout << j <<", "<<k<<", "<<a[j][k]<<", "<<side<<", "<<nxt[0]<<", "<<nxt[1]<<", "<<nxt[2]<<"\n"<<flush;
        j=j+nxt[0];
        k=k-nxt[1];
        side=nxt[2];
        //cout <<"---"<< j <<", "<<k<<", "<<a[j][k]<<", "<<side<<", "<<nxt[0]<<", "<<nxt[1]<<", "<<nxt[2]<<"\n"<<flush;
        if(is5==10){
            dx=j-x0;
            dy=k-y0;
            lena=sqrt((dx*dx)+dy*dy);
            ss=dx*prevx+dy*prevy;
            ss=ss/(lena*prevlen);
            cout<<ss<<"\n"<<flush;
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

cout << "Hello, world!\n";

double **h=arr("hdata.txt",2244,1650);
double **h2=arr("hdata2.txt",250,250);

int **h2_1000=binary(250,250,h2,1000.0);
int **ms_h2_1000=msquares(250,250,h2_1000);

int **h2_800=binary(250,250,h2,800.0);
int **ms_h2_800=msquares(250,250,h2_800);

int **h2_1200=binary(250,250,h2,1200.0);
int **ms_h2_1200=msquares(250,250,h2_1200);

int **h2_1400=binary(250,250,h2,1400.0);
int **ms_h2_1400=msquares(250,250,h2_1400);

int **test_combined=addup(249,249,ms_h2_1000,ms_h2_800);
int **test_combined2=addup(249,249,test_combined, ms_h2_1200);
int **comb=addup(249,249,test_combined2, ms_h2_1400);


/*vector<double> lst={800.0,1200.0,1400.0};
double **comb=combine(h2,250,250,lst,3);*/
  
write_arr_int("h2.txt", 249,249,comb);
write_arr("check.txt", 250,250,h2);

double deg=wind(100,100,comb,249,249);
cout<<deg;

}
