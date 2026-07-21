#include <stdio.h>

int bsearchData(int arr[], int len, int data)
{
    int left = 0;
    int right = len - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (data > arr[mid])
        {
            left = mid + 1;
        }
        else if (data < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {1, 4, 6, 7, 8, 11, 15, 28};
    int len = sizeof(arr) / sizeof(arr[0]);

    int data1 = 15;
    int res1 = bsearchData(arr, len, data1);
    printf("查找15，下标：%d\n", res1);


    int data2 = 4;
    int res2 = bsearchData(arr, len, data2);
    printf("查找4，下标：%d\n", res2);


    int data3 = 45;
    int res3 = bsearchData(arr, len, data3);
    printf("查找45，下标：%d\n", res3);

    return 0;
}