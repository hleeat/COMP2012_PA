CPPFLAGS = -std=c++11

all: pa4.exe

pa4.exe: doubleHashingHashTable.o linearProbingHashTable.o main.o openAddressingHashTable.o shop.o quadraticProbingHashTable.o
	g++ -o $@ $(CPPFLAGS) doubleHashingHashTable.o linearProbingHashTable.o main.o openAddressingHashTable.o shop.o quadraticProbingHashTable.o

%.o: %.cpp
	g++ $(CPPFLAGS) -c $<

depend:
	makedepend *.cpp

clean:
# On Windows, use: del *.o *.exe
	del *.o *.exe
# On Linux or MacOS, use: 
# rm -f *.o *.exe


# DO NOT DELETE
doubleHashingHashTable.o: doubleHashingHashTable.h hashTable.h openAddressingHashTable.h magic.h
linearProbingHashTable.o: linearProbingHashTable.h hashTable.h openAddressingHashTable.h magic.h
main.o: hashTable.h openAddressingHashTable.h magic.h shop.h doubleHashingHashTable.h linearProbingHashTable.h quadraticProbingHashTable.h
openAddressingHashTable.o: hashTable.h openAddressingHashTable.h magic.h
shop.o: shop.h hashTable.h
quadraticProbingHashTable.o: quadraticProbingHashTable.h hashTable.h openAddressingHashTable.h magic.h
