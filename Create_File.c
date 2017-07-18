#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

void write_to_file(float* array, FILE* fpr, FILE* fps, int n, int is_coeffs)
{
    int i;
    for (i = 0; i < n; i++)
    {
        // Generate random float ranging from 0 to 100
        array[i] = (float)((rand() % 101)) / 100;

        // 50% chance that the number will be negative
        // Make sure coeffs are all positive
        if (!is_coeffs && rand() % 2 == 0)
        {
            array[i] *= -1;
        }

        // Write the randomly generated float to the file
        fprintf(fpr, "%0.2f\n", array[i]);

        // Convert the float into an 8 bit representation
        // Range: -1.0 (129 to 256) to +1.0 (0 to 128)
        // Scale Factor: 128

        if (is_coeffs)
        {
            uint8_t scaled = (uint8_t)(roundf(array[i] * 256));
            fprintf(fps, "%d\n", scaled);
        }
        else
        {
            int8_t scaled = (int8_t)(roundf(array[i] * 128));
            fprintf(fps, "%d\n", scaled);
        }
    }

    fclose(fpr);
    fclose(fps);
}

void create_coeffs_files(int n_coeffs)
{
    FILE* fp_real_coeffs;
    fp_real_coeffs = fopen("real_coeffs.txt", "w+");
    fprintf(fp_real_coeffs, "%d\n", n_coeffs);

    FILE* fp_coeffs;
    fp_coeffs = fopen("coeffs.txt", "w+");
    fprintf(fp_coeffs, "%d\n", n_coeffs);

    float real_coeffs[n_coeffs];
    write_to_file(real_coeffs, fp_real_coeffs, fp_coeffs, n_coeffs, 1);
}

void create_inputs_files(int n_inputs)
{
    FILE* fp_real_inputs;
    fp_real_inputs = fopen("real_inputs.txt", "w+");
    fprintf(fp_real_inputs, "%d\n", n_inputs);

    FILE* fp_inputs;
    fp_inputs = fopen("inputs.txt", "w+");
    fprintf(fp_inputs, "%d\n", n_inputs);

    float real_inputs[n_inputs];
    write_to_file(real_inputs, fp_real_inputs, fp_inputs, n_inputs, 0);
}

int main(int argc, char* argv[])
{
    // Error handling
    if (argc != 3)
    {
        printf("Usage: %s [Number of Coefficients] [Number of Inputs]\n", argv[0]);
    }
    else
    {
        // Initialize the randomizer
        srand(time(NULL));

        //create_coeffs_files(atoi(argv[1]));
        create_inputs_files(atoi(argv[2]));
    }

    return 0;
}