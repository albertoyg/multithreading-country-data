#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>





void readFile(char** filePaths){
    // start loop to get data for each file 
    for (int i = 0; filePaths[i] != NULL; i++) {
        // open file 
        FILE* f = fopen(filePaths[i], "r");
        // check if file actually opened / exists 
        if(f == NULL) {
            printf("Error, file '%s' does not exsist\n", filePaths[i]);
            exit(0);
        }
        // init min and max temp values, curMin and curMax, line length, and count
        float max = -100000;
        float min = 100000;
        char line[500];
        float curMax = 0;
        float curMin = 0;
        int count = 0;
        // look at each line in file f and extract data
        while(fgets(line, sizeof(line), f)) {
            // scan each line that follows (float) (float) format
            sscanf(line, "%f %f", &curMax, &curMin);
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
        }
        printf("for '%s' max temp = '%f' min temp = '%f'\n", filePaths[i], max, min);
        fclose(f);
    }
    
}


int main(int argc, char* argv[]){
    char* filePaths[10] = {
        "data_files/Charlottetown.dat",
        "data_files/Edmonton.dat",
        "data_files/Halifax.dat",
        "data_files/Montreal.dat",
        "data_files/Ottawa.dat",
        "data_files/Quebec.dat",
        "data_files/Toronto.dat",
        "data_files/Vancouver.dat",
        "data_files/Victoria.dat",
        "data_files/Winnipeg.dat"
    };
    
    if (argc == 1){
        printf("ready to process with multithreading disabled'\n");
        readFile(filePaths);
    }
    else if (argc == 2)
    {
        printf("input is './data_av in multithreading mode'\n");
    }
    else {
        printf("error: Too many arguments\n");
    }
        
    return 0;
}