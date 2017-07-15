# Embedded Systems Project
Implementation of an optimized finite impulse response filter.
Contained is also a program for generating N number of coefficients and M number of inputs.

Usage: .\FIR_Optimized [Number of Coefficients] [Number of Inputs]

## Implementation Details

The coefficients are represented as 8-bit unsigned integers.  
The inputs are represented as 8-bit signed integers.

The binary decimal point is located at 2^7, or 00.000000.  
The range of accepted inputs is from -1.00 to +1.00.  
This results in a scaling factor of 2^7, or 128.

## Optimizations Will Include:
 - Software Pipelining
 - Vector Operations
 - Operation Strength Reduction
