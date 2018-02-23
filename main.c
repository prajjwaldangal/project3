#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int * arr;
int arr_size=0;

void display_arr(int * array, int beg, int end);
void * worker(void * args);
int comp (const void * elem1, const void * elem2);

int main(int argc, const char * argv[]) {
	
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
	fclose(fp);
	
	printf("Original array: \n");
	display_arr(arr, 0, arr_size);
	
	pthread_t thread1, thread2, thread_m;
	pthread_attr_t attr1, attr2, attr_m;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr_m);
	
	char * args1 = "1";
	char * args2 = "2";
	char * args3 = "3";
	
	pthread_create(&thread1, &attr1, worker, (void *)args1);
	pthread_create(&thread2, &attr2, worker, (void *)args2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_create(&thread_m, &attr_m, worker, (void *)args3); 
	pthread_exit(NULL);
	return 0;
}

void display_arr(int array[], int beg, int end) {
	for (int i=beg; i< end; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void merge(int array[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int * L = (int *) malloc(sizeof(int)*n1);
    int * R = (int *) malloc(sizeof(int)*n2);
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void merge_sort(int array[], int l, int r) {
	if (l < r) {
		int m=l+(r-l)/2;
		merge_sort(array, l, m);
		merge_sort(array, m+1, r);
		merge(arr, l, m, r);
	}
}


void * worker(void * args) {
	char * num = (char *) args;
	int mid = arr_size / 2;
	if (*num == '1') {
		merge_sort(arr, 0, mid);
		printf("Sub array 1 sorted by thread1\n");
		display_arr(arr, 0, mid);
	} else if(*num == '2') {
		merge_sort(arr, mid+1, arr_size);
		printf("Sub array 2 sorted by thread2\n");
		display_arr(arr, mid+1, arr_size);
	} else {
		merge(arr, 0, mid, arr_size);
		printf("Merge arr by thread3\n");
		display_arr(arr, 0, arr_size);
	}
	pthread_exit(NULL);
}
