CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I./
SRCS = pendule.c
OBJS = $(SRCS:.c=.o)
MAIN = pendule


.PHONY: depend clean

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)
        
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

