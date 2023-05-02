#ifndef ADD_DIGIT_H
#define ADD_DIGIT_H

/******************************************************************************
 * You must define this struct; here is its forward declaration and aliases.  *
 ******************************************************************************/
 
// Forward declaration
struct BigNumber;

typedef unsigned char BigDigit;
typedef struct BigNumber BigNumber;

/******************************************************************************
 * You must define these functions; their declaration are shown below.        *
 ******************************************************************************/

extern BigNumber* create_BigNumber(
	const char* text
);

extern void destroy_BigNumber(
	BigNumber* number
);

extern BigNumber* add_BigNumber(
	const BigNumber* number1,
	const BigNumber* number2
);

extern void print_BigNumber_sum(
	const BigNumber* number1,
	const BigNumber* number2,
	const BigNumber* sum
);

/******************************************************************************
 * You must use this function; it has already been defined.                   *
 ******************************************************************************/

BigDigit add_BigDigit(
	BigDigit digit1,
	BigDigit digit2,
	BigDigit* carry
);

#endif
