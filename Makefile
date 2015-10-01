# copied from the files added by Akshay
# this looks much more comprehensive
CUDA_PATH      ?= /usr/local/cuda
COMPUTE        ?= 35

CC        := gcc
CFLAGS    := -I include -Wall  -O3 -lm
CXX       := g++
CXXFLAGS  := $(CFLAGS)
NVCC      := $(CUDA_PATH)/bin/nvcc
NVCCFLAGS := -arch=sm_$(COMPUTE) -O3 -lineinfo
LD        := $(NVCC)
LDFLAGS   := -O3
EXE       := findrings

## Add your source files here ##
SRC_DIR   := src
CUDA_SRC  := $(wildcard $(SRC_DIR)/*.cu)
C_SRC     := $(wildcard $(SRC_DIR)/*.c)
CPP_SRC   := $(wildcard $(SRC_DIR)/*.cpp)
## End of source files lists ##

OBJ_DIR   := obj
CUDA_OBJS := $(patsubst $(SRC_DIR)/%.cu,$(OBJ_DIR)/%.cu.o,$(CUDA_SRC))
C_OBJS    := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.c.o,$(C_SRC))
CPP_OBJS  := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.cpp.o,$(CPP_SRC))


build: $(EXE)

$(EXE): $(CUDA_OBJS) $(C_OBJS) $(CPP_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.cu.o: $(SRC_DIR)/%.cu
	$(NVCC) $(NVCCFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(EXE) $(CUDA_OBJS) $(C_OBJS) $(CPP_OBJS)
