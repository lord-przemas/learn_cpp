SRCS-y := $(shell find . -type f -name '*.cpp')
OBJECTS_CMP := $(patsubst ./%.cpp, build/%.o, $(SRCS-y))
OBJECTS_LIB := $(filter-out build/main.o, $(OBJECTS_CMP))
CXX = g++
CFLAGS := -std=c++17 -fpic
INCLUDES := -I..
LDLIBS := -L$(PWD) -lpolymorphism

all: build $(OBJECTS_CMP)
	@$(CXX) -shared $(OBJECTS_LIB) -o libpolymorphism.so
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
