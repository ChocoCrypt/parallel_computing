BIN		:= list_trav list_trav_task 

CFLAGS		:= -std=c++14 -O3 -m64                                         
LDFLAGS		:= -fopenmp

CXX		:= g++

HEADS		:=                        
SRC		:=



list_trav: list_trav.cpp 
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ list_trav.cpp

list_trav_task: list_trav_task.cpp 
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ list_trav_task.cpp


clean:                                           
	rm $(BIN) *.o core*
