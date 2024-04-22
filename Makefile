CC = gcc
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

C++ = g++

.PHONY: build clean

build: servere colorare compresie criptat oferta 

run-p1:
	./servere
run-p2:
	./colorare
run-p3:
	./compresie
run-p4:
	./criptat
run-p5:
	./oferta

p1: servere.cpp
	$(C++) -o $@ $^ $(CCFLAGS)
p2: colorare.cpp
	$(C++) -o $@ $^ $(CCFLAGS)
p3: compresie.cpp
	$(C++) -o $@ $^ $(CCFLAGS)
p4: criptat.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p5: oferta.cpp
	$(C++) -o $@ $^ $(CCFLAGS)

clean:
	rm -f servere colorare compresie criptat oferta