basic_test: serialize deserialize
	./serialize < test.dat

serialize: serialize.o helpers.o 
	gcc -Wall -o serialize serialize.o helpers.o

deserialize: deserialize.o helpers.o 
	gcc -Wall -o deserialize deserialize.o helpers.o 

serialize.o: serialize.c
	gcc -c serialize.c

deserialize.o: deserialize.c
	gcc -c deserialize.c

helpers.o: helpers.c
	gcc -c helpers.c

clean:	
	rm -f *.o serialize deserialize