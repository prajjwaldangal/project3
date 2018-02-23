Input requirements:

1. file.txt should not start nor end with a space character (or it will display 0s in place of those spaces).

2. all integers should be in one single line, separated by ' ' character.

Appropriate comments accompany the code in main.c which is the only src file.

Makefile

main:
	gcc -o sort -pthread main.c -std=c11


To make:
	make
	
To Run: 
	./sort file.txt
	
Note: To be used with Jessie Linux that comes with the book.

