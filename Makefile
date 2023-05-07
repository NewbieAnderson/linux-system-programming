all: src/file

src/file:
	gcc -o ./bin/fd ./file/fd.c
	gcc -o ./bin/io ./file/io.c
	gcc -o ./bin/offset ./file/offset.c
	gcc -o ./bin/io_redirection ./file/io_redirection.c
	gcc -o ./bin/fp ./file/fp.c