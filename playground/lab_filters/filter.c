// Credit: https://ccrma.stanford.edu/~jos/

/* C function implementing the Matlab filter() function:
 * 
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double filter(double * b, double * a, double * x, double * y, int Nx, int Nm0, int Mn0) {
  
  //int Nx;
  int Nm, Mn; // see jos (3.1) 
  double B, A; // summed B term and A term
  int n, k; //
  
  y[0] = b[0] * x[0];
  
  for ( n = 1; n < Nx; n++ ) {
    
    B = 0, A = 0;
    Mn = ( Mn0 < n ) ? Mn0 : n ;
    Nm = ( Nm0 < n ) ? Nm0 : n ;
    
    for ( k = 0; k < Mn; k++ ) {
      B += b[k] * x[n-k];
    }
    
    for ( k = 1; k < Nm; k++ ) {
      A += a[k] * y[n-k];
    }
    
    y[n] = B - A;
  }
  
  return y[Nx-1];
}

int main() { 
  double x[10] = {1,3,5,7,9,11,9,7,5,3}; 
  double y[10];
  
  double b[4] = {0.25, 0.25, 0.25, 0.25};
  double a[2] = {1, 0};
  
  int i;
  int N = 10;
  
  double xm1 = 0;
  xm1 = filter(b, a, x, y, N, 2, 4);
  
  for (i=0;i<N;i++) {
    printf("x[%d]=%f\ty[%d]=%f\n",i,x[i],i,y[i]);
  }
  
  exit(0);
  
}

