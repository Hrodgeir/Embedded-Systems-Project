FIR Filter Project README
This is how to run the various programs in the FIR filter project.

===========================================================================================

Authors:

Matthew Hodgson V00803081
Graeme Turney   V00802741

===========================================================================================

This program generates N inputs from:
    -1.00 to +1.00 for the real_inputs_N.txt
    -128 to 128 for the scaled_inputs_N.txt

Create_File.c

Compile: gcc -o Create_File.exe Create_File.c
Execute: .\Create_File [Number of Inputs]

Notes:
This will only generate up to approximately 500,000 inputs.

===========================================================================================

This is the naive implementation.

FIR_Initial.c

Compile: arm-linux-gcc -static -o FIR_Initial.exe FIR_Initial.c
Execute: qemu-arm FIR_Initial.exe real_coeffs_N.txt real_inputs_N.txt

===========================================================================================

This is the first pass optimization.

FIR_Optimized_Fixed_Point.c

Compile: arm-linux-gcc -static -o FIR_Optimized_Fixed_Point.exe FIR_Optimized_Fixed_Point.c
Execute: qemu-arm FIR_Optimized_Fixed_Point.exe scaled_coeffs_N.txt scaled_inputs_N.txt

===========================================================================================

This is the second pass optimization.

FIR_Optimized.c

Compile: arm-linux-gcc -static -o FIR_Optimized.exe FIR_Optimized.c -O3
Execute: qemu-arm FIR_Optimized.exe scaled_coeffs_N.txt scaled_inputs_N.txt

===========================================================================================