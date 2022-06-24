/*  
    Code to demonstrate various vulnerabilities in C/C++
    
    All code was adapted from godbolt.org:

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


void malloc_and_free(char *input, int size) {
    if(size < 20)
        return;

    if(input[0] != 'F')
        return;
    
    if(input[1] != 'u')
        return;

    if(input[2] != 'z')
        return;
    
    if(input[3] != 'z')
        return;
    
	char *buf1R1;
	char *buf2R1;
	char *buf2R2;
	char *buf3R2;
	buf1R1 = (char *) malloc(BUFSIZER1); 
	buf2R1 = (char *) malloc(BUFSIZER1); 

	free(buf2R1); 

	buf2R2 = (char *) malloc(BUFSIZER2);
	buf3R2 = (char *) malloc(BUFSIZER2);
	strncpy(buf2R1, input, BUFSIZER1-1); 
    printf("%s",buf2R1);
	free(buf1R1);
	free(buf2R2);
	free(buf3R2);
}


void print_iso_in_DMY(char* input, int size){
    if(size < 20)
        return;

    if(input[0] != 'a')
        return;
    
    if(input[1] != 'd')
        return;

    if(input[2] != '2')
        return;
    
    if(input[3] != '!')
        return;

    char year[BUFSIZE];
    char month[BUFSIZE];
    char day[BUFSIZE];
    const char s[] = "-";
    char *token = strtok(input, s);
    strncpy(year,token,BUFSIZE);
    token = strtok(NULL, s);
    strncpy(month,token,BUFSIZE);
    token = strtok(NULL, s);
    strncpy(day,token,BUFSIZE);
    printf(" %s.%s.%s\n", day, month, year);
}


char* duplicate_str(char* input, int str_len, long int duplicate_cnt) {
    if(str_len < 30)
       return NULL;

    if(input[0] != 'z')
        return NULL;
    
    if(input[1] != 'z')
        return NULL;

    if(input[2] != 'u')
        return NULL;
    
    if(input[3] != 'F')
        return NULL;
    
    if(duplicate_cnt < 2)
        return NULL;
	
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
			duplicated[it1 * str_len + it2] = input[it2];
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

    char str0[] = "2022-06-22";
    char str1[] = "FUZZ short test string";
    char str2[] = "FUZZ longer test string for checking buffer size";
    malloc_and_free(str2, strlen(str2));
    print_iso_in_DMY(str0, strlen(str0));

    char* duplicated_str = NULL;
	duplicated_str = duplicate_str(str1, strlen(str1), 20);
    return 0;
}

