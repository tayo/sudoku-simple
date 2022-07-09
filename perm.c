
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s N R\n", argv[0]);
		return 1;
	}
	// get N and R
	int n = atoi(argv[1]);
	int r = atoi(argv[2]);
	// // compute permutations using tgamma
	double num1 = tgamma((float)n + 1);
	double denom1 = tgamma(((float)n - (float)r) + 1);
	double res1 = num1 / denom1;
	// // compute permutations using lgamma
	double num2 = lgamma(n + 1);
	double denom2 = lgamma((n - r) + 1);
	double res2 = exp(num2 - denom2);

	printf("res1: %g\nres2: %g\n", res1, res2);
	return 1;
}
