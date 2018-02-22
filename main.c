#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp (const void * elem1, const void * elem2);
void sort (int * arr);

// 1. create arr
int * arr; 
int arr_i = 0; // arr_length -> inappropriately named
// to-do: check gcc version,
int main (int argc, const char *argv[]) {
    // 1.1 
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
	// 1.2 rewind and insert chars into s	
	rewind(fp);
	int i = 0;
	printf("\n");
	while ((c = fgetc(fp)) != EOF) {
		s[i] = c;
		i++;
	}
	
	// 1.3 generate int arr
	int j = 0;
	int n_d = 0; // no. of integers
	while(j <= i) {
		if (s[i] == ' ')
			n_d ++;
		j ++;
	}
	n_d = i - n_d;
	j = 0;
	arr = (int *) malloc(sizeof(int) * n_d);
	int t = 0; // t is for tracking_index
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
    // 2. split into two, half1 and half2
    printf("arr_i = %d\n", arr_i);
    int len_arr1 = (int)arr_i/2;
    int len_arr2 = arr_i - len_arr1;
    int * arr1 = (int *)malloc(sizeof(int)*len_arr1);
    int * arr2 = (int *)malloc(sizeof(int)*len_arr2);
    // insert into arr1
    int k;
    for (k=0; k <= len_arr1; k++) {
	arr1[k] = arr[k];
    }
    // insert into arr2
    for (k=1; k <= len_arr2; k++) {
	arr2[k-1] = arr[len_arr1+k];
    }
    // output arr1
    printf("Array1:\n");
    for (k=0; k <= len_arr1; k++) {
	printf("%d ", arr1[k]);
    }
    printf("\n");
    printf("Array2:\n");
    // output arr2
    for (k=0; k <= len_arr2; k++) {
	printf("%d ", arr2[k]);
    }
    printf("\n");
        
    // 3. sort half1 by thread1
    // create thread1
    pthread_t thread1, thread2;
    //pthread_create(&tid, NULL,  
    // sort using thread1
    sort(arr1);
    // create thread2
    // sort using thread2
   
    
    // sort half2 by thread2
    
    // merge two halves -> arr2 -> thread3
    
    return 0;
}

void sort(int * arr) {
	qsort(arr, sizeof(arr)/sizeof(*arr), sizeof(*arr), comp);
}

int * comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
