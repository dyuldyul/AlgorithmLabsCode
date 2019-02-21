#include <stdio.h>

int main() {

	int a, b;

	scanf_s("%d %d", &a, &b);

	int sm, big, gcd, lcm;

	if (a > b) {
		big = a;
		sm = b;
	}
	else{
		big = b;
		sm = a;
	}

	for (int i = 1; i < sm; i++) {
		if (big%i == 0 && sm%i == 0) {
			gcd = i;
		}
	}

	int c, d;
	c = big / gcd;
	d = sm / gcd;

	lcm = c * d*gcd;

	printf("%d\n%d", gcd, lcm);

	return 0;
}