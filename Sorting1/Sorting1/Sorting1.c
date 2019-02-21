#include <stdio.h>

int main() {
	int n, k;
	scanf("%d", &n);

	int arr[n];

	for (int i = 0; i < n; i++) {
		scnaf("%d", &arr[i]);
	}

	for (int i = 0; i < n; i++) {
		int inx= i;
		for (int j = i+1; j < n; j++ ){
			if (arr[inx] > arr[j]) {
				inx = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[inx];
		arr[inx] = temp;
	}

	printf("%d", arr[k+1]);

	return 0;
}