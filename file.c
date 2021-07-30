#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "list.h"
#include <sys/stat.h>
#include <sys/types.h>

int countlines(int fd) {  //returns the number of lines in a file
	int count = 0;
	char ch;
	while(read(fd, &ch, 1)) {
		if(ch == '\n')
			count++;
	}
	return count;
}
char *readline(int fd, int flag_w) {  //used to read the file
	char ch;
	int i = 0;
	char *s = (char *)malloc(sizeof(char)*1000);
	while(read(fd, &ch, 1)) {
		if(flag_w == 1) {    //flag_w = 1 indicates that we can read the file neglecting spaces and digits
			if(ch != '\n')
				if(ch != ' ' && ch != 9) //if space or digit encounters then continue
					s[i++] = ch;
				else
					continue;
			else {
				s[i++] = '\0';
				break;
			}
		}
		else {
			if(ch != '\n')  //this is used to store character as well if there are more than one lines in file
				s[i++] = ch;
			else {
				s[i++] = '\0';
				break;
			}

		}
	}
	return s;
}



