#include <stdio.h>
#define NUM 1024
#define COUNT 10
int A[NUM][NUM];
void main (void) {
    int i, j, k;
    for (k = 0; k < COUNT; k++)
        for (i = 0; i < NUM; i++)
            for (j = 0; j < NUM; j++)
                A[j][i] = i + j;
    printf("%d count computing over!\n", i * j * k);
}
