// 折半插入

#include <stdio.h>

// 折半插入排序
void binInsertSort(int a[], int len) {
    for (int i = 1; i < len; ++i) {
        int left = 0, right = i - 1, mid;
        int data = a[i];

        // 二分查找插入位置
        while (left <= right) {
            mid = (left + right) / 2;
            if (a[mid] > data)
                right = mid - 1;
            else
                left = mid + 1;
        }

        // 移动元素，腾出位置
        for (int j = i - 1; j >= left; --j) {
            a[j + 1] = a[j];
        }

        a[left] = data;
    }
}

// 打印数组
void displayArray(int a[], int len) {
    for (int i = 0; i < len; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int arr[] = {79, 72, 4, 99, 3, 29, 4, 32, 9};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("排序前: ");
    displayArray(arr, len);

    binInsertSort(arr, len);

    printf("排序后: ");
    displayArray(arr, len);

    return 0;
}