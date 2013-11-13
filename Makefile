CC = gcc
AR = ar
CFLAGS = -g
LFLAGS = -lavformat -lavcodec -lavutil

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
	$(call build,LINK,$(CC) $(CFLAGS) $(OBJS)  -o $@ $(LFLAGS))

%.o : %.c 
	$(call build,CC,$(CC) $(CFLAGS) -c $< -o $@)

%.a : %.o
	$(call build,AR,$(AR) rcs $@ $^)


all: $(OBJS) $(TGT)

ffmpeg_multitask.o: ffmpeg_multitask.c ffmpeg_multitask.h

clean: 
	rm -f *.o $(OBJS) $(TGT)
