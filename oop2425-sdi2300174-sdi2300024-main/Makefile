CXX = g++
CXXFLAGS = -g

PROGRAM = oop24

SRCS = oop24.cpp Helper.cpp User.cpp Product.cpp Admin.cpp Customer.cpp
OBJS = $(SRCS:.cpp=.o)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)

.PHONY: all clean