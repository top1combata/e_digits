#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <gmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void write_digits(mpz_t, mpz_t, uint64_t);
void evaluate_p_q(mpz_t, mpz_t, uint64_t, uint64_t);
uint64_t evaluate_series_terms_count(uint64_t);
