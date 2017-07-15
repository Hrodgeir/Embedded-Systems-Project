#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define N 100

int12_t coeffs[N];
int12_t input[N];
int12_t output[N];

void FIR(int12_t* coeffs, int12_t* input, int12_t* output)
{
    /*
    o: position in output
    c: position in coeffs
    i: position in input
    */
    int o, c, i;
    for (o = 0; o < N; o++)
    {
        for (c = 0; c < N; c++)
        {
            i = o - c;

            if (i >= 0)
            {
                output[c] += coeffs[o] * input[i];
            }
        }
    }
}

int main()
{
   create_file();

   FIR(coeffs, input, output);

   int i;
   for (i = 0; i < N; i++)
   {
       printf("FIR: %d", output[i]);
   }
   
   return 0;
}