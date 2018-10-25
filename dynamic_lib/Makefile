SRCS-y := $(shell find . -type f -name '*.cpp')
OBJECTS_CMP := $(patsubst ./%.cpp, build/%.o, $(SRCS-y))
OBJECTS_LIB := $(filter-out build/main.o, $(OBJECTS_CMP))
CXX = g++
CFLAGS := -std=c++17 -fpic
INCLUDES := -I..
LDLIBS := -L/home/przemas/proj/learn_cpp/dynamic_lib -lbluered

all: build $(OBJECTS_CMP)
	@$(CXX) -shared $(OBJECTS_LIB) -o libbluered.so
	@$(CXX) build/main.o $(LDLIBS) -o app
	@echo "Building done!"

build/%.o : %.cpp
	@echo "Compiling $< ..."
	@$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

build:
	@mkdir -p build
	
clean:
	@rm -rf build app
	@echo "Cleaning done!"
