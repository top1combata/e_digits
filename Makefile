all:
	@gcc main.c functions.c -O3 -Wall -lgmp -lm -o e_digits.out
