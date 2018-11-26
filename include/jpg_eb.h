#include "jpge.h"
#include <dirent.h>


static int get_file_size(const char *pFilename);

int jpeg_to_jpeg(unsigned char *dest,unsigned char *src, unsigned int len, unsigned char ratio);


