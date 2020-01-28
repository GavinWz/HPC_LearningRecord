#include<stdio.h>
#include<math.h>

double f(double num){
    return num;
}

double Trap(double a, double b, int n, double h){
    double area = 0;
    for(int i = 0; i <= n-1; i++){
        double add = (f(a+i*h) + f(a+(i+1)*h)) / 2.0 * h;
        printf("%lf\n", add);
        area += add;
    }
    return area;
}

int main(){
    printf("%lf", Trap(0, 32, 32, 1));
}