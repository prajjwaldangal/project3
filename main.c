#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// to-do: check gcc version,
int main (int argc, const char *argv[]) {
    // 1. create arr
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
	// 1.1 rewind and insert chars into s	
	rewind(fp);
	int i = 0;
	printf("\n");
	while ((c = fgetc(fp)) != EOF) {
		s[i] = c;
		i++;
	}
	
	// 1.2 generate int arr
	int j = 0;
	int n_d = 0; // no. of integers
	while(j <= i) {
		if (s[i] == ' ')
			n_d ++;
		j ++;
	}
	n_d = i - n_d;
	int * arr = (int *) malloc(sizeof(int) * n_d);
	j = 0;
	int t = 0; // t is for tracking_index
	int arr_i = 0; // index into arr
	while (j <= i) {
		while (s[j] != ' ' && s[j] != '\0') {
			j += 1;
		}
		char * c_dig = (char *) malloc(sizeof(char)*(j-t));
		int k=t; // k -> "local var"
		while(k < j) {
			c_dig[k-t] = s[k];
			k += 1;
		}		
		int dig = atoi(c_dig);
		t = j+ 1;
		j += 1;
		
		arr[arr_i] = dig;
		arr_i ++;
		printf("dig: %d\n", dig); 		
	}
	
	printf("s_size: %d\ns: %s\n", s_size, s);
	for (int a=0; a <= arr_i; a++) {
		printf("%d ", arr[a]);
	}
    }
    // split into two, half1 and half2
    
    // sort half1 by thread1
    
    // sort half2 by thread2
    
    // merge two halves -> arr2 -> thread3
    
    return 0;
}
