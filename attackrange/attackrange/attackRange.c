#include <stdio.h>

int main() {
	int n, x, y, r;

	scanf_s("%d %d %d %d", &n, &x, &y, &r);

	x = x - 1;
	y = y - 1;

	int arr[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == x && j == y) {
				arr[i][j] = -1;
			}
			else arr[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 1; k <= r; k++) {
				int cha1 = 0;
				int cha2 = 0;


				if (i > x) {
					cha1 = i - x;
				}
				else if ( x > i) {
					cha1 = x - i;
				}

				if (j > y ) {
					cha2 = j - y;
				}
				else if ( y > j ) {
					cha2 = y - j;
				}

				if (cha1 + cha2 == k) {
					arr[i][j] = k;
				}
			}
		}
	}
	

	printf("%d %d\n", x, y);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == -1) { printf("x "); }
			else printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}