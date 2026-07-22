// √∞≈›≈≈–Ú
#include <stdio.h>

void bubbleSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void displayArray(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int arr[] = {21, 32, 43, 24, 45, 26, 27, 98, 59};
    int len = sizeof(arr) / sizeof(arr[0]);

    printf("≈≈–Ú«∞£∫");
    displayArray(arr, len);

    bubbleSort(arr, len);

    printf("≈≈–Ú∫Û£∫");
    displayArray(arr, len);
}
