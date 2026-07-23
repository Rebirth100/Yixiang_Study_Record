#include <stdio.h>
#include <stdlib.h>

// ¸ë³²ÅÅÐò£¨´æ´¢ÔªËØ±¾Éí£¬¶¯Ì¬À©ÈÝ£©
void pigeonholeSort(int a[], int len) {
    if (len <= 1) return;

    int min = a[0], max = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
    int range = max - min + 1;

    int **holes = (int **)calloc(range, sizeof(int *));
    int *holeSize = (int *)calloc(range, sizeof(int));
    int *holeCap  = (int *)calloc(range, sizeof(int));

    for (int i = 0; i < len; i++) {
        int idx = a[i] - min;
        if (holes[idx] == NULL) {
            holes[idx] = (int *)malloc(2 * sizeof(int));
            holeCap[idx] = 2;
        }
        if (holeSize[idx] >= holeCap[idx]) {
            holeCap[idx] *= 2;
            holes[idx] = (int *)realloc(holes[idx], holeCap[idx] * sizeof(int));
        }
        holes[idx][holeSize[idx]++] = a[i];
    }

    int k = 0;
    for (int i = 0; i < range; i++) {
        if (holes[i] != NULL) {
            for (int j = 0; j < holeSize[i]; j++) {
                a[k++] = holes[i][j];
            }
            free(holes[i]);
        }
    }

    free(holes);
    free(holeSize);
    free(holeCap);
}


void displaArray(int a[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {21, 32, 43, 24, 45, 26, 27, 98, 59};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("ÅÅÐòÇ°: ");
    displaArray(arr, len);

    pigeonholeSort(arr, len);

    printf("ÅÅÐòºó: ");
    displaArray(arr, len);

    return 0;
}