BIN		:=


CFLAGS		:= -std=c++14 -O3 -m64                                         
LDFLAGS		:= -fopenmp

CXX		:= g++

HEADS		:= generate_random.hpp                        
SRC		:= generate_random.cpp



merge_sort: merge_sort.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) merge_sort.cpp

merge_sort_mod: merge_sort_mod.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) merge_sort_mod.cpp

merge_sort_omp: merge_sort_omp.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) merge_sort_omp.cpp

merge_sort_mod_omp: merge_sort_mod_omp.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) merge_sort_mod_omp.cpp

insertion_sort: insertion_sort.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) insertion_sort.cpp

generate: generate.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) generate.cpp


clean:                                           
	rm $(BIN) *.o core*
