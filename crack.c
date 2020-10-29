/*
 * crack.c
 *
 *  Created on: 26 ott 2020
 *      Author: root-hunter
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_VAR 8  //length of incremental numerical sub_string
#define YEARS 2
#define RANGE (99999999*YEARS)+1
#define RANGE_Y 99999999
#define PASS_LEN 13  //total password len
#define INCREMENTAL_PART 8
#define EXP_FILE "mokeypass.txt" //path of exported password

#define F_YEAR 18 //first_year
#define S_YEAR 19 //second_year
#define T_YEAR 19 // .. year

typedef struct{
	char first[1];
	int second[3];
	char thrd[2];
	int fourth;
	char result[PASS_LEN+1];
	int set;
}pass;


void init_final(pass *x){
	x->first[0] = 'S';
	x->second[0] = F_YEAR;
	x->second[1] = S_YEAR;
	x->second[2] = T_YEAR;
	x->set = 0;
	strcpy(x->thrd, "2V");
	x->fourth = 0;

	x->result[0] = *x->first;

	char tmp_str[2];
	itoa(x->second[0],tmp_str, 10);
	x->result[1] = tmp_str[0];
	x->result[2] = tmp_str[1];
	x->result[3] = x->thrd[0];
	x->result[4] = x->thrd[1];

	char *tmp_count =calloc(10, sizeof(char));
	itoa(x->fourth, tmp_count,10);

	for(unsigned int i = 5; i < PASS_LEN; i++){
		x->result[i] = '0';
	}
	x->result[12] = '\0';
	//printf("MANNAFFIA A FACE A %s", x->result);

}

void to_file(FILE *x, pass *t){
	if(x == NULL){
		puts("Error, file is not open..");
	}else{
		fprintf(x,"%s\n",t->result);
	}
}


void updater(pass *x){

	char tmp_str[2];

	if(x->fourth > RANGE_Y){
		x->fourth = 0;
		++x->set;
		itoa(x->second[x->set],tmp_str, 10);
	}else{
		itoa(x->second[x->set],tmp_str, 10);
	}

		x->result[1] = tmp_str[0];
		x->result[2] = tmp_str[1];
		x->result[3] = x->thrd[0];
		x->result[4] = x->thrd[1];

		char tmp_count[10];
		itoa(x->fourth, tmp_count,10);
		if(strlen(tmp_count)<= INCREMENTAL_PART){
			for(unsigned int k = PASS_LEN-INCREMENTAL_PART; k < PASS_LEN-strlen(tmp_count); ++k){
				x->result[k] = '0';
			}


			for(unsigned int j = PASS_LEN-strlen(tmp_count),b = 0; j < PASS_LEN+1; ++j,++b){
				x->result[j] = tmp_count[b];
			}
		}
		x->result[13] = '\0';
		printf("%s\n", x->result); //enable if we want show a genereted pasword..

		++x->fourth;
}
int main(int argc, char **argv) {
	pass mypass;
	FILE *file = fopen(EXP_FILE, "w+");
	init_final(&mypass);
	for(unsigned int x = 0; x <= RANGE; ++x){
		updater(&mypass);
		//system("pause");
		to_file(file, &mypass);
	}

}

