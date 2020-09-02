BIN		:= barrier critical atomic

CFLAGS		:= -std=c++14 #-O3 -m64                                         
LDFLAGS		:= -fopenmp                                                     

CXX		:= g++                                                          

HEADS		:=                                                              
SRC		:=


barrier: barrier.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) barrier.cpp

critical: critical.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) critical.cpp

atomic: atomic.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) atomic.cpp


clean:                                                                          
	rm $(BIN) *.o core*            
