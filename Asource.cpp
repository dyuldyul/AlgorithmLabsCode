#include <stdio.h>

int main() {

    int n;
    scanf_s("%d", &n);

    for (int i = 1; i <= n; i++) {
        if (i == n/2 +1) {
            for (int j = 1; j <= 2 * n - 1; j++) {
                if (j <= n + (i - 1) && j >= n - (i - 1)) {
                    printf("*");
                }
                else printf(" ");
            }
        }
        else {
            for (int j = 1; j <= 2 * n - 1; j++) {
                if (j == n - (i - 1) || j == n + (i - 1)) {
                    printf("*");
                }
                else printf(" ");

            }
        }
        printf("\n");
    }

    return 0;
}


/*

    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            printf(" ");
        }

        for (int j = 0; j < 2 * i + 1; j++) {
            printf("*");
        }

        printf("\n");
    }
*/