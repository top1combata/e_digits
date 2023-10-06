# e digits 

Simple and fast [algorithm](https://en.wikipedia.org/wiki/E_(mathematical_constant)#Computing_the_digits) to compute as many digits of Euler's number as you want. For arbitrary precision integers it uses [GMP](https://gmplib.org/). 


# Algorithm
$$ e = \sum_{k = 0}^{\infty} \frac{1}{k!} \hspace{50pt} S_{n} = \sum_{k=0}^{n} \frac{1}{k!}$$
$$ r_{n} = e - S_{n} = \sum_{k=n+1}^{\infty} \frac{1}{k!} < \frac{1}{n!}\sum_{k=1}^{\infty} \frac{1}{2^k} = \frac{1}{n!}$$

So here we have an estimation error and we can find $n$ using Stirling's formula and binary search.

Auxiliary Functions:
$$ P(l,r) = r!\bigg(\frac{1}{(l+1)!} + \frac{1}{(l+2)!} + ... + \frac{1}{r!}\bigg)  $$

$$ Q(l,r) = (l+1)(l+2)...(r-1)r$$
We can compute $P$ and $Q$ recursively:
$$ P(l,r) = P(l,m)Q(m,r) + P(m,r)$$

$$ Q(l,r) = Q(l,m)*Q(m,r)$$

$$ l < m < r$$

It remains to note that:
$$ S_{n} = \sum_{k = 0}^{n} \frac{1}{k!} = 1 + \frac{P(0,n)}{Q(0,n)}$$