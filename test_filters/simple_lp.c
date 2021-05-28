// Credit: https://ccrma.stanford.edu/~jos/

/* C function implementing the simplest lowpass:
 * 
 *      y(n) = x(n) + x(n-1)
 *
 *
 * M: block size
 * xm1: the filter's state
 */

#include <stdio.h>
#include <stdlib.h>

double simplp (double *x, double *y, int M, double xm1) {
  int n;
  y[0] = x[0] + xm1;
  for (n=1; n < M ; n++) {
    y[n] =  x[n]  + x[n-1];
  }
  return x[M-1];
}

int main() { 
  double x[10] = {1,2,3,4,5,6,7,8,9,10}; 
  double y[10];

  int i;
  int N = 10;
  int M = N/2; /* block size */
  double xm1 = 0;

  xm1 = simplp(x, y, M, xm1);
  xm1 = simplp(&x[M], &y[M], M, xm1);

  for (i=0;i<N;i++) {
    printf("x[%d]=%f\ty[%d]=%f\n",i,x[i],i,y[i]);
  }
  
  exit(0);
  
}

