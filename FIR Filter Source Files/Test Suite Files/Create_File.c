#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

void write_to_file(float* array, FILE* fpr, FILE* fps, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        // Generate random float ranging from 0 to 1
        array[i] = (float)((rand() % 101)) / 100;

        // 50% chance that the number will be negative
        if (rand() % 2 == 0)
        {
            array[i] *= -1;
        }

        // Write the randomly generated float to the file
        fprintf(fpr, "%0.2f\n", array[i]);

        // Convert the float into an 8-bit representation
        int8_t scaled = (int8_t)(roundf(array[i] * 128));
        fprintf(fps, "%d\n", scaled);
    }

    fclose(fpr);
    fclose(fps);
}

void create_inputs_files(int n_inputs)
{
    FILE* fp_real_inputs;
    char* real_file_name = (char*)malloc(30*sizeof(char));
    sprintf(real_file_name, "real_inputs_%d.txt", n_inputs);
    fp_real_inputs = fopen(real_file_name, "w+");
    fprintf(fp_real_inputs, "%d\n", n_inputs);

    FILE* fp_inputs;
    char* file_name = (char*)malloc(30*sizeof(char));
    sprintf(file_name, "scaled_inputs_%d.txt", n_inputs);
    fp_inputs = fopen(file_name, "w+");
    fprintf(fp_inputs, "%d\n", n_inputs);

    float real_inputs[n_inputs];
    write_to_file(real_inputs, fp_real_inputs, fp_inputs, n_inputs);
}

int main(int argc, char* argv[])
{
    // Error handling
    if (argc != 2)
    {
        printf("Usage: %s [Number of Inputs]\n", argv[0]);
    }
    else
    {
        // Initialize the randomizer
        srand(time(NULL));
        create_inputs_files(atoi(argv[1]));
    }

    return 0;
}