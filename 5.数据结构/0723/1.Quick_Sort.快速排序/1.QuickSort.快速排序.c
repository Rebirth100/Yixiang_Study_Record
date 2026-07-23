#include <stdio.h>

void quickSort(int a[], int len){
    if (len <= 1)
        return;

    int t = a[0];
    int left = 0;
    int right = len - 1;

    while (1){
        while (left != right && a[right] >= t)
            --right;
        if (left == right)
            break;
        a[left] = a[right];

        while (left != right && a[left] <= t)
            ++left;
        if (left == right)
            break;
        a[right] = a[left];
    }
    a[left] = t;

    quickSort(a, left);
    quickSort(a + left + 1, len - left - 1);
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

    quickSort(a, len);
    displayArray(a, len);

    return 0;
}