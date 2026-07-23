// 直接插入排序

#include <stdio.h>

void StraightInsertionSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int t=arr[i];

        int j;
        for (j = i - 1; j >= 0; --j) {
            if (arr[j] > t)
                arr[j + 1] = arr[j];
            else
                break;

            arr[j + 1] = t;
        }
    }
}

void displayArray(int a[], int len){
    for (int i = 0; i < len; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {21, 32, 43, 24, 45, 26, 27, 98, 59};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("排序前：");
    displayArray(arr, len);

    StraightInsertionSort(arr, len);

    printf("排序后：");
    displayArray(arr, len);

    return 0;
}