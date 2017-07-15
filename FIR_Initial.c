#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FIR(float* coeffs, float* inputs, float* outputs, int n_coeffs, int n_inputs)
{
    int n;
    for (n = 0; n < n_inputs+n_coeffs-1; n++)
    {
        int k;
        float acc = 0;
        for (k = 0; k < n_coeffs; k++)
        {
            int j = n - k;
            if (j >= 0 && j < n_inputs)
            {
                acc += coeffs[k] * inputs[j];
            }
        }

        outputs[n] = acc;
        printf("Output %d: %f\n", n+1, outputs[n]);
    }
}

int main(int argc, char* argv[])
{
    // Error handling
    if (argc != 3)
    {
        printf("Usage: %s real_coeffs.txt real_input.txt", argv[0]);
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
            printf("Coeff %d: %f\n", i+1, coeffs[i]);
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
        float inputs[n_inputs];

        printf("Input Size: %d\n", n_inputs);

        int j;
        for (j = 0; j < n_inputs; j++)
        {
            char tmp[7];
            fgets(tmp, 7, fp_inputs);
            inputs[j] = atof(tmp);
            printf("Input %d: %f\n", j+1, inputs[j]);
        }

        // Pass values into FIR filter
        float outputs[n_inputs+n_coeffs-1];
        FIR(coeffs, inputs, outputs, n_coeffs, n_inputs);
    }

    return 0;
}