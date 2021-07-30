/*Give two file names as arguments*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include "list.h"
#include "file.h"
#include <sys/stat.h>



int main(int argc, char* argv[]){
	list l1, l2;
	list_lcs l;
	init(&l1);
	init(&l2);
	init_lcs(&l);
	char ch;
	char *line;
	line = (char *)malloc(sizeof(char) * 1000);
	int x;
	int fd[5];  //file descriptor
    int  flag_c = 0,  flag_w = 0, flag_b = 0, flag_i = 0, i, flag_u = 0, flag_y = 0;
    int opt;
    int error = 0;

    while((opt = getopt(argc, argv, ":ycwbiu")) != -1) {
    	switch(opt) {
    		case 'y':
    			flag_y = 1;
    			break;
    		case 'c':
    			flag_c = 1;
    			break;

    		case 'w':
    			flag_w = 1;
    			break;

    		case 'b':
    			flag_b = 1;
    			break;

    		case 'i':
    			flag_i = 1;
    			break;

			case 'u':
				flag_u = 1;
				break;

			default:
				error = 1;
				break;
    	}
    }
	if(error){
		printf("Invalid options\n");
		return 0;
	}

	if(optind == argc) {
		printf("Insufficient arguments : ");
		exit(0);
	}
	if(argc < 3 || argc > 4){
		if(argc < 3)
			printf("Less arguments\n");
		else
			printf("Too much arguments\n");

		exit(0);
	}

	int k = 0;
	for(i = optind; i < argc; i++) {
		fd[k++] = open(argv[i], O_RDONLY, S_IRUSR);
	}


	if(fd[0] == -1){
		printf("First file not opened\n");
		exit(0);
	}
	x = countlines(fd[0]);

	if(x == 0)
		l1.front = l1.rear = NULL;
	else{
		lseek(fd[0], SEEK_SET, 0);
		while(x){
			line = readline(fd[0], 0);
			addnode(&l1, line);
			x--;
		}
	}
	close(fd[0]);


	if(fd[1] == -1){
		printf("Second file not opened\n");
		exit(0);
	}
	x = countlines(fd[1]);

	if(x == 0)
		l2.front = l2.rear = NULL;
	else{
		lseek(fd[1], SEEK_SET, 0);
		while(x){
			line = readline(fd[1], 0);
			addnode(&l2, line);
			x--;
		}
	}
	close(fd[1]);

	if(flag_c == 1){
		l = lcs(l1, l2, 'c');
		_cdiff(l, l1, l2);
	}
	else if(flag_y == 1){
		l = lcs(l1, l2, 'y');
		_ydiff(l, l1, l2);
	}
	else if(flag_u){
		l = lcs(l1, l2, 'u');
		_udiff(l, l1, l2);
	}
	else if(flag_i || flag_w || flag_b ){
		if(flag_i == 1)
			ch = 'i';
		else if(flag_w == 1)
			ch = 'w';
		else
			ch = 'b';
		l = lcs(l1, l2, ch);
		diff(l, l1, l2);
	}

	else{
        l = lcs(l1, l2, '0');
        diff(l, l1, l2);
	}

		return 0;
}


