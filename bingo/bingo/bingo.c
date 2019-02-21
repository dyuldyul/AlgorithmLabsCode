#include <stdio.h>

int main() {
	int arr1[5][5];
	int arr2[5][5];

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf_s("%d ", &arr1[i][j]);
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			scanf_s("%d ", &arr2[i][j]);
		}
	}

	int count = 0;
	int bingo = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					if (arr2[i][j] == arr1[k][l]) {
						arr1[k][l] = 0;
					}
					if (arr1[0][0] == 0 && arr1[1][1] == 0 && arr1[2][2] == 0 && arr1[3][3] == 0 && arr1[4][4]) {
						count++;
						if (count == 3) {
							bingo = 5 * i + j + 1;
							printf("%d", bingo);
							break;
						}
					}
					if (arr1[0][4] == 0 && arr1[1][3] == 0 && arr1[2][2] == 0 && arr1[3][1] == 0 && arr1[4][0]) {
						count++;
						if (count == 3) {
							bingo = 5 * i + j + 1;
							printf("%d", bingo);
							break;
						}

					}
					for (int m = 0; m < 5; m++) {
						if (arr1[m][0] == 0 && arr1[m][1] == 0 && arr1[m][2] == 0 && arr1[m][3] == 0 && arr1[m][4]) {
							count++;
							if (count == 3) {
								bingo = 5 * i + j + 1;
								printf("%d", bingo);
								break;
							}
						}
					}
					for (int n = 0; n < 5; n++) {
						if (arr1[0][n] == 0 && arr1[1][n] == 0 && arr1[2][n] == 0 && arr1[3][n] == 0 && arr1[4][n]) {
							count++;
							if (count == 3) {
								bingo = 5 * i + j + 1;
								printf("%d", bingo);
								break;
							}
						}
					}
					if (count == 3) {
						bingo = 5 * i + j + 1;
						printf("%d", bingo);
						break;
					}
				}
				if (count == 3) {
					bingo = 5 * i + j + 1;
					printf("%d", bingo);
					break;
				}
			}
			if (count == 3) {
				bingo = 5 * i + j + 1;
				printf("%d", bingo);
				break;
			}
		}
	}


	return 0;
}