CXX=g++
#CXXFLAGS=-Wall -I. -O2 -DNDEBUG
CXXFLAGS=-Wall -I. 
OBJS=Graph.o floyd_seq.o
PROGS=floyd_seq
floyd_seq: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
all: $(PROGS)
clean:
	rm -f *.o $(PROGS)
