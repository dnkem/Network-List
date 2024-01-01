objects = main.o Control.o View.o Network.o Entity.o List.o Message.o CellPhone.o Tower.o Location.o
testobjects = test.o TestControl.o Tester.o View.o Network.o Entity.o List.o Message.o CellPhone.o Tower.o Location.o

all: a3 test

a3: $(objects)
	g++ -o a3 $(objects) 

test: $(testobjects)
	g++ -o test $(testobjects)

test.o: test.cc TestControl.h
	g++ -c test.cc

main.o: main.cc Control.h 
	g++ -c main.cc 

Control.o: Control.h Control.cc
	g++ -c Control.cc
	
View.o: View.cc View.h
	g++ -c View.cc
	
Network.o: Network.cc Network.h
	g++ -c Network.cc

Entity.o: Entity.cc Entity.h
	g++ -c Entity.cc

List.o: List.h List.cc
	g++ -c List.cc

Message.o: Message.h Message.cc
	g++ -c Message.cc

	
CellPhone.o: CellPhone.cc CellPhone.h Entity.h
	g++ -c CellPhone.cc 

Tower.o: Tower.cc Tower.h 
	g++ -c Tower.cc

Location.o: Location.cc Location.h
	g++ -c Location.cc
	
Tester.o: Tester.cc Tester.h
	g++ -c Tester.cc

clean:
	rm -f a3 *.o