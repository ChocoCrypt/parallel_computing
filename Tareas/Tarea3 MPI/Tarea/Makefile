BIN             := normalize reconstruct_ser reconstruct_mpi

INCLUDES        +=
LIBS            := -lgomp

CFLAGS          := -O3 -m64
LDFLAGS         := -fopenmp

CXX             := g++
MPIXX           := mpic++

C_SOURCCES	:=
HEADERS         :=

C_OBJS          := 


normalize: normalize.cpp pgmio.hpp
	$(CXX) $(CFLAGS) -o $@ normalize.cpp pgmio.cpp

reconstruct_ser: reconstruct_ser.cpp pgmio.hpp
	$(CXX) $(CFLAGS) -o $@ reconstruct_ser.cpp pgmio.cpp

reconstruct_mpi: reconstruct_mpi.cpp pgmio.hpp
	$(MPIXX) $(CFLAGS) -o $@ reconstruct_mpi.cpp pgmio.cpp


clean:                                                                        
	rm $(BIN) *.o core*   
