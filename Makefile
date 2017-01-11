

TARGET=cube
CPPSRCS = Cube.cc main.cc


OBJS = $(CPPSRCS:.cc=.o)
LDFLAGS = -lglut -lGL -lGLU


all: $(TARGET)


$(TARGET): $(OBJS)
	g++ -o $@ $^ $(LDFLAGS)

.cc.o:
	g++ -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
