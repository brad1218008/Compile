cc:=gcc
oobj:=main.o parser.o

all:main
	
main:$(oobj)
	$(cc) -o $@ $^
clean:
	rm -f *.o
	rm main