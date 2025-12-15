#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TICKER 5
#define STOCKS 7
typedef struct Stock {
    char ticker[TICKER];
    float price; 
} Stock;


void data_setup(Stock mag7[], int count);
void merge_sort(Stock mag7[], int left, int right);
void merge(Stock mag7[], int left, int mid, int right);
void data_present(const Stock mag7[], int count);

int main(void)
{
    Stock mag7[STOCKS];

    data_setup(mag7, STOCKS);
    merge_sort(mag7, 0, STOCKS - 1);
    data_present(mag7, STOCKS);

    return 0;

}
//Fetch mag7 EOD data
void data_setup(Stock mag7[], int count) {
    



}


//Merge sort algo
void merge_sort(Stock mag7[], int left, int right) {

}

//Merge helper
void merge(Stock mag7[], int left, int mid, int right) {

}

//Interpret
void data_present(const Stock mag7[], int count) {

}