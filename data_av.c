#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>

int totalCount = 0;
float overallMax = -100000;
float overallMin = 100000;
char overallMaxCity[100];
char overallMinCity[100];
pthread_mutex_t myMutex;
clock_t srt;
clock_t end;
clock_t difference;
pthread_t id[11];

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


void process_file(char* file){
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
        char spaces;

        // Allocate memory for the city name string
        char city[100]; 

        // Copy the substring between the first 11 characters and the last 4 characters
        strncpy(city, file + 11, strlen(file) - 11 - 4);
        city[strlen(file) - 11 - 4] = '\0';

        // look at each line in file f and extract data
        while(fgets(line, sizeof(line), f)) {
            // scan each line that follows (float) (float) formatd
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
        
        // output values
        printf("===================================================\n");
        printf("Data for: %s\n", city);
        printf("%s's lowest temperature is: %.1f degrees Celsius\n", city, min);
        printf("%s's highest temperature is: %.1f degrees Celsius\n", city, max);
        printf("The average temperature for %s is: %f degrees Celsius\n", city, average/count);
        printf("Total values processed for %s are: %d\n\n", city, (count/2));
        fclose(f);
        // check and update overall max and min
        if (max > overallMax) {
            overallMax = max;
            strcpy(overallMaxCity, city);
        }
        if (min < overallMin) {
            overallMin = min;
            strcpy(overallMinCity, city);
        }
}

void* threadExecution(void* thread){
    // get filename 
    char* filename = (char*) thread;
    // lock thread
    pthread_mutex_lock(&myMutex);
    // process the thread/file
    process_file(filename);
    // unlock thread
    pthread_mutex_unlock(&myMutex);
    // exit thread
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    // init thread
    pthread_mutex_init(&myMutex, NULL);
    // start time
    srt = clock();
    // single thread 
    if (argc == 1){
        printf("\n\n              REGULAR EXECUTION\n\n");
        for (int i = 0; filePaths[i] != NULL; i++) {
            process_file(filePaths[i]);
        }
    }
    // multithreading
    else if (strcmp(argv[1],"-m") == 0 ){
        printf("\n\n              THREADED EXECUTION\n\n");
        for (int i = 0; filePaths[i] != NULL; i++) {
            if(pthread_create(&id[i], NULL, threadExecution, filePaths[i])) {
                printf("error: failed to create thread\n");
                exit(0);
            }
        }    
        for (int i = 0; id[i] != NULL; i++) {
                if(pthread_join(id[i], NULL)) {
                    printf("error: failed to join thread\n");
                    exit(0);
            }
        }
    }
    // too many arguments
    else {
        printf("error: Wrong or too many arguments\n");
        exit(0);
    }
    // end time
    end = clock();

    printf("===================================================\n");
    printf("Total values evaluated is: %d\n", totalCount);
    printf("The lowest temperature overall is: %.1f reported in: %s\n", overallMin, overallMinCity);
    printf("The highest temperature overall is: %.1f reported in: %s\n", overallMax, overallMaxCity);
    printf("Elapsed time: %ld clocks\n", end - srt);    
    printf("\n");

    return 0;
}