#include <stdio.h>

int main() {

	int n;
	scanf_s("%d", &n);

	int arr[1000];

	for (int i = 0; i < n; i++) {
		scanf_s("%d", &arr[i]);
	}


	int arr2[1000];

	for (int i = 0; i < n; i++) {
		arr2[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i] == j + 1) {
				arr2[j]++;
			}
		}
	}

	if (n < 3) {
		printf("NO");
	}

	else if (n == 3) {
		int count = 0;

		for (int i = 0; i <= n; i++) {
			if (arr2[i] == 2) { count++; }
		}

		if (count == 3) {
			printf("YES");
		}
		else printf("NO");
	}

	else if (n == 4) {
		int count1 = 0;
		int count2 = 0;

		for (int i = 0; i <= n; i++) {
			if (arr2[i] == 2) {
				count1++;
			}

			if (arr2[i] == 1) {
				count2++;
			}
		}

		if (count1 == 2 && count2 == 2) {
			printf("YES");
		}
		else if (count1 == 3) {
			printf("YES");
		}
		else printf("NO");
	}

	else if (n == 5) {
		int count1 = 0;
		int count2 = 0;

		for (int i = 0; i <= n; i++) {
			if (arr2[i] == 2) {
				count1++;
			}
			if (arr2[i] == 1) {
				count2++;
			}
		}

		if (count1 == 1 && count2 == 4) {
			printf("YES");
		}

		else if (count1 == 2 && count2 == 2) {
			printf("YES");
		}

		else if (count1 == 3) {
			printf("YES");
		}
		else printf("NO");
	}

	else if (n >= 6) {
		int count1 = 0;
		int count2 = 0;

		for (int i = 0; i <= n; i++) {
			if (arr2[i] == 2) {
				count1++;
			}
			if (arr2[i] == 1) {
				count2++;
			}
		}
		if (count2 == 6) {
			printf("YES");
		}

		else if (count1 == 1 && count2 == 4) {
			printf("YES");
		}

		else if (count1 == 2 && count2 == 2) {
			printf("YES");
		}

		else if (count1 == 3) {
			printf("YES");
		}
		else printf("NO");
	}

	return 0;
}