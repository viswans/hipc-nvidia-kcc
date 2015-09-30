# hipc-nvidia-kcc
K closest circles problem for hipc nvidia track

### Build And Source Instructions
1. `make` generates object files in obj and executable as KCC
2. `make clean` cleans up object directory and deletes KCC
3. Add sources to src. For cuda code I will modify the makefile to take in nvcc compiler to build the cuda parts in the code
4. Split the header files into the include directory. Need to modify makefile to generate dependency based on headers - right now, have to `make clean` and `make` everytime the headers are changed`
