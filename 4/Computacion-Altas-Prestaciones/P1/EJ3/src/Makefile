CC = gcc
LIBS = -lm 
LIB_DIR = 
FLAGS = -O3 -march=native -fwhole-program -Wall -D_GNU_SOURCE 

.PHONY: clean all

all: greyScale greyScaleImprove clear

greyScale: greyScale.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ greyScale.c $(LIBS)

greyScaleImprove: greyScaleImprove.c stb_image_write.h stb_image.h
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ greyScaleImprove.c $(LIBS)

greyScaleIntrinsics: greyScaleIntrinsics.c stb_image_write.h stb_image.h 
	$(CC) $(FLAGS) -std=gnu99 $(LIB_DIR) -o $@ greyScaleIntrinsics.c $(LIBS)

stb_image.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

stb_image_write.h:
	@echo "Los ficheros de cabecera de stb se deberían descarga automáticamente"
	@echo "En caso de fallo, descargadlo de https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h"
	wget --no-check-certificate https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h

clean:
	rm -f *.o *~ greyScale greyScaleImprove 
	
clear:
	rm -f *.o *~
