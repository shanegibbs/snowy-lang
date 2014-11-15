all: my-hello fromc.ll

my-hello: my-hello.ll
	clang my-hello.ll -o my-hello

fromc.ll: fromc.c
	clang -O3 -emit-llvm fromc.c -c -o fromc.bc
	llvm-dis < fromc.bc > fromc.ll
