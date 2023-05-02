/*!
@file       add_digit.c
@author     Timothy Lee (timothykexin.lee@digipen.edu.sg)
@course     RSE 1201
@section    Laboratory 12
@Laboratory Big Numbers
@date       04/12/2021
@brief      This file contains definitions to perform addition of big numbers of any number 
            of digits long. 
            It contains the definitions of functions:
            create_BigNumber(const char* text)
            destroy_BigNumber(BigNumber* number)
            add_BigNumber(const BigNumber* number1, const BigNumber* number2)
            print_BigNumber_sum(const BigNumber* number1, const BigNumber* number2,
	                            const BigNumber* sum)
*//*________________________________________________________________________________________*/

#include "add_digit.h"
#include <stdlib.h>                                                      //For malloc, free
#include <stdio.h>                                                       //For printf
#include <string.h>                                                      //For strlen, memmove
#include <stdbool.h>                                                     //For bool 
enum state {
    TRUE = 1, 
    FALSE = 0
    };

struct BigNumber
{
BigDigit* digits;
size_t length;
};

/*!
@brief  This function dynamically allocates memory to a BigNumber object. Digits data member 
        allocated array. Length data member is to be assigned the same value as the number 
        of characrers in the input text. Digits is to then be set with the values of the 
        text input, and that range is from 0 - 9. Note that the Digits should be populated
        with digits derived from the text's ASCII characters.

@param  text (the input text containing the ASCII characters)
        
@return ptr (Pointer to the Struct BigNumber)
*//*_______________________________________________________________________________________*/
BigNumber* create_BigNumber(const char* text) {
    size_t length = strlen(text);                                        //Doesn't take in the NUL
    BigNumber *ptr = malloc(sizeof(BigNumber));                          //Allocate memory size 
    (*ptr).digits = malloc(length * sizeof(BigDigit));                   //Allocate memory size to digits
    (*ptr).length = length;                                              //Assign length value
    for(size_t i = 0; i < length; i++) {                                 //Assign each digits element with text elements
        unsigned char set = (unsigned char)(text[i] - '0');              //ASCII '0' is 48; if '1' - '0' value = 1
        ptr->digits[i] = set;
    }
    return ptr;
}

/*!
@brief  This function destroys BigNumber objects

@param  number (the object to be destroyed)
        
@return nothing
*//*_______________________________________________________________________________________*/
void destroy_BigNumber(BigNumber* number) {
	free((*number).digits);
	free(number);
}

/*!
@brief  This function adds the two BigNumber objects.

@param  number1 (First object to Struct BigNumber)
        number2 (Second object to Struct BigNumber)
        
@return add (Object to the Struct BigNumber)
*//*_______________________________________________________________________________________*/
BigNumber* add_BigNumber(const BigNumber* number1, const BigNumber* number2) {
    size_t num1 = number1->length, num2 = number2->length, large, diff;
    bool one_bigger = TRUE;
    if(num1 >= num2) {
        large = num1;                                                    //largest length
        diff = num1 - num2;                                              //difference 
    }
    else {
        large = num2;                                                    //largest length
        one_bigger = FALSE;                                              //num2 is larger
        diff = num2 - num1;                                              //difference 
    }

    BigNumber *add = malloc(sizeof(BigNumber));
    add->length = large + 1;                                             //+1 for case of carry forward after final addition
    add->digits = malloc(add->length * sizeof(BigDigit));
    BigDigit carry = 0;
 
    int Cont_adding = 1;                                                 //1 to start the addition
    for(size_t i = large - 1; (int)i >= 0; i--){
        
        if ((int)(i - diff) < 0)                                         //To stop the addition
            Cont_adding = 0;

        BigDigit sum;
        if (Cont_adding) {
            if (one_bigger == TRUE) {                                    //number1 larger
                sum = add_BigDigit(number1->digits[i], 
                                    number2->digits[i - diff], &carry);  //i - diff to point to the correct element
            }
            else {                                                       //number2 larger
                sum = add_BigDigit(number2->digits[i], 
                                    number1->digits[i - diff], &carry);  //i - diff to point to the correct element
            }
        }
        else {
            if (one_bigger == TRUE) {                                    //number1 larger
                sum = add_BigDigit(number1->digits[i], 0, &carry);       //0 cuz no more elements to point to for number2
            }
            else {   //number2 larger
                sum = add_BigDigit(number2->digits[i], 0, &carry);       //0 cuz no more elements to point to for number1
            }
        }
        add->digits[i + 1] = sum;                                        //Assigns the summed value into the new struct pointer
    }
    
    if (carry == 1) 
        add->digits[0] = carry;
    else {                                                               //To remove the +1 in the event there is no carry forward
        memmove(add->digits, add->digits + 1, large);                    //memory move from +1 to digits for large elements
        add->length = large;                        
    }
    return add;
}

/*!
@brief  This function prints the sum of the BigNumber objects.

@param  number1 (First object to Struct BigNumber)
        number2 (Second object to Struct BigNumber)
        sum     (Third object to Struct BigNumber)
        
@return nothing
*//*_______________________________________________________________________________________*/
void print_BigNumber_sum(const BigNumber* number1, const BigNumber* number2, 
                                const BigNumber* sum) {
    size_t longest = number1->length;
    if (longest < number2->length)
        longest = number2->length;

    if (longest < sum->length)
        longest = sum->length;

    //Printf first line
    printf("  ");
    for(size_t i = 0; i < longest - number1->length; ++i)
        printf(" ");
    for(size_t i = 0; i < number1->length; ++i)
        printf("%c", number1->digits[i] + '0');
    printf("\n");

    //Printf second line
    printf("+ ");
    for(size_t i = 0; i < longest - number2->length; ++i)
        printf(" ");
    for(size_t i = 0; i < number2->length; ++i)
        printf("%c", number2->digits[i] + '0');
    printf("\n");
    
    for(size_t i = 0; i < longest + 2; ++i)
        printf("-");                                                     //Printf separator

    //Printf sum line
    printf("\n  ");
    for(size_t i = 0; i < longest - sum->length; ++i)
        printf(" ");
    for(size_t i = 0; i < sum->length; ++i)
        printf("%c", sum->digits[i] + '0');
    printf("\n");
}

