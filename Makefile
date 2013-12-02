CC = gcc
AR = ar
CFLAGS = -g
LFLAGS = -lffmpeg
INCLUDE = -L/home/aetelelink/ffmpeg_multitask/libffmpeg-c/ffmpeg
RLINK_PATH = /home/aetelelink/ffmpeg_multitask/libffmpeg-c/lib/	
LDFLAGS = -Wl,-rpath-link,$(RLINK_PATH)

TGT = ffmpeg_multitask

OBJS =  ffmpeg_multitask.o

build = \
	@if [ -z "$V" ]; then \
		echo '	[$1]	$@'; \
		$2; \
	else \
		echo '$2'; \
		$2; \
	fi

% : %.o
	$(call build,LINK,$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) $(OBJS)  -o $@ $(LFLAGS))

%.o : %.c 
	$(call build,CC,$(CC) $(CFLAGS) -c $< -o $@)

%.a : %.o
	$(call build,AR,$(AR) rcs $@ $^)


all: $(OBJS) $(TGT)

ffmpeg_multitask.o: ffmpeg_multitask.c ffmpeg_multitask.h

clean: 
	rm -f *.o $(OBJS) $(TGT)
