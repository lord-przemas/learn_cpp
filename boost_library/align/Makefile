SRCS-y := $(shell find . -type f -name '*.cpp')
OBJECTS := $(patsubst ./%.cpp, build/%.o, $(SRCS-y))
OBJECTS := $(filter-out build/test.o, $(OBJECTS))
CXX = g++
CFLAGS := -std=c++17
INCLUDES := -I.. -I/home/przemas/proj/cpp/boost_1_69_0
LDLIBS := 

all: build $(OBJECTS)
	@$(CXX) $(CFLAGS) $(OBJECTS) $(LDLIBS) -o app
	@echo "Building done!"

build/%.o : %.cpp
	@echo "Compiling $< ..."
	@$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

build:
	@mkdir -p build
	
clean:
	@rm -rf build app
	@echo "Cleaning done!"
