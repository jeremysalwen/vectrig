CFLAGS+= -g -std=c99 -ftree-vectorizer-verbose=2 -lm -O3 -ffast-math -march=native -mtune=native
LDFLAGS+= -lm -g

all: optimizer run

optimizer: main.o optimizer.o

run: run.o main.o
