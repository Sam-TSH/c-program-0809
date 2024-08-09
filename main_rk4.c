# include <stdio.h>
# include <math.h>

double f(double t, double y) {
    return y - t * t + 1;
}


int main(){
	
	FILE *fptr_s;
	fptr_s = fopen("20240809_example3.txt","w");

  double t = 0, w = 0.5;
  double h = 0.05;
  int steps = 40; 
  double k1, k2, k3, k4;

  for (int i = 1; i <= steps; i++) {

    k1 = h * f(t, w);
    k2 = h * f(t + h / 2.0, w + k1 / 2.0);
    k3 = h * f(t + h / 2.0, w + k2 / 2.0);
    k4 = h * f(t + h, w + k3);

    w = w + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
    t = t + h;

		fprintf(fptr_s, "%f ,%f, %f, %f, %f, %f\n",t,k1,k2,k3,k4,w);
	}
	fclose(fptr_s);
	return 0;
}