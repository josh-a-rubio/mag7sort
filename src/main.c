#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>

#define DATA_FILE "mag7_data.csv"

#define TICKER 6
#define STOCKS 7
typedef struct Stock {
    char ticker[TICKER];
    float price; 
    float percentGain;
    double marketCap;
} Stock;

#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"
#define GREEN "\033[32m"
#define RED   "\033[31m"


void data_setup(Stock mag7[], int count);
void merge_sort(Stock mag7[], int left, int right);
void merge(Stock mag7[], int left, int mid, int right);
void data_present(const Stock mag7[], int count);

int main(void) {
    freopen("/dev/null", "r", stdin);

    Stock mag7[STOCKS];

    data_setup(mag7, STOCKS);
    merge_sort(mag7, 0, STOCKS - 1);
    data_present(mag7, STOCKS);

    return 0;

}

//Fetch mag7 EOD data
void data_setup(Stock mag7[], int count) {
    printf("Fetching latest MAG7 data...\n");
    
    int ret = system("./fetch-mag7 > /dev/null 2>&1");  
    if (ret != 0) {
        fprintf(stderr, "Error fetching MAG7 data!\n");
        exit(1);  
    }

    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open %s\n", DATA_FILE);
        exit(1);
    }

    char line[256];
    fgets(line, sizeof(line), fp);
    
    for (int i = 0; i < count; i++) {
        if (fscanf(
            fp,
            "%5[^,],%f,%f,%lf\n",
            mag7[i].ticker,
            &mag7[i].price,
            &mag7[i].percentGain,
            &mag7[i].marketCap
        ) != 4) {
            fprintf(stderr, "Malformed data in %s\n", DATA_FILE);
            fclose(fp);
            exit(1);
        }
    }
    fclose(fp);

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
        if (leftArr[i].percentGain >= rightArr[j].percentGain){
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
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &tm);

    double totalMarketCap = 0.0;
    for (int i = 0; i < count; i++) {
        totalMarketCap += mag7[i].marketCap;
    }

    // Title box
    printf("+-------------------------------------------+\n");
    printf("|"BOLD BLUE" MAG 7 — Live Market Snapshot - %s "RESET"|\n", dateStr);
    printf("+-------------------------------------------+\n");
    printf(BOLD "The Magnificent Seven are now worth %.2f trillion USD!\n\n" RESET, totalMarketCap);

    // Winner & Loser
    printf("+---------------------------------------+\n");
    printf("|"BOLD WHITE" Winner & Loser of the Day (By %% Gain) "RESET"|\n");
    printf("+---------------------------------------+\n");

    const char *winnerColor = (mag7[0].percentGain >= 0) ? GREEN : RED;
    const char *loserColor = (mag7[count-1].percentGain >= 0) ? GREEN : RED;

    printf(
        "Winner:  %-6s | Price: %s%7.2f%s | Gain: %s%+6.2f%%%s\n",
        mag7[0].ticker,
        winnerColor,
        mag7[0].price,
        RESET,
        winnerColor,
        mag7[0].percentGain,
        RESET
    );
    printf(
        "Loser:   %-6s | Price: %s%7.2f%s | Gain: %s%+6.2f%%%s\n\n", 
        mag7[count-1].ticker,
        loserColor,
        mag7[count-1].price,
        RESET,
        loserColor,
        mag7[count-1].percentGain,
        RESET
    );

    // Sorted list
    printf("+--------------------------------------------+\n");
    printf( "|"BOLD WHITE" Sorted MAG 7 Stocks (Descending by %% Gain) "RESET"|\n");
    printf("+--------------------------------------------+\n");
    printf("Rank | Ticker | Price   | Gain   | Market Cap \n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        const char *gainColor = (mag7[i].percentGain >= 0) ? GREEN : RED;

        printf(
            WHITE "%d" RESET "    | %-6s | %s%7.2f%s | %s%+6.2f%%%s | %.2fT\n", 
            i + 1,
            mag7[i].ticker,
            gainColor,
            mag7[i].price,
            RESET,
            gainColor,
            mag7[i].percentGain,
            RESET,
            mag7[i].marketCap
        );
    }
    printf("\n");

}





