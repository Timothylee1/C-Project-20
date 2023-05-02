#include <stdlib.h>
#include <stdio.h>

#include "add_digit.h"

/******************************************************************************
 * These helper functions have been defined in this file after main().        *
 ******************************************************************************/

static void print_string_sum(
	const char* in1,
	const char* in2,
	const char* in3
);

static void add_string(
	const char* in1,
	const char* in2
);

/******************************************************************************
 * Test driver.                                                               *
 ******************************************************************************/

void test_print(void)
{
	printf("---- [TEST PRINTOUTS - THESE SUMS DO NOT HAVE TO ADD UP] ----\n\n");
	print_string_sum(
		"123",
		"456",
		"789345"
	);
	printf("\n");
	print_string_sum(
		"38942938588",
		"8092010461941764",
		"55057839278052"
	);
	printf("\n");
	print_string_sum(
		"0",
		"8960238801",
		"52272535417416149"
	);
	printf("\n");
	print_string_sum(
		"0546723737800550742",
		"4692129",
		"166389602636221390874025"
	);
	printf("\n");
	print_string_sum(
		"351767983670665905036068167",
		"6097194894",
		"71375289436108175532"
	);
}

void test_add_string(void)
{
	printf("\n---- [PROPER CALCULATIONS] ----\n");
	printf("\n");
	add_string("0", "0");
	printf("\n");
	add_string("0", "5");
	printf("\n");
	add_string("5", "0");
	printf("\n");
	add_string("10", "4");
	printf("\n");
	add_string("14", "4");
	printf("\n");
	add_string("10000", "1000");
	printf("\n");
	add_string("10000", "1234");
	printf("\n");
	add_string("2103304", "3557040");
	printf("\n");
	add_string(
		"492358267338223333628632935656",
		"6812538795997748941351275296794624212683611641315635972314764214943671"
			"3944989423391414"
	);
}

int main(void)
{
	test_print();
	test_add_string();
}

/******************************************************************************
 * Definitions of all the helper functions.                                   *
 ******************************************************************************/

// Counts calls to add_BigDigit().
unsigned int called = 0;

BigDigit add_BigDigit(
	BigDigit digit1,
	BigDigit digit2,
	BigDigit* const carry
)
{
	BigDigit sum = (BigDigit)(digit1 + digit2 + *carry);
	called++;
	*carry = (sum / 10);
	return (sum % 10);
}

void print_string_sum(
	const char* in1,
	const char* in2,
	const char* in3
)
{
	BigNumber* num1 = create_BigNumber(in1);
	BigNumber* num2 = create_BigNumber(in2);
	BigNumber* num3 = create_BigNumber(in3);

	print_BigNumber_sum(num1, num2, num3);

	destroy_BigNumber(num1);
	destroy_BigNumber(num2);
	destroy_BigNumber(num3);
}

void add_string(
	const char* in1,
	const char* in2
)
{
	BigNumber* num1 = create_BigNumber(in1);
	BigNumber* num2 = create_BigNumber(in2);
	BigNumber* num3 = add_BigNumber(num1, num2);

	print_BigNumber_sum(num1, num2, num3);

	destroy_BigNumber(num1);
	destroy_BigNumber(num2);
	destroy_BigNumber(num3);

	if (called)
	{
		printf(
			((called > 1)
				? "\nadd_BigDigit() was called %d times.\n"
				: "\nadd_BigDigit() was called %d time.\n"
			),
			called
		);
		called = 0;
	}
}
