# include <stdio.h>
# include <math.h>

double f(double t, double y) {
    return y - t * t + 1;
}

void rk45(double t0, double y0, double t_end, double h, double epsilon) {
  	
	FILE *fptr_s;
	fptr_s = fopen("20240809_example_rk45.txt","w");

    double t = t0;
    double y = y0;
    int step = 0;

    while (t < t_end) {
        if (t + h > t_end) {
            h = t_end - t;
        }

        double k1 = h * f(t, y);
        double k2 = h * f(t + h / 4, y + k1 / 4);
        double k3 = h * f(t + 3 * h / 8, y + 3 * k1 / 32 + 9 * k2 / 32);
        double k4 = h * f(t + 12 * h / 13, y + 1932 * k1 / 2197 - 7200 * k2 / 2197 + 7296 * k3 / 2197);
        double k5 = h * f(t + h, y + 439 * k1 / 216 - 8 * k2 + 3680 * k3 / 513 - 845 * k4 / 4104);
        double k6 = h * f(t + h / 2, y - 8 * k1 / 27 + 2 * k2 - 3544 * k3 / 2565 + 1859 * k4 / 4104 - 11 * k5 / 40);

        double w1 = y + 25 * k1 / 216 + 1408 * k3 / 2565 + 2197 * k4 / 4104 - k5 / 5;
        double w2 = y + 16 * k1 / 135 + 6656 * k3 / 12825 + 28561 * k4 / 56430 - 9 * k5 / 50 + 2 * k6 / 55;

        double R = fabs(w1 - w2) / h;
        double delta = 0.84 * pow(epsilon / R, 0.25);

        if (R <= epsilon) {
            t += h;
            y = w1;
            step++;
            fprintf(fptr_s,"Step %d: t = %6.4f, y = %18.15f\n", step, t, y);
        }
        h *= delta;
    }

    fclose(fptr_s);
}


int main(){

  double t0 = 0.0;
  double y0 = 0.5;
  double t_end = 2.0;
  double h = 0.2;
  double epsilon = 0.00001;

  rk45(t0, y0, t_end, h, epsilon);

	return 0;
}