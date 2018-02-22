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
        
        size_t s_size=0;
	while ((c=fgetc(fp)) != EOF) {
		s_size += 1;
	}
	char * s = (char *) malloc(sizeof(char)*s_size);
	// rewind and insert chars into s	
	rewind(fp);
	int i = 0;
	printf("\n");
	while ((c = fgetc(fp)) != EOF) {
		s[i] = c;
		i++;
	}

	// convert to int, and insert into arr
	size_t int_arr_size = (int) s_size / 2 + 1;	
	//int * arr = 
	//strtok(s, " ");
	
	printf("s_size: %d\ns: %s\n, intarrsize: %d\n", s_size, s, int_arr_size);
    }
    // split into two, half1 and half2
    
    // sort half1 by thread1
    
    // sort half2 by thread2
    
    // merge two halves -> arr2 -> thread3
    
    return 0;
}
