#include <stdio.h>

int main() {
	int n;
	scanf_s("%d", &n);
	
	int arr[1000][5];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 5; j++) {
			scanf_s("%d", &arr[i][j]);
		}
	}

	int cnt[1000];
	for (int i = 0; i < 1000; i++) {
		cnt[i] = 0;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int l = 0; l < n; l++) {
			for (int j = 0; j < 5; j++) {
				if (arr[i][j] == arr[l][j]) {
					cnt[i]++;
					cnt[l]++;
					break;
				}
			}
		}
	}

	int max = 0;
	int maxindex;
	for (int i = 0; i < n; i++) {
		if (cnt[i] > max) {
			max = cnt[i];
			maxindex = i;
		}
	}

	printf("%d", maxindex + 1);

	return 0;
}