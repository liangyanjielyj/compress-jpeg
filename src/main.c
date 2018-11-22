#include <stdio.h>
#include "jpg_eb.h"

int main(int argc, char *argv[]){

	if(argc < 2)
	{
		printf("Usage : <%s> no srcfile + no destfile\n",argv[0]);
		return -1;
	}
	
        //argv[2];//未压缩图片路径
        //argv[1];//压缩后图片的路径
	//接口参数，dest_name指针和src_name指针
        if(jpeg_tupian(argv[1],argv[2])){
                printf("sucess\n");
        }



	return 0;
}
