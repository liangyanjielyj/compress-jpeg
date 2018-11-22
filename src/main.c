#include <stdio.h>
#include "jpg_eb.h"

int main(int argc, char *argv[]){

	if(argc < 2)
	{
		printf("Usage : <%s> no srcfile + no destfile\n",argv[0]);
		return -1;
	}
	
    if(jpeg_to_jpeg(argv[1],argv[2])){
        printf("sucess\n");
     }

	return 0;
}
