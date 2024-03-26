EXE = intro
OBJS = main.o intro.o rgbapixel.o png.o

COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall -Werror -I/opt/homebrew/Cellar/libpng/1.6.43/include
LINKER = g++
LINKER_OPTS = -L/opt/homebrew/Cellar/libpng/1.6.43/lib -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp intro.h ./RGB/png.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

intro.o : intro.cpp ./RGB/png.h ./RGB/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) intro.cpp

rgbapixel.o : ./RGB/rgbapixel.cpp ./RGB/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) ./RGB/rgbapixel.cpp

png.o : ./RGB/png.cpp ./RGB/png.h
	$(COMPILER) $(COMPILER_OPTS) ./RGB/png.cpp

clean :
	-rm -f *.o $(EXE)

