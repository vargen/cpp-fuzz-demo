/*  
    Code to demonstrate various vulnerabilities in C/C++
    
    All code was taken from godbolt.org:

        https://godbolt.org/z/dozWv1aed
        https://godbolt.org/z/j14cve3cP
        https://godbolt.org/z/edorEaG4e
        https://godbolt.org/z/K1bsMebY1
        https://godbolt.org/z/1sjMfr4Px
*/


#include <iostream>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 10
#define BUFSIZER1 32
#define BUFSIZER2 ((BUFSIZER1/2) - 8)


//use after free
void malloc_and_free(char *argv) {
	char *buf1R1;
	char *buf2R1;
	char *buf2R2;
	char *buf3R2;
	buf1R1 = (char *) malloc(BUFSIZER1); //create buffer size 32
	buf2R1 = (char *) malloc(BUFSIZER1); //create 2nd buffer size 32

	free(buf2R1); //free 2nd buffer

	buf2R2 = (char *) malloc(BUFSIZER2); //create 3rd buffer size 8
	buf3R2 = (char *) malloc(BUFSIZER2); //create 4th buffer size 8
	strncpy(buf2R1, argv, BUFSIZER1-1); //copy input to the freed buffer
    printf("%s",buf2R1); //print from the freed buffer
	free(buf1R1);
	free(buf2R2);
	free(buf3R2);
}


//null pointer dereference
void print_iso_in_DMY(char* str){
   char year[BUFSIZE];
   char month[BUFSIZE];
   char day[BUFSIZE];
   const char s[] = "-";
   char *token = strtok(str, s);
   strncpy(year,token,BUFSIZE);
   token = strtok(NULL, s);
   strncpy(month,token,BUFSIZE);
   token = strtok(NULL, s);
   strncpy(day,token,BUFSIZE);
   printf(" %s.%s.%s\n", day, month, year);
}

//integer overflow or wraparound
char* duplicate_str(char* str, int str_len, long int duplicate_cnt) {
	char* duplicated = NULL;
	int it1 = 0;
	int it2 = 0;

	if (duplicate_cnt < 2) {
		return duplicated;
	}

	printf("Allocating %d bytes\n", (int)(duplicate_cnt * str_len * sizeof(char)));
	duplicated = (char*)malloc(duplicate_cnt * str_len * sizeof(char));

	for (it1 = 0; it1 < duplicate_cnt; ++it1) {
		for (it2 = 0; it2 < str_len; ++it2) {
			duplicated[it1 * str_len + it2] = str[it2];
		}
	}

	return duplicated;
}


void read_the_void(){
    constexpr auto length = 5;
    std::array<int,length> arr{};
    for(int i=0; i<= length; i++ ){
        std::cout << " " << arr[i];
    }
    std::cout << std::endl << "Done reading the void" << std::endl;
}

void write_to_the_void(){
    constexpr auto length = 5;
    std::array<int,length> arr{};
    arr[length] = 42;
    std::cout << arr[length];
    std::cout << std::endl << "Done writing to the void" << std::endl;
}


int main(){
    //read_the_void();
    //write_to_the_void();
    
    //char str0[] = "2022-06-22";
    char str1[] = "short test string";
    //char str2[] = "much longer test string to go past the maximum buffer size of 32";
    //malloc_and_free(str2);
    //print_iso_in_DMY(str1);

    char* duplicated_str = NULL;
	duplicated_str = duplicate_str(str1, strlen(str1), 20);
    return 0;
}






// int main(int argc, char** argv) {
// 	char* duplicated_str = NULL;
// 	long int duplicate_cnt = 0;

// 	if (argc != 3) {
// 		printf("usage: %s str duplicate_cnt\n", argv[0]);
// 		exit(1);
// 	}

// 	sscanf(argv[2], "%ld", &duplicate_cnt);
// 	printf("Amount of duplicates: %ld\n", duplicate_cnt);
// 	duplicated_str = duplicate_str(argv[1], strlen(argv[1]), duplicate_cnt);

// 	if (duplicated_str != NULL)
// 		printf("Duplicated string: %.128s...\n", duplicated_str);
// }