# Variables
CXX = g++
INCLUDES = -I include -I include/3rdparty
LIBS = -L ./libs/GLFW -lglfw3 -lgdi32 -lopengl32 
SRC_DIR = src
LIB_DIR = libs/glad
BIN_DIR = build/debug
TARGET = $(BIN_DIR)
LIBS_GAME = -L $(BIN_DIR) -lframework

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
LIB_FILES = $(LIB_DIR)/glad.c

# All rule
all: compile run

# Compile rule
compile:
	$(CXX) main.cpp $(SRC_FILES) $(LIB_FILES) -o $(TARGET)/sandbox.exe $(INCLUDES) $(LIBS)

compile_dll:
	$(CXX) -shared $(SRC_FILES) $(LIB_FILES) -o $(TARGET)/framework.dll $(INCLUDES) $(LIBS) -DBUILD_DLL

# Run rule
run:
	.\$(TARGET)/sandbox.exe

# Clean rule
clean:
	rm -rf $(BIN_DIR)/*.exe

dll: compile_dll

game:
	$(CXX) main.cpp -o $(TARGET)/sandbox.exe $(INCLUDES) $(LIBS_GAME)