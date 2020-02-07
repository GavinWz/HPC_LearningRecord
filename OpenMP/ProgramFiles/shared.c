#include<stdio.h>
#include<omp.h>

int main(){
    int cnt = 0;
    #pragma omp parallel for shared(cnt)
    for(int i = 0; i < 10; i++){
        if(i % 2 == 0){
            cnt++;
            printf("cnt = %d\n", cnt);
        }
    }


}