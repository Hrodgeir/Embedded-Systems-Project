#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float coeffs[100];
float input[1000];
float output[1000];

void FIR(float* coeffs, float* input, float* output)
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
       printf("FIR: %0.2f\n", output[i]);
   }
   
   return 0;
}