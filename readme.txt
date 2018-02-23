file.txt should not start nor end with a space character (or it will display 0s in place of those spaces).

Appropriate comments are accompany the code in main.c which is the only src file.

Makefile
main:
	gcc -o sort -pthread main.c -std=c11

Run sort as: ./sort file.txt
