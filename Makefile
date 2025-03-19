# Compiler
NVCC = "$(CUDA_PATH)\bin\nvcc"
CXX  = g++

# Define directories
SRC_DIR  = src
BIN_DIR  = bin
DATA_DIR = data
LIB_DIR  = lib

# Compiler flags
CXXFLAGS =  -std=c++11 \
            -I "$(CUDA_PATH)\include" \
			-I $(LIB_DIR)\stb-master

CUDA_LIBS = -L"$(CUDA_PATH)\lib\x64" -lcudart 
NPP_LIBS  = -lnppc -lnppial -lnppicc -lnppidei -lnppif -lnppig -lnppim -lnppist -lnppisu -lnppitc

# Linker flags
LDFLAGS = $(CUDA_LIBS) $(NPP_LIBS)

# Source files
SRC = $(SRC_DIR)\gaussian_blur.cpp

# Target executable
TARGET = $(BIN_DIR)\gaussian_blur

IMAGE = outer_wilds_fanart.jpg

# Define the default rule
all: build

# Rule for building the target executable
build: $(SRC)
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@echo $(NVCC) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
	$(NVCC) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Rule for running the application
run: 
	$(TARGET) $(DATA_DIR)\$(IMAGE)

# Clean up
clean: 
	@if exist "$(BIN_DIR)" rd /s /q "$(BIN_DIR)"


# Installation rule (not much to install, but here for completeness)
install:
	@echo "No installation required."

# Help command
help:
	@echo "Available make commands:"
	@echo "  make        - Build the project."
	@echo "  make run    - Run the project."
	@echo "  make clean  - Clean up the build files."
	@echo "  make install- Install the project (if applicable)."
	@echo "  make help   - Display this help message."