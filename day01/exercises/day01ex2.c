#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define SIZE_OF 8  // for double precision
#define SEED 86456

double x[N][N], y[N][N], z[N][N], tx[N][N];
double rate, msec, start, end;

int main() {
    FILE *fptr;

    // use appropriate location if you are using MacOS or Linux
    fptr = fopen("day01ex02data.txt","w");
    if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }
    srand(SEED);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x[i][j] = (double)rand() / RAND_MAX + 1.0;
            y[i][j] = (double)rand() / RAND_MAX + 1.0;
        }
    }
    printf("block size, time (msec), rate\n");

    start = (double)clock() /(double) CLOCKS_PER_SEC;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            z[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                z[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    end = (double)clock() /(double) CLOCKS_PER_SEC;
    msec = (end-start) * 1000.0;
    rate = sizeof(double) * N * (1000.0 / msec) / (1024*1024);
    printf("Not Block, %f, %f,\n", msec,rate);
    fprintf(fptr,"Not Block, %f, %f\n",msec,rate);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            z[i][j] = 0.0;
        }
    }
    
    for(int B=1; B <= 20; B++){
        start = (double)clock() /(double) CLOCKS_PER_SEC;
        for (int ii = 0; ii < N; ii+=B) {
            for (int jj = 0; jj < N; jj+=B) {
                for (int kk = 0; kk < N; kk+=B) {
                    for (int i = ii; i < ii+B; i++) {
                        for (int j = jj; j < jj+B; j++) {
                            for (int k = kk; k < kk+B; k++) {
                                z[i][j] += x[i][k]*y[k][j];
                            }
                        }
                    }
                }
            }
        }
        end = (double)clock() /(double) CLOCKS_PER_SEC;
        msec = (end-start) * 1000.0;
        rate = sizeof(double) * N * (1000.0 / msec) / (1024*1024);
        printf("%d, %f, %f,\n",B, msec, rate);
        fprintf(fptr,"%d, %f, %f\n",B, msec, rate);
    }
    fclose(fptr);

    return 0;
}
