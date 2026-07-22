// 选择排序
#include <stdio.h>

void selectSort(int arr[], int len) {
    for (int j = 0; j < len - 1; ++j) {
        int min;

        min = j;
        for (int i = j + 1; i < len; ++i) {
            if (arr[i] < arr[min])
                min = i;
        }
        int t;
        t = arr[j];
        arr[j] = arr[min];
        arr[min] = t;
    }
}

void displayArray(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int arr[] = {21, 32, 43, 24, 45, 26, 27, 98, 59};
    int len = sizeof(arr) / sizeof(arr[0]);

    selectSort(arr, len);
    displayArray(arr, len);

    return 0;
}
