all: my-hello fromc fromc.ll

my-hello: my-hello.ll
	clang my-hello.ll -o my-hello

fromc.ll: fromc.c
	clang -O0 -emit-llvm fromc.c -c -o fromc.bc
	llvm-dis < fromc.bc > fromc.ll

fromc: fromc.ll
	clang fromc.ll -o fromc

clean:
	rm -f my-hello fromc fromc.ll fromc.bc
