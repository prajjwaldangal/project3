#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// to-do: check gcc version,
int main (int argc, const char *argv[]) {
    // create arr
    printf("filename: %s, args count: %d\n", argv[1], argc);
    const char * filename = argv[1];
    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error opening file\n");
    } else {
        char c;
        char * s = (char *) malloc(1);
        int i=1;
        while ( (c = fgetc(fp)) != EOF ) {
            if (i % 2 != 1) {
                strcat(s, &c);
            }
            i += 1;
            s = (char *) realloc(s, i);
        }
        // char * strtok ( char * str, const char * delimiters );
        // splits a given string *str by delimiter
        strtok(s, " ");
        printf("%s\n", s);
        fclose(fp);
        free(s);
    }
    // split into two, half1 and half2
    
    // sort half1 by thread1
    
    // sort half2 by thread2
    
    // merge two halves -> arr2 -> thread3
    
    return 0;
}
