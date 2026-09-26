/*
 ============================================================================
 Name        : Lab2.c
 Author      : Austin Tian (starter), completed by Solomon Ewusi
 Student ID  : N01659373
 Course      : CENG 356 - Computer Systems Architecture
 Description : Signed number and unsigned numbers, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 32   // maximum size of the binary number is 32 bit. 
#define number1 "11000001010010000000000000000000"
#define number2 "01000001010101000000000000000000"
void convert_binary_to_signed(const char *binary);
void convert_binary_to_float(const char *binary);
char *menu =    "\n" \
                "\n" \
                "===================================================================\n" \
                "************Please select the following options********************\n" \
                " *    1. Binary number to signed decimal number conversion.(Lab 2) *\n" \
                " *    2. Binary number to Floating number conversion (Lab 2)       *\n" \
                " *******************************************************************\n" \
                " *    e. To Exit, Type 'e'                                         *\n" \
                " *******************************************************************\n";

int main(void) {
        char options;  // the option should only be a byte
        char inputs[33] = {0};  // 32-bit string plus a ending indicator.         
        do{
            puts(menu); /* prints Memory Simulation */
            fflush(stdin);  // clear the input buffer before getchar. 
            options = getchar();
            fflush(stdin);  // clear the input buffer after getchar.             
            switch (options)
            {             
                case '1': /* lab 2. Convert binary number into a SIGNED decimal
                           number and display */
                    puts("Please input your BINARY number, "\
                            "I will convert it to signed decimal:");
                    scanf("%s", &inputs[0]);  // Input must be a string with 0/1
                    convert_binary_to_signed(inputs);
                    continue;
                case '2':/* lab 2. Convert 32-bit binary number into a floating 
                          *  point number number and display */
                    puts("Please input your 32-bit floating point number " \
                            "in binary, I will convert it to decimal");
                    scanf("%s", &inputs[0]);  // Input must be a string with 0/1
                    convert_binary_to_float(inputs);
                    continue;  
                case 'e':
                    puts("Code finished, exit now");
                    return EXIT_SUCCESS;
                default:
                    puts("Not a valid entry, exit now");
                    continue;                  
            } 
        }while (1);
}

void convert_binary_to_signed(const char *binary)
{
    int result = 0;   //  holds the final signed decimal value
    int length = 8;   // this converts 8-bit binary numbers

    for (int i = 0; i < length; i++)
    {
        int bit_value = binary[i] - '0';  // converts the character '0' or '1' into the integer 0 or 1
        int position = length - 1 - i;    // position of bit from the right (7 down to 0)

        if (i == 0)
        {
            // leftmost bit is the sign bit, worth NEGATIVE 2^7
            result += bit_value * (-128);
        }
        else
        {
            // every other bit is worth its normal positive power of 2
            result += bit_value * (int)pow(2, position);
        }
    }

    printf("Signed decimal value: %d\n", result);
}

void convert_binary_to_float(const char *binary)
{
    int sign = binary[0] - '0';   // the first bit is the sign bit (0 = positive, 1 = negative)
    int exponent = 0;             // this will hold the 8 exponent bits as a normal number

    for (int i = 1; i <= 8; i++)  // the exponent bits are characters 1 through 8
    {
        int bit_value = binary[i] - '0';               // this converts '0'/'1' character to 0/1
        exponent += bit_value * (int)pow(2, 8 - i);    // this add this bit's normal power of 2
    }

    double fraction = 0.0;        // this will hold the fractional part, like 0.5625

    for (int i = 9; i <= 31; i++) // this fraction bits are characters 9 through 31
    {
        int bit_value = binary[i] - '0';               // this convert '0'/'1' character to 0/1
        fraction += bit_value * pow(2, -(i - 8));      // the first fraction bit is worth 2^-1, next 2^-2, etc.
    }

    double mantissa = 1.0 + fraction;  // the leading 1 is implied, so add it back

    double value = mantissa * pow(2, exponent - 127);  // apply the exponent with the bias (127) removed

    if (sign == 1)
    {
        value = -value;   // sign bit of 1 means the number is negative
    }

    printf("Floating point value: %f\n", value);
}