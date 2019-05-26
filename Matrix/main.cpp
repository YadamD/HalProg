#include <iostream>
#include "matr2D.h"

using namespace std;

int main(int, char**) {
    cout.precision(6);
    

    auto msg = [](auto str){cout << "matr2d.h error in: " << str << "\n"; exit(-1); };

    //Test default constructor
    {
        smatrix<double> m;
        if(m.size() != 1)         { msg("default contructor test [size]");           }
        if(m.dimension() != 1)    { msg("default contructor test [dimension]");      }
        if(++(m.begin()) != m.end())  { msg("default contructor test [begin == end]");   }
        if(++(m.cbegin()) != m.cend()){ msg("default contructor test [cbegin == cend]"); }
    }
    //Test list initialization and indexing:
    {
        smatrix<double> mt(2,{1.1, 2.2, 3.3, 4.4});
        if(mt.size() != 4)                                                      { msg("initializer list constructor test [size]");               }
        if(mt.dimension() != 2)                                                 { msg("initializer list constructor test [dimension]");          }
        if(mt[0] != 1.1 || mt[1] != 2.2 || mt[2] != 3.3 || mt[3]!=4.4)          { msg("initializer list constructor test [indexing with []]");   }
        if(mt(0,0) != 1.1 || mt(0,1) != 2.2 || mt(1,0) != 3.3 || mt(1,1)!=4.4)  { msg("initializer list constructor test [indexing with ()]");   }
        if( ++ ++ ++ ++(mt.begin()) != mt.end() )                               { msg("initializer list constructor test [begin + 4 == end]");   }
		if( ++ ++ ++ ++(mt.cbegin()) != mt.cend() )                             { msg("initializer list constructor test [cbegin + 4 == cend]"); }
    }
    //Test copy constructor
    {
        smatrix<double> a(2,{1.1, 2.2, 3.3, 4.4});
        smatrix<double> b{a};
        if(b.size() != 4)                                           { msg("copy constructor test [size]");               }
        if(b.dimension() != 2)                                      { msg("copy constructor test [dimension]");          }
        if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3]!=4.4)  { msg("copy constructor test [elements]");           }
        if( ++ ++ ++ ++(b.begin()) != b.end() )                     { msg("copy constructor test [begin + 4 == end]");   }
		if( ++ ++ ++ ++(b.cbegin()) != b.cend() )                   { msg("copy constructor test [cbegin + 4 == cend]"); }
        if(a.size() != 4)                                           { msg("copy constructor test [src size]");           }
        if(a[0] != 1.1 || a[1] != 2.2 || a[2] != 3.3 || a[3] != 4.4){ msg("copy constructor test [src elements]");       }
    }
    //Test move constructor
    {
        smatrix<double> a(2, {1.1, 2.2, 3.3, 4.4});
        smatrix<double> b{move(a)};
        if(a.size() != 0)                                           { msg("move constructor test [src size]");             }
        if(a.dimension() != 0)                                      { msg("move constructor test [src dimension]");        }
        if(a.begin() != a.end())                                    { msg("move constructor test [src begin == src end]"); }
        if(b.size() != 4)                                           { msg("move constructor test [size]");                 }
        if(b.dimension() != 2)                                      { msg("move constructor test [dimension]");            }
        if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] !=4.4) { msg("move constructor test [elements]");             }
        if( ++ ++ ++ ++(b.begin()) != b.end() )                     { msg("move constructor test [begin + 4 == end]");     }
        if( ++ ++ ++ ++(b.cbegin()) != b.cend() )                   { msg("move constructor test [cbegin + 4 == cend]");   }
    }

    //Test assignment:
	{
		smatrix<double> a(2, {1.1, 2.2, 3.3, 4.4});
		smatrix<double> b;
		b = a;
		if(b.size() != 4)                                           { msg("assignment test [size]");                     }
        if(b.dimension() != 2)                                      { msg("assignment test [dimension]");                }
        if(b[0] != 1.1 || b[1] != 2.2 || b[2] != 3.3 || b[3] !=4.4) { msg("assignment test [elements]");                 }
		if(a.size() != 4)                                           { msg("assignment test [src size]");                 }
        if(a.dimension() != 2)                                      { msg("assignment test [src dimension]");            }
        if(a[0] != 1.1 || a[1] != 2.2 || a[2] != 3.3 || a[3] !=4.4) { msg("assignment test [src elements]");             }
	}

    //Test self assignment:
	{
		smatrix<double> c(2, {1.1, 2.2, 3.3, 4.4});
		c = c;
		if(c.size() != 4)                                           { msg("self assignment test [size]");     }
        if(c.dimension() != 2)                                      { msg("self assignment test [dimension]");}
		if(c[0] != 1.1 || c[1] != 2.2 || c[2] != 3.3 || c[3] !=4.4) { msg("self assignment test [elements]"); }
	}

    //Test self move assignment:
	{
		smatrix<double> c(2,{1.1, 2.2, 3.3, 4.4});
		c=move(c);
		if(c.size() != 4)                                               { msg("self assignment test [size]");     }
		if(c.dimension() != 2)                                          { msg("self assignment test [dimension]");}
        if(c[0] != 1.1 || c[1] != 2.2 || c[2] != 3.3 || c[3] != 4.4)    { msg("self assignment test [elements]"); }
	}

    
    smatrix<double> const m1(3,{123.4,42.42,10.0,32.4,65.7,99.9,1.0,2.0,3.0});
    smatrix<double> const m2(3,{30.12,624.1,142.2,55.55,12.0,12.0,24.5,2.1,400.01});
    smatrix<double> m3(m2);

    double err=1e-9;

    smatrix<double> const madd(3,{153.52,666.52,152.2,87.95,77.7,111.9,25.5,4.1,403.01});
    smatrix<double> const msub(3,{93.28,-581.68,-132.2,-23.15,53.7,87.9,-23.5,-0.1,-397.01});
    smatrix<double> const mmul(3,{6318.239,77543.98,22056.62,7073.073,21219.03,45356.679,214.72,654.4,1366.23});

    if(matr_not_eq(m1+m2,madd,err))  {msg("addition");}    
    if(matr_not_eq(m1-m2,msub,err))  {msg("subtraction");}
    if(matr_not_eq(m1*m2,mmul,err))  {msg("matrix multiplication");}







}

