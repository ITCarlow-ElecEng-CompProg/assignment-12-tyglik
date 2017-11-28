/** Lab 12 - Complex Number Calculator
 *
 * Martina Nunvarova
 * 27/11/2017
 */

 ///includes
#include <iostream>
#include <math.h>

///namespace
using namespace std;

///Define the data structure
struct struCplx {
    double Re,Im;
};

///Complex Addition: cpxAdd(cA,cB,&cR);
/// cR = cA + cB
void cplxAdd(struCplx cA, struCplx cB, struCplx *cR)
{
    cR->Re=cA.Re+cB.Re;     ///Add Real
    cR->Im=cA.Im+cB.Im;     ///Add Imaginary
}

///Complex Subtraction: cpxSub(cA,cB,&cR);
/// cR = cA - cB
void cplxSub(struCplx cA, struCplx cB, struCplx *cR)
{
    cB.Re=-cB.Re;           ///Make the cB negative
    cB.Im=-cB.Im;
    cplxAdd(cA,cB,cR);      ///Add cA + cB, since cB => -cB ... cA + cB => cA - cB
}

///Complex Multiplication: cpxMul(cA,cB,&cR);
/// cR = cA * cB
void cplxMul(struCplx cA, struCplx cB, struCplx *cR)
{
    double m,a;             ///define local scope variables for magnitude and angle

    m=sqrt(cA.Re*cA.Re+cA.Im*cA.Im) * sqrt(cB.Re*cB.Re+cB.Im*cB.Im);    ///multiply the magnitudes
    a=atan2(cA.Im,cA.Re) + atan2(cB.Im,cB.Re);                          ///add the angles

    cR->Re=cos(a)*m;                                                    ///Convert to Cartesian form
    cR->Im=sin(a)*m;
}

///Complex Division: cpxDiv(cA,cB,&cR);
/// cR = cA / cB
void cplxDiv(struCplx cA, struCplx cB, struCplx *cR)
{
    double m,a;             ///define local scope variables for magnitude and angle

    m=sqrt(cA.Re*cA.Re+cA.Im*cA.Im)/sqrt(cB.Re*cB.Re+cB.Im*cB.Im);      ///divide the magnitudes
    a=(atan2(cA.Im,cA.Re)-atan2(cB.Im,cB.Re));                          ///subtract the angles

    cR->Re=cos(a)*m;                                                    ///Convert to Cartesian
    cR->Im=sin(a)*m;
}

///Complex number printout: cpxOut(cX);
/// prints in the format of: <real> [+/-] j<imaginary>
/// example  7.5 - j2  or   2 + j0.05
void cplxOut(struCplx x)
{
    char tmp;                                   ///temporary char variable for the sign symbol

    if (x.Im<0) {                               ///negative imaginary
        tmp='-';                                ///will print "-"
        x.Im*=-1;                               ///and invert the number to positive for printing
    } else
        tmp='+';                                ///just print the "+" sign

    cout << x.Re << " "<<tmp << " j" << x.Im;   ///Print it out
}

///Complex number input: getCplx(&cX);
/// user input parsing of : <real> [+/-] j<imaginary>  => returned in cX
void getCplx(struCplx *x)
{
    char sgn,j;                                 /// temporary input characters to allow input in form: "7-j4"

    cin >>x->Re>>sgn>>j>>x->Im;                 ///read it in
    if (sgn=='-')                               ///if negative,
        x->Im*=-1;                              ///save it as negative
}

/// Main function
int main(void)
{
    const char ops[4]={'+','-','*','/'};        ///define operations codes for quicker print out of results
    struCplx a,b,z[4];                          /// 2 simple complex numbers and an array of 4 results
    int i;                                      /// loop variable for result printout loop

    cout <<"Complex number calculator"<<endl<<endl<<endl;       /// tell user what's going on

    cout << "Enter a complex number (eg: 1+j2, 2-j4):";         ///ask for 1st number
    getCplx(&a);                                                 ///Get it
    cout << "Enter a second complex number (eg: 1+j2, 2-j4):";  ///ask for 2nd number
    getCplx(&b);                                                 ///Get it

    cplxAdd(a,b,&z[0]);                                         ///add them
    cplxSub(a,b,&z[1]);                                         ///subtract them
    cplxMul(a,b,&z[2]);                                         ///mutiply them
    cplxDiv(a,b,&z[3]);                                         ///divide them

    cout.precision(2);                                          ///set precision
    cout <<endl<<endl<<"Results:"<<endl<< std::fixed;           ///and start printing

    for (i=0;i<4;i++) {                                         ///print all four results
        cout <<"( ";
        cplxOut(a);
        cout << " ) "<<ops[i]<<" ( ";
        cplxOut(b);
        cout << " ) = ";
        cplxOut(z[i]);
        cout <<endl;
    }

    return 0;                                                   ///back to OS, return no error
}

