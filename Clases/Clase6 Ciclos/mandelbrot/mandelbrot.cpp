/*Compute the area of the mandelbrot set.
 *A point inside the set is one for which
 *the iterative application of a cuadratic map
 *q_c(z) does not exceed certain value (in this
 *case |z|<2.
 */

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <complex>
#include <omp.h>
using namespace std;


const int MAX_ITER = 1000;
const double MIN_RE = -2.;
const double MAX_RE = 1.;
const double MIN_IM = -1.;
const double MAX_IM = 1.;



bool is_in(const complex<double>& c) {
  complex<double> z(0,0);
  for(int i = 0; i < MAX_ITER; ++i){
    z = z*z + c;
    //printf("(%f,%f)\n",z.real(),z.imag());
    if(norm(z) > 4)
      return false;
  }
  return true;
}

long mandelbrot(int* A, int nrows, int ncols, double xlim[2],
		double ylim[2]) {
  double stepx = (xlim[1] - xlim[0]) / ncols;
  double stepy = (ylim[1] - ylim[0]) / nrows;
  long noutside = 0;
  #pragma omp parallel
  {
      #pragma omp for collapse(2), schedule(auto) ,reduction(+ :noutside)
      for(int i = 0; i < nrows; ++i){
        for(int j = 0; j < ncols; ++j){
          complex<double> c(stepx*j+xlim[0], stepy*i+ylim[0]);
          bool test = is_in(c);
          if(test){
    	A[i*ncols+j] = 1;
          }else{
    	A[i*ncols+j] = 0;
    	noutside++;
          }
        }
      }
  }
  return noutside;
  }


void print_out(const int* A, int nrows, int ncols) {
  ofstream Out("mandelbrot.dat");
  for(int i = 0; i < nrows; ++i){
    for(int j = 0; j < ncols; ++j)
      Out << A[i*ncols+j] << " ";
    Out << endl;
  }
  Out.close();
}


int main(int argc, char** argv) {
  int nrows = atoi(argv[1]);
  int ncols = atoi(argv[2]);

  double xlim[2] = {MIN_RE, MAX_RE};
  double ylim[2] = {MIN_IM, MAX_IM};

  int* A = new int[nrows*ncols];

  double t_start = omp_get_wtime();
  long nout = mandelbrot(A, nrows, ncols, xlim, ylim);
  double t_stop = omp_get_wtime();

  print_out(A, nrows, ncols);

  delete[] A;

  double a = (xlim[1]-xlim[0]) * (ylim[1]-ylim[0]);
  double tot = nrows*ncols ;
  double m_area = a * (tot-nout) / (nrows*ncols);

  printf("Area: %f\n",m_area);
  printf("Time: %f\n",t_stop-t_start);

  return 0;
}
