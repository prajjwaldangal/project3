#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct sort_args {
	int * arr;
	int size;
};
typedef struct sort_args sort_args;

void display_arr(int * arr, int size);
void * sort(void * args);
int comp (const void * elem1, const void * elem2);

int main(int argc, const char * argv[]) {
	int arr_size = 0;
	int * arr;
	// 1.1 get command line arguments
	printf("args count: %d, filename: %s\n", argc, argv[1]);
	const char * filename = argv[1];
	FILE *fp = fopen(filename, "r");
	// find no. of integers to read
	char c;
	while ((c=getc(fp)) != EOF) {
		if (c == ' ') {
			arr_size ++;
		}
	}	
	arr_size++;
	arr = (int *) malloc(sizeof(int) * arr_size);
	int i = 0;
	rewind(fp);
	while ((fscanf(fp, "%d", &arr[i])) == 1) {
		i++;
	}
	
	int len_sub_arr1 = (int) arr_size/2;
	int len_sub_arr2 = arr_size - len_sub_arr1;
	int * sub_arr1 = (int *)malloc(sizeof(int)*len_sub_arr1);
	int * sub_arr2 = (int *)malloc(sizeof(int)*len_sub_arr2);
	for (int j=0; j < arr_size; j++) {
		if (j <= len_sub_arr1) {
			sub_arr1[j] = arr[j];
		} else {
			sub_arr2[j-len_sub_arr1-1] = arr[j];
		}
	}
	printf("Original array: \n");
	display_arr(arr, arr_size);
	
	pthread_t thread1, thread2;
	// args1 is for arr1, args2 is for arr2
	sort_args * args1 = (sort_args*)malloc(sizeof(sort_args));
	args1->arr = sub_arr1;
	args1->size = len_sub_arr1;
	sort_args * args2 = (sort_args*)malloc(sizeof(sort_args));
	args2->arr = sub_arr2;
	args2->size = len_sub_arr2;
	
	pthread_create(&thread1, NULL, sort, (void *)args1);
	pthread_create(&thread2, NULL, sort, (void *)args2);
	printf("Sub array zzz: \n");
    	display_arr(args1->arr, args1->size);
	pthread_exit(NULL);
	return 0;
}

void display_arr(int * arr, int size) {
	for (int i = 0; i < size; i ++ ) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void * sort(void * args) {
    sort_args * sa = (sort_args *)args;
    //int * arr = sa->arr;
    //int size = sa->size; 
    qsort(sa->arr, sa->size, sizeof(sa->arr), comp);
    printf("Sub array 1: \n");
    display_arr(sa->arr, sa->size);
}

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
