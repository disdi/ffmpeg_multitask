CC=gcc
HEADES_DIR= /usr/local/include/libffmpeg
LIB_DIR= /usr/local/lib

INCLUDES=	include/libffmpeg.h
			 
			
SOURCES=	src/libffmpeg.c 
			
			
LIBS_OLD= 		-lavcodec -lavformat -lavdevice \
			-lavutil -lswscale -lpostproc \
			-lavfilter -Llibpostproc

LIBS= 		/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/libavcodec.so \
		/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/libavformat.so \
		/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/libavdevice.so \
		/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/libavutil.so \
		/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/libswscale.so \
		/home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/libavfilter.so

ALL: libffmpeg.so

libffmpeg.so: $(INCLUDES) $(SOURCES)
	$(CC) $(INCLUDES) $(SOURCES) \
	-shared $(LIBS) -g \
	-fPIC \
	-o libffmpeg.so
	
clean:
	rm -f *.o libffmpeg.so

install: libffmpeg.so $(INCLUDES)
	install -d $(HEADES_DIR)
	install -t $(HEADES_DIR) include/libffmpeg.h
	install -t $(LIB_DIR) libffmpeg.so
