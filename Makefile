#
# Makefil
# Computer Networking Programing Assignments
#

CXX = g++
LD = g++
CXXFLAGS = -g -pthread -std=c++11
LDFLAGS = -g -pthread

#
# Any libraries we might need.
#
LIBRARYS = -lpthread

AlgoBowl: AlgoBowl.o
	${LD} ${LDFLAGS} AlgoBowl.o -o $@ ${LIBRARYS}

AlgoBowl.o : AlgoBowl.cpp
	${CXX} -c ${CXXFLAGS} -o $@ $<

#
# Please remember not to submit objects or binarys.
#
clean:
	rm -f core AlgoBowl.o
