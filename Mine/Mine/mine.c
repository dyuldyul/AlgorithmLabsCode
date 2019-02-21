#include <stdio.h>

int main() {

	int count =0;
	int n, m, x, y;

	scanf_s("%d %d %d %d", &n, &m, &x, &y);
	x = x - 1;
	y = y - 1;
	int arr[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf_s("%d", &arr[i][j]);
		}
	}

			if (arr[x][y] == 1)
				printf("game over");
			else {
				if (arr[x - 1][y - 1] == 1) {
					count++;
				}
				if (arr[x - 1][y] == 1) count++;
				if (arr[x - 1][y + 1] == 1) count++;
				if (arr[x][y - 1] == 1) count++;
				if (arr[x][y + 1] == 1)count++;
				if(arr[x + 1][y - 1] == 1)count++;
				if (arr[x+1][y] == 1)count++;
				if (arr[x+1][y + 1] == 1)count++;
			}

			if (arr[x][y] != 1) {
				printf("%d", count);
			}
			
	return 0;
}