COMP = g++-8.3.0

SHARED_OBJS = _007_a.so 
OBJS = Algorithm.o
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
CPP_LINK_FLAG = -shared

all: $(SHARED_OBJS)

_007_a.so: $(OBJS)
	$(COMP) $(CPP_LINK_FLAG) -o $@ $^

Algorithm.o: Algorithm.h  Algorithm.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
	
clean:
	rm -f $(OBJS) $(SHARED_OBJS)
