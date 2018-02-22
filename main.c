#include <stdio.h>
#include <stdlib.h>

int arr_size = 0;
int * arr;
char * read_integers(const char * filename);

int main(int argc, const char * argv[]) {
	// 1.1 get command line arguments
	printf("args count: %d, filename: %s\n", argv[1]);
	const char * filename = argv[1];
	char * s = read_integers(filename);
	printf("%s", s);
	return 0;
}

char * read_integers(const char * filename) {
	char * s;
	FILE * fp = fopen(filename, "r");
	if (fp==NULL) {
		fprintf(stderr, "error opening file");
	} else {
		char c;
		size_t s_size=0;
		while ((c=fgetc(fp)) != EOF) {
			s_size ++;
		}
		s = (char *) malloc(sizeof(char) * s_size);
		// 1.2 rewind and insert chars into s
		rewind(fp);
		int i = 0;
		while ((c=fgetc(fp)) != EOF) {
			s[i] = c;
			i ++ ;
		}
	}
	return s;
}
