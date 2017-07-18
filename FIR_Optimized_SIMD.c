#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <arm_neon.h>

void FIR(int8_t* coeffs, int8_t* inputs, int8_t* outputs, int n_coeffs, int n_inputs, int n_outputs)
{
    /*
    A fixed point arithmetic implementation of an FIR filter.
    This version of the filter takes the following as input:
        8-bit signed integer inputs
        8-bit signed integer coefficients
    
    Input Range: -128 to 128
    Coefficient Range: 0 to 128
    */

    int n, k, j;
    int16_t acc;

    // Vector operators
    int8x8_t coeffs_vec;
    int8x8_t  inputs_vec;
    int16x8_t result_vec;

    // Loop over the number of outputs to be generated
    for (n = 0; n < n_outputs; n++)
    {
        acc = 0;
        result_vec = vdupq_n_s16(0);

        // Loop over the number of coefficients
        for (k = 0; k < n_coeffs / 8; k++)
        {
            // Eight vector multiply and accumulate operations in parallel
            coeffs_vec = vld1_s8(&coeffs[k*8]);
            inputs_vec = vld1_s8(&inputs[n - (k+1)*8]);
            result_vec = vmlal_s8(result_vec, coeffs_vec, inputs_vec);
        }

        // Add each vector result to the acc
        acc += vgetq_lane_s16(result_vec, 0);
        acc += vgetq_lane_s16(result_vec, 1);
        acc += vgetq_lane_s16(result_vec, 2);
        acc += vgetq_lane_s16(result_vec, 3);
        acc += vgetq_lane_s16(result_vec, 4);
        acc += vgetq_lane_s16(result_vec, 5);
        acc += vgetq_lane_s16(result_vec, 6);
        acc += vgetq_lane_s16(result_vec, 7);

        // Handle the remaining data with scalar operations
        if (n_coeffs % 8)
        {
            // Loop over the number of coefficients
            for (k = n_coeffs - (n_coeffs % 8); k < n_coeffs; k++)
            {
                acc += coeffs[k] * inputs[n-k];
            }
        }

        // Store the result in the output array
        outputs[n] = (acc >> 7);
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
        int8_t coeffs[n_coeffs];

        printf("Coeff Size: %d\n", n_coeffs);

        int i;
        for (i = 0; i < n_coeffs; i++)
        {
            char tmp[6];
            fgets(tmp, 6, fp_coeffs);
            coeffs[i] = (int8_t)(atoi(tmp));
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

        char inputs_size[6];
        fgets(inputs_size, 6, fp_inputs);
        int n_inputs = atoi(inputs_size);
        int8_t inputs[n_inputs];

        printf("Input Size: %d\n", n_inputs);

        int j;
        for (j = n_inputs; j >= 0; j--)
        {
            char tmp[7];
            fgets(tmp, 7, fp_inputs);
            inputs[j] = (int8_t)(atoi(tmp));
            printf("Input %d: %d\n", j, inputs[j]);
        }

        // Pass values into FIR filter
        int n_outputs = n_inputs + n_coeffs - 1;
        int8_t outputs[n_outputs];
        FIR(coeffs, inputs, outputs, n_coeffs, n_inputs, n_outputs);

        // Display the results
        int k;
        for (k = 0; k < n_outputs; k++)
        {
            printf("Output %d: %d\n", k, outputs[k]);
        }
    }

    return 0;
}