#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>


void readFile(char** filePaths){
    for (int i = 0; filePaths[i] != NULL; i++) {
        FILE* f = fopen(filePaths[i], "r");
        if(f == NULL) {
            printf("Error, file '%s' does not exsist\n", filePaths[i]);
            exit(0);
        }
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