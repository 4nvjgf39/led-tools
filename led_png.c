#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "readpng.h"

int main(int argc, char *argv[])
{
	int fd;
	FILE * fp;
	int line;
   
	ulg width, height, rowbytes;
        uch *img;
	int channels;
	
	fd = fopen("/dev/ws2812", O_WRONLY);
	if(fd<0)
	{
		fprintf(stderr, "Failed to open /dev/pwm_dma\n");
		exit(-1);
	}

	if(argc < 2)
	{
		fprintf(stderr, "LED sequence file missing\n");
		exit(-1);
	}

	fp = fopen(argv[1], "rt");
	if(fp == NULL)
	{
		fprintf(stderr, "Failed to open file %s\n", argv[1]);
		exit(-1);
	}

	readpng_init(fp, &width, &height);
	img = readpng_get_image(1.0, &channels, &rowbytes);
	
	for(line = 0; line < height; line++)
	{
		fwrite(fd, img, 25*4);
		img += rowbytes;
		usleep(30000);
	}
	
	fclose(fd);
}

