#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Optimizations:
// 1. Restrict arrays to promise unique memory locations
void FIR(uint8_t* __restrict coeffs, int8_t* __restrict inputs, int8_t* __restrict outputs, int n_coeffs, int n_inputs, int n_outputs)
{
    /*
    A fixed point arithmetic implementation of an FIR filter.
    This version of the filter takes the following as input:
        8-bit signed integer inputs
        8-bit unsigned integer coefficients
    
    All coefficients must add up to less than 256 to avoid overflow.
    
    Input Range: -128 to 128
    Coeff Range: 0 to 256
    */

    // Optimizations:
    // 1. Request registers for commonly accessed values
    register int n, k, j;
    register int16_t acc;

    // Loop over the number of outputs to be generated
    // Optimizations:
    //  1. n ^= n         : 1 Cycle
    //  2. n != n_outputs : 1 Cycle
    for (n ^= n; n != n_outputs; n++)
    {
        acc = 0;

        // Loop over the number of coefficients
        // Optimizations:
        //  1. k ^= k        : 1 Cycle
        //  2. k != n_coeffs : 1 Cycle
        for (k ^= k; k != n_coeffs; k++)
        {
            j = n - k;

            // Multiply and accumulate for valid input range
            // Optimizations:
            // 1. Enforce MAC operations by compiling with -O3
            if (j >= 0 && j < n_inputs)
            {
                acc += coeffs[k] * inputs[j];
            }
        }

        // Store the result in the output array
        // Optimizations:
        // 1. Increase precision by introducing rounding
        outputs[n] = ((acc >> 6) + 1) >> 1;
    }
}

int main(int argc, char* argv[])
{
    // Error handling
    if (argc != 3)
    {
        printf("Usage: %s coeffs.txt input.txt\n", argv[0]);
    }
    else
    {
        // Open coefficients file and store in array
        FILE* fp_coeffs;
        char* coeffs_file_name = argv[1];
        fp_coeffs = fopen(coeffs_file_name, "r");

        if (!fp_coeffs)
        {
            printf("Error opening coefficients file.\n");
        }

        char coeffs_size[6];
        fgets(coeffs_size, 6, fp_coeffs);
        int n_coeffs = atoi(coeffs_size);
        uint8_t coeffs[n_coeffs];

        printf("Coeff Size: %d\n", n_coeffs);

        int i;
        for (i = 0; i < n_coeffs; i++)
        {
            char tmp[6];
            fgets(tmp, 6, fp_coeffs);
            coeffs[i] = (uint8_t)(atoi(tmp));
            printf("Coeff %d: %d\n", i, coeffs[i]);
        }

        // Open inputs file and store in array
        FILE* fp_inputs;
        char* inputs_file_name = argv[2];
        fp_inputs = fopen(inputs_file_name, "r");

        if (!fp_inputs)
        {
            printf("Error opening inputs file.\n");
        }

        char inputs_size[8];
        fgets(inputs_size, 8, fp_inputs);
        int n_inputs = atoi(inputs_size);
        int8_t inputs[n_inputs];

        printf("Input Size: %d\n", n_inputs);

        int j;
        for (j = 0; j < n_inputs; j++)
        {
            char tmp[7];
            fgets(tmp, 7, fp_inputs);
            inputs[j] = (int8_t)(atoi(tmp));
            printf("Input %d: %d\n", j, inputs[j]);
        }

        // Pass values into FIR filter
        int n_outputs = n_inputs + n_coeffs - 1;
        int8_t outputs[n_outputs];

        clock_t start, end;
        start = clock();
        FIR(coeffs, inputs, outputs, n_coeffs, n_inputs, n_outputs);
        end = clock();

        // Display the results
        int k;
        for (k = 0; k < n_outputs; k++)
        {
            printf("Output %d: %d\n", k, outputs[k]);
        }

        // Display the time taken
        printf("Time Taken: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    }

    return 0;
}