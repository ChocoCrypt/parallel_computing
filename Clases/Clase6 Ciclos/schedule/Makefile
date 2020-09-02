BIN		:= sch_static sch_dynamic sch_guided \
		   sch_auto sch_runtime

CFLAGS		:= -std=c++14 #-O3 -m64
LDFLAGS		:= -fopenmp

CXX		:= g++

HEADS		:= 
SRC		:=


sch_static: sch_static.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) sch_static.cpp

sch_dynamic: sch_dynamic.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) sch_dynamic.cpp

sch_guided: sch_guided.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) sch_guided.cpp

sch_auto: sch_auto.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) sch_auto.cpp

sch_runtime: sch_runtime.cpp $(HEADS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) sch_runtime.cpp


clean:
	rm $(BIN) *.o core*
