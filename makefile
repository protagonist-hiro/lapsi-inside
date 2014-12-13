CC = gcc
CFLAGS = $(shell pkg-config --cflags gstreamer-1.0 gtk+-3.0 gstreamer-video-1.0 gstreamer-audio-1.0 )
LIBS = $(shell pkg-config --libs gstreamer-1.0 gtk+-3.0 gstreamer-video-1.0 gstreamer-audio-1.0)
SOURCES = lapsi-backend.c main.c lapsipc.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLES = lapsi
all : $(SOURCES) $(EXECUTABLES)
$(EXECUTABLES) : $(OBJECTS)
	$(CC) $(OBJECTS)  $(LIBS) $(CFLAGS) -o $@
%.o : %.c
	$(CC) $(SOURCES) $(CFLAGS) -c

clean:
	rm -rf *.o
