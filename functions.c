#include "functions.h"


void write_digits(mpz_t p, mpz_t q, uint64_t digits_count)
{
    char filename[64];
    sprintf(filename, "e_%ld_digits.txt", digits_count);
    
    FILE* fout = fopen(filename, "w");

    printf("Writing digits to the %s..\n", filename);


    clock_t start = clock();

    mpf_t num, den, quot;
    mpf_inits(num, den, quot, NULL);


    mpf_set_prec(quot, ceil(digits_count*log2(10)));
    mpf_set_prec(num , ceil(digits_count*log2(10)));
    mpf_set_prec(den , ceil(digits_count*log2(10)));

    mpf_set_z(num, p);
    mpf_set_z(den, q);

    mpf_div(quot, num, den);
    mpf_out_str(fout, 10, digits_count, quot);

    mpf_clears(num, den, quot, NULL);


    fclose(fout);

    printf("Written in %.3f seconds!\n", (clock()-start)/(double)CLOCKS_PER_SEC);
}



static void evaluate_p_q_wrap(mpz_t p, mpz_t q, uint64_t l, uint64_t r)
{
    if (r - l == 1)
    {
        mpz_set_ui(p, 1);
        mpz_set_ui(q, r);
        return;
    }

    uint64_t m = (l+r)/2;

    mpz_t plm, qlm;
    mpz_inits(plm, qlm, NULL);

    // P(l,m) and Q(l,m)
    evaluate_p_q_wrap(plm, qlm, l, m);

    mpz_t pmr, qmr;
    mpz_inits(pmr, qmr, NULL);

    // P(m,r) and Q(m,r)
    evaluate_p_q_wrap(pmr, qmr, m, r);

    // P(l,r) = P(l,m)*Q(m,r) + P(m,r)
    mpz_set(p, pmr);
    mpz_addmul(p, plm, qmr);

    // Q(l,r) = Q(l,m) * Q(m,r)
    mpz_mul(q, qlm, qmr);

    mpz_clears(plm, pmr, qlm, qmr, NULL);
}



void evaluate_p_q(mpz_t p, mpz_t q, uint64_t k, uint64_t digits_count)
{
    printf("%ld series terms to compute %ld e digits\n\n", k, digits_count);

    printf("Computing the partial sum of %ld terms as a fraction..\n", k);

    clock_t start = clock();
    evaluate_p_q_wrap(p, q, 0, k);
    mpz_add(p, p, q);

    printf("Calculated in %.3f seconds!\n\n", (clock()-start)/(double)CLOCKS_PER_SEC);
}



static double log_factorial(uint64_t value)
{
    // 1/2*ln(2*pi*k) + k*(ln(k)-1)
    return 0.5l*log(2*M_PI*value) + value*(log(value)-1);
}



uint64_t evaluate_series_terms_count(uint64_t digits_count)
{
    if (digits_count < 30) return 30;

    // 1/2*log(2*pi*k) + k*(log(k)-1) > n*log(10)
    uint64_t left = 1, right = digits_count, mid = (left + right)/2;
    double rhs = digits_count * log(10);

    // binary search for least n
    while (!(log_factorial(mid-1) < rhs && log_factorial(mid) > rhs))
    {
        if (log_factorial(mid) < rhs)
            left = mid;
        else
            right = mid;
        mid = (left + right)/2;
    }

    return mid+1;
}

