SRCS-y := $(shell find . -type f -name '*.cpp')
OBJECTS := $(patsubst ./%.cpp, build/%.o, $(SRCS-y))
OBJECTS := $(filter-out build/test.o, $(OBJECTS))
CXX = g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror -Wunused
INCLUDES := -I..
LDLIBS := -pthread

all: build $(OBJECTS)
	@$(CXX) $(OBJECTS) $(LDLIBS) -o app
	@echo "Building done!"

build/%.o : %.cpp
	@echo "Compiling $< ..."
	@$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

build:
	@mkdir -p build
	
clean:
	@rm -rf build app words_*
	@echo "Cleaning done!"
