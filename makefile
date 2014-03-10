CXX = g++
CXXFLAGS = -Wall -g -O3
#-std=gnu++98 -fPIC

LD_FLAGS = -Llib/cv  -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_flann -lopencv_objdetect
INCLUDE_FLAGS = -Iinclude/cv -Iinclude/intraface
INTRAFACE_LIB = lib/intraface/libintraface.a
#LIBFLAGS = -fopenmp

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJECTS =	$(BUILD_DIR)/mblbp-detect.o \
		$(BUILD_DIR)/binary_model_file.o \
		$(BUILD_DIR)/detector.o \
		$(BUILD_DIR)/main.o
			
TARGET = $(BIN_DIR)/detect

.PHONY: all clean

all: $(TARGET)
	
$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LD_FLAGS) $(INTRAFACE_LIB)
	
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDE_FLAGS)
clean:
	$(RM) $(TARGET) $(OBJECTS)
