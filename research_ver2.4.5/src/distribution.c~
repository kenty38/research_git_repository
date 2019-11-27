
#include"function.h"

//0~1の乱数
double Uniform(void){
	return ((double)rand()+1.0)/((double)RAND_MAX+2.0);
}

double rand_normal(double mu,double sigma){
	double z=sqrt(-2.0*log(Uniform()))*sin(2.0*M_PI*Uniform());
	return mu+sigma*z;
}

double rand_lnormal(double mu,double sigma){
	double z=mu+sigma*sqrt(-2.0*log(Uniform()))*sin(2.0*M_PI*Uniform());
	return exp(z);
}

double rand_Igauss( double mu, double lambda){
   double x,y,w,z;
   x=sqrt(-2.0*log(Uniform()))*sin(2.0*M_PI*Uniform());//normal random number
   y=x*x; //chi-squared
   w= mu + 0.5*y*mu*mu/lambda -(0.5*mu/lambda)*sqrt(4.0*mu*lambda*y+mu*mu*y*y);
   z=Uniform();

   if( z< mu/(mu+w) )   return w;
   else                return mu*mu/w;
}

double poisson(double lambda){
    double a, b;
    int k = 0;
    a = Uniform();
    b = exp(-lambda);
    while(a>=b){
        a *= Uniform();
        k++;
    }
    return k;
}
