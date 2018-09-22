SRCS-y := $(shell find . -type f -name '*.cpp' -or -name '*.asm')
OBJECTS := $(patsubst ./%.cpp, build/%.o, $(SRCS-y))
OBJECTS := $(patsubst ./%.asm, build/%.o, $(OBJECTS))
OBJECTS := $(filter-out build/test.o, $(OBJECTS))
CXX = g++
CFLAGS := -std=c++17 -g
ASM_FLAGS := -g
INCLUDES := -I..
LDLIBS := 

all: build $(OBJECTS)
	@$(CXX) $(CFLAGS) $(OBJECTS) $(LDLIBS) -o app
	@echo "Building done!"

build/%.o : %.cpp
	@echo "Compiling $< ..."
	@$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

build/%.o : %.asm
	@echo "Compiling $< ..."
	@nasm $(ASM_FLAGS) -f elf64 $< -o $@

build:
	@mkdir -p build
	
clean:
	@rm -rf build app
	@echo "Cleaning done!"
