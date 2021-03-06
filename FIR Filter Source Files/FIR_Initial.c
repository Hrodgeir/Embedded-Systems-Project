#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void FIR(float* coeffs, float* inputs, float* outputs, int n_coeffs, int n_inputs)
{
    /*
    A naive implementation of an FIR filter.
    This version of the filter takes float arrays as inputs to the system.
    
    Input Range: -1.00 to +1.00
    Coefficient Range: 0 to +1.00
    */

    int n;

    // Loop over the number of outputs to be generated
    for (n = 0; n < n_inputs+n_coeffs-1; n++)
    {
        int k;
        float acc = 0;

        // Loop over the number of coefficients
        for (k = 0; k < n_coeffs; k++)
        {
            int j = n - k;

            // Multiply and accumulate for valid input range
            if (j >= 0 && j < n_inputs)
            {
                acc += coeffs[k] * inputs[j];
            }
        }

        // Populate the output at time n
        outputs[n] = acc;
    }
}

int main(int argc, char* argv[])
{
    // Error handling
    if (argc != 3)
    {
        printf("Usage: %s real_coeffs.txt real_input.txt\n", argv[0]);
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
        float coeffs[n_coeffs];

        printf("Coeff Size: %d\n", n_coeffs);

        int i;
        for (i = 0; i < n_coeffs; i++)
        {
            char tmp[6];
            fgets(tmp, 6, fp_coeffs);
            coeffs[i] = atof(tmp);
            printf("Coeff %d: %f\n", i, coeffs[i]);
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
        float inputs[n_inputs];

        printf("Input Size: %d\n", n_inputs);

        int j;
        for (j = 0; j < n_inputs; j++)
        {
            char tmp[7];
            fgets(tmp, 7, fp_inputs);
            inputs[j] = atof(tmp);
            printf("Input %d: %f\n", j, inputs[j]);
        }

        // Pass values into FIR filter
        int n_outputs = n_inputs + n_coeffs - 1;
        float outputs[n_outputs];

        clock_t start, end;
        start = clock();
        FIR(coeffs, inputs, outputs, n_coeffs, n_inputs);
        end = clock();

        // Display the results
        int k;
        for (k = 0; k < n_outputs; k++)
        {
            printf("Output %d: %f = %d\n", k, outputs[k], (int)(outputs[k]*128));
        }

        // Display the time taken
        printf("Time Taken: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    }

    return 0;
}