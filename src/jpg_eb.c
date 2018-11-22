#include <iostream>
using namespace std;
#include <stdio.h>
#include "jpge.h"
#include "stb_image.c"
#include <vector>
#include <dirent.h>
#include <string>
#include "jpg_eb.h"

static int get_file_size(const char *pFilename)
{
  FILE *pFile = fopen(pFilename, "rb");
  if (!pFile) return 0;
  fseek(pFile, 0, SEEK_END);
  uint file_size = ftell(pFile);
  fclose(pFile);
  return file_size;
}

int jpeg_to_jpeg(const char *dest,const char *src)
{
	int quality_factor = 5;//ÉèÖÃÑ¹ËõÏµÊý
	DIR* dir = opendir(src);
	dirent* p;  
	while(p = readdir(dir))	
	{
		if(p->d_name[0] != '.')
		{
			string name = src + string(p->d_name);
			string dname = dest + string(p->d_name);
			const char* pSrc_filename = name.c_str();
			const char* pDst_filename = dname.c_str();

			bool test_memory_compression = true;
			bool optimize_huffman_tables = false;
			int subsampling = -1;
			char output_filename[256] = "";
			if ((quality_factor < 1) || (quality_factor > 100))
			{
				cout << "Quality factor must range from 1-100!\n" << endl;
				return EXIT_FAILURE;
			}
			// Load the source image.
			const int req_comps = 3; // request RGB image
			int width = 0, height = 0, actual_comps = 0;
			uint8 *pImage_data = stbi_load(pSrc_filename, &width, &height, &actual_comps, req_comps);
			if (!pImage_data)
			{
				cout << "Failed loading file: " << pSrc_filename << endl;
				return EXIT_FAILURE;
			}
			
			cout << "33Source file: " << pSrc_filename << ", width: " << width << ", height: " << height << ", actual_comps: " << actual_comps << endl;
			
			// Fill in the compression parameter structure.
			struct params params_1;
			params_1.m_quality = quality_factor;
			params_1.m_subsampling = (subsampling < 0) ? ((actual_comps == 1) ? Y_ONLY : H2V2) : static_cast<subsampling_t>(subsampling);
			params_1.m_two_pass_flag = optimize_huffman_tables;
			
			cout << "44Writing JPEG image to file: " << pDst_filename << endl;
	
			// Now create the JPEG file.
			if (test_memory_compression)
			{
				int buf_size = width * height * 3; 
				if (buf_size < 1024) buf_size = 1024;
				void *pBuf = malloc(buf_size);
			
				if (!compress_image_to_jpeg_file_in_memory(pBuf, buf_size, width, height, req_comps, pImage_data, params_1))
				{
					cout << "Failed creating JPEG data!\n" << endl;
					return EXIT_FAILURE;
				} 
			
				FILE *pFile = fopen(pDst_filename, "wb");
				if (!pFile)
				{
					cout << "Failed creating file: " << pDst_filename << endl;
					return EXIT_FAILURE;
				}
			
				if (fwrite(pBuf, buf_size, 1, pFile) != 1)
				{
					cout << "Failed writing to output file!" << endl;
					return EXIT_FAILURE;
				}
			
				if (fclose(pFile) == EOF)
				{
					cout << "Failed writing to output file!" << endl;
					return EXIT_FAILURE;
				}
			}
			else
			{
				cout << "Failed to compress image!" << endl;
				return EXIT_FAILURE;
			}
			
			const uint total_pixels = width * height;
		}
	}
  cout << "Success.\n" << endl;
  

//	}
//	closedir(dir);	
  return EXIT_SUCCESS;
}
