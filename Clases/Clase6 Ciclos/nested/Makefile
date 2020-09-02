BIN		:= nested nested_omp1 nested_omp2 \
		   reduction

CFLAGS		:= -std=c++14 #-O3 -m64                                         
LDFLAGS		:= -fopenmp

CXX		:= g++                                                          

HEADS		:=                                              
SRC		:=


nested: nested.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) nested.cpp

nested_omp1: nested_omp1.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) nested_omp1.cpp

nested_omp2: nested_omp2.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) nested_omp2.cpp

reduction: reduction.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) reduction.cpp

clean:
	rm $(BIN) *.o core*    
