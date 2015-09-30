CUDA_PATH      ?= /usr/local/cuda
COMPUTE        ?= 35

CC        := gcc
CFLAGS    := -Wall -Werror -O3 -lm
CXX       := g++
CXXFLAGS  := $(CFLAGS)
NVCC      := $(CUDA_PATH)/bin/nvcc
NVCCFLAGS := -arch=sm_$(COMPUTE) -O3 -lineinfo
LD        := $(NVCC)
LDFLAGS   := -O3
EXE       := findrings

## Add your source files here ##
CUDA_SRC  := 
C_SRC     := 
CPP_SRC   := timer.cpp
## End of source files lists ##

CUDA_OBJS := $(patsubst %.cu,%.cu.o,$(CUDA_SRC))
C_OBJS    := $(patsubst %.c,%.c.o,$(C_SRC))
CPP_OBJS  := $(patsubst %.cpp,%.cpp.o,$(CPP_SRC))


build: $(EXE)

$(EXE): $(CUDA_OBJS) $(C_OBJS) $(CPP_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.cu.o: %.cu
	$(NVCC) $(NVCCFLAGS) -c -o $@ $<

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(EXE) $(CUDA_OBJS) $(C_OBJS) $(CPP_OBJS)
