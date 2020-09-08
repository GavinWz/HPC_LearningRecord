#include<stdio.h>
#include<omp.h>

double f(double x){
    return x * x;
}

double trap(double a, double b, int n, double h){
    printf("a = %f, b = %f, n = %d, h = %lf ", a,b,n,h);
    double approx = (f(a) + f(b)) / 2;
    for(int i = 0; i < n; i++){
        double x_i = a + i * h;
        approx += f(x_i);
    }
    approx *= h;
    printf("approx = %lf", approx);
    return approx;
}

int main(){
    double a = 0, b = 8;
    int n = 800;
    int num_thread = 8;
    int local_n = n / num_thread;
    double h = (b - a) / n;
    double result = 0.0;
    #pragma omp parallel num_threads(num_thread)
    {
        int procs = omp_get_thread_num();
        double local_a = a + procs * local_n * h;
        double local_b = local_a + local_n * h;
        double pro = trap(local_a, local_b, local_n, h);
        // printf("%d", pro);
        result += pro;
        printf("  %lf\n", result);
    }
    printf("%lf",result);
}