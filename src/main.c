#include <stdio.h>
#include "jpg_eb.h"

int main(int argc, char *argv[]){

	if(argc < 2)
	{
		printf("Usage : <%s> no srcfile + no destfile\n",argv[0]);
		return -1;
	}
	unsigned char *src = (unsigned char *)argv[2];
	unsigned char *dest = (unsigned char *)argv[1];
	unsigned char ratio = 6;
	unsigned int len = 2;
    if(jpeg_to_jpeg(dest,src,len,ratio)){
        printf("sucess\n");
     }

	return 0;
}
