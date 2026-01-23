#include <stdio.h>
#include <math.h>

double f(double x)
{
    return x * x * x  +1.1*x * x  + 0.9 * x - 1.4;
}
int main()
 {
    double a=0.0;       
    double b=1.0;        
    const double TOL=1e-3; 
    double c;              
    if (fabs(f(a))<TOL) 
    {
        printf("根为:%.6f\n",a);
        return 0;
    } else if (fabs(f(b))<TOL) 
    {
        printf("根为:%.6f\n",b);
        return 0;
    }
    while ((b-a)>TOL) 
    {
        c=(a+b)/2; 
        double fc=f(c); 
        if (fabs(fc)<TOL) 
        {
            break;
        }
        else if (f(a)*fc<0) 
        {
            b=c;
        }
        else 
        {
            a = c;
        }
    }
    c=(a+b)/2;
    printf("方程的实根近似值为: %.6f\n", c);
    printf("函数值验证: f(%.6f) = %.8f\n", c, f(c));
    return 0;
}
