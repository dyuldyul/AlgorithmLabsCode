#include <stdio.h>

int main() {
	
	int arr[10];

	for (int i = 0; i < 10; i++) {
		scanf_s("%d", &arr[i]);
	}

	int cnt[10];
	for (int i = 0; i < 10; i++) {
		cnt[i] = 0;
	}

	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (arr[i] == arr[j]) {
				cnt[i]++;
				cnt[j]++;
			}
		}
	}

	int max = 0;
	int maxindex =0;

	for (int i = 0; i < 10; i++) {
		if (cnt[i] > max) {
			max = cnt[i];
			maxindex = i;
		}
	}

	int avr = 0;
	int sum = 0;

	for (int i = 0; i < 10; i++) {
		sum += arr[i];
	}
	avr = sum / 10;

	printf("\n%d\n", avr);

	printf("%d", arr[maxindex]);

	return 0;
}