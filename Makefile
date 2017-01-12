

TARGET=cube
CPPSRCS = main.cc Cube.cc CubeGL.cc
#CPPSRCS = main_test.cc Cube.cc

OBJS = $(CPPSRCS:.cc=.o)
LDFLAGS = -lglut -lGL -lGLU


all: $(TARGET)


$(TARGET): $(OBJS)
	g++ -o $@ $^ $(LDFLAGS)

%.o: %.cc
	g++ -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
