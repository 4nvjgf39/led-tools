led_png: led_png.c readpng.c
	$(CC) -o $@ $^ -lpng -lz -lm
