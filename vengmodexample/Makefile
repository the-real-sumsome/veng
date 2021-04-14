vm.o: vm.c
	gcc -c -fPIC vm.c -o vm.o

libvengmodexample.so: vm.o
	gcc vm.o -shared -o libvengmodexample.so

all: libvengmodexample.so

clean:
	rm -r -f *.o
	rm -r -f *.so