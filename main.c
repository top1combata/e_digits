#include "functions.h"


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("incorrect usage, argumnet must be a number of digits\n");
	return 1;
    }
    
    uint64_t digits_count = strtoull(argv[1], NULL, 10); 
    mpz_t p, q;
    mpz_inits(p, q, NULL);

    uint64_t k = evaluate_series_terms_count(digits_count);
    evaluate_p_q(p, q, k, digits_count);
    write_digits(p, q, digits_count);
    printf("Done!\n");

    mpz_clears(p, q, NULL);
 
    return 0;
}
