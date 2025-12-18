#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TICKER 6
#define STOCKS 7
typedef struct Stock {
    char ticker[TICKER];
    float price; 
} Stock;


void data_setup(Stock mag7[], int count);
void merge_sort(Stock mag7[], int left, int right);
void merge(Stock mag7[], int left, int mid, int right);
void data_present(const Stock mag7[], int count);

int main(void) {
    Stock mag7[STOCKS];

    data_setup(mag7, STOCKS);
    merge_sort(mag7, 0, STOCKS - 1);
    data_present(mag7, STOCKS);

    return 0;

}
//Fetch mag7 EOD data
void data_setup(Stock mag7[], int count) {
    if (count < 7) return;

    strcpy(mag7[0]. ticker, "MSFT"); mag7[0].price = 299.10;
    strcpy(mag7[1]. ticker, "AAPL"); mag7[1].price = 207.30;
    strcpy(mag7[2]. ticker, "TSLA"); mag7[2].price = 174.50;
    strcpy(mag7[3]. ticker, "GOOGL"); mag7[3].price = 131.20;
    strcpy(mag7[4]. ticker, "AMZN"); mag7[4].price = 102.00;
    strcpy(mag7[5]. ticker, "META"); mag7[5].price = 184.60;
    strcpy(mag7[6]. ticker, "NVDA"); mag7[6].price = 441.00;
    
}

//Merge sort algo
void merge_sort(Stock mag7[], int left, int right) {
    if(left >= right) return;
    
    int mid = left + (right - left) / 2;

    merge_sort(mag7, left, mid);
    merge_sort(mag7, mid + 1, right);
    merge(mag7, left, mid, right);

}

//Merge helper
void merge(Stock mag7[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Stock leftArr[n1];
    Stock rightArr[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = mag7[left + i];
    
    for (int j = 0; j < n2; j++)
        rightArr[j] = mag7[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2){
        if (leftArr[i].price >= rightArr[j].price){
            mag7[k] = leftArr[i];
            i++;
        } else {
            mag7[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        mag7[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        mag7[k] = rightArr[j];
        j++;
        k++;
    }

}

//Interpret
void data_present(const Stock mag7[], int count) {

}