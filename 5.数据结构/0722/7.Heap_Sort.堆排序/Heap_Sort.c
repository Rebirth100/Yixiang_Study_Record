#include <stdio.h>

void maxHeap(int a[], int len, int i){
    int maxson;

    while (1){
        maxson = 2 * i + 1;
        if (maxson >= len)
            return;
        if (maxson + 1 < len && a[maxson + 1] > a[maxson])
            ++maxson;

        if (a[i] >= a[maxson])
            return;

        int t;
        t = a[i];
        a[i] = a[maxson];
        a[maxson] = t;

        i = maxson;
    }
}

void heapSort(int a[], int len){
    for (int i = len / 2 - 1; i >= 0; --i) {
        maxHeap(a, len, i);
    }

    for (int i = len - 1; i > 0; --i) {
        int t;
        t = a[0];
        a[0] = a[i];
        a[i] = t;
        maxHeap(a, i, 0);
    }
}

void displayArray(int a[], int len){
    for (int i = 0; i < len; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[] = {27,82,98,2,86,9,24,44,83,3,12,46,22,46};
    int len = sizeof(a) / sizeof(a[0]);

    heapSort(a, len);
    displayArray(a, len);

    return 0;
}