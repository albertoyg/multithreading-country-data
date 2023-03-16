#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>

// single thread, then multithread, see how many clock ticks each takes
// one buffer for each city 

int totalCount = 0;
float overallMax = -100000;
float overallMin = 100000;
char overallMaxCity[100];
char overallMinCity[100];

void readFile(char* file){
        // open file 
        FILE* f = fopen(file, "r");
        // check if file actually opened / exists 
        if(f == NULL) {
            printf("Error, file '%s' does not exsist\n", file);
            exit(0);
        }
        // init min and max temp values, curMin and curMax, line length, and count
        float max = -100000;
        float min = 100000;
        char line[500];
        float curMax = 0;
        float curMin = 0;
        int count = 0;
        float average = 0;
        
        // Allocate memory for the city name string
        char city[100]; 

        // Copy the substring between the first 11 characters and the last 4 characters
        strncpy(city, file + 11, strlen(file) - 11 - 4);
        city[strlen(file) - 11 - 4] = '\0';

        // look at each line in file f and extract data
        while(fgets(line, sizeof(line), f)) {
            // scan each line that follows (float) (float) format
            int items = sscanf(line, "%f %f", &curMax, &curMin);
            if (items == 2){
                // compare curent min temp
                if (curMin < min) {
                    // if it is, curMin is the new min
                    min = curMin;
                }
                // compare current max temp
                if (curMax > max) {
                    // if it is, curMax is the new max
                    max = curMax;
                    
                }



                average = average + curMin + curMax;
                count = count + 2;
            }
            
        }
        totalCount = totalCount + (count/2);
        printf("===================================================\n");
        printf("Data for: %s\n", city);
        printf("%s's lowest temperature is: %.1f degrees Celsius\n", city, min);
        printf("%s's highest temperature is: %.1f degrees Celsius\n", city, max);
        printf("The average temperature for %s is: %.1f degrees Celsius\n", city, average/count);
        printf("Total values processed for %s are: %d\n\n", city, (count/2));
        fclose(f);

        if (max > overallMax) {
            overallMax = max;
            strcpy(overallMaxCity, city);
        }
        if (min < overallMin) {
            overallMin = min;
            strcpy(overallMinCity, city);
        }
}


int main(int argc, char* argv[]){
    char* filePaths[11] = {
        "data_files/Charlottetown.dat",
        "data_files/Edmonton.dat",
        "data_files/Halifax.dat",
        "data_files/Montreal.dat",
        "data_files/Ottawa.dat",
        "data_files/Quebec.dat",
        "data_files/Toronto.dat",
        "data_files/Vancouver.dat",
        "data_files/Victoria.dat",
        "data_files/Winnipeg.dat",
        NULL
    };
    clock_t start_t;
    clock_t end_t;
    double total_t;
    clock_t elapsed_t;
    
    start_t = clock();
    if (argc == 1){
        for (int i = 0; filePaths[i] != NULL; i++) {
            readFile(filePaths[i]);
        }
    }
    else if (argc == 2)
    {
        printf("input is './data_av in multithreading mode'\n");
    }
    else {
        printf("error: Too many arguments\n");
        exit(0);
    }

    end_t = clock();
    total_t = (double)(end_t-start_t)/CLOCKS_PER_SEC;
    elapsed_t = end_t-start_t;
    printf("===================================================\n");
    printf("Total values evaluatedis: %d\n", totalCount);
    printf("The lowest temperature overall is: %.1f reported in: %s\n", overallMin, overallMinCity);
    printf("The highest temperature overall is: %.1f reported in: %s\n", overallMax, overallMaxCity);
    printf("Elapsed time: %ld clocks\n", elapsed_t);    
    printf("\n");

    return 0;
}