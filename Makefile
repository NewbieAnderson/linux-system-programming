all: src/file

src/file:
	gcc -o ./bin/fd ./file/fd.c
	gcc -o ./bin/fd_io ./file/fd_io.c
	gcc -o ./bin/fd_offset ./file/fd_offset.c
	gcc -o ./bin/fd_io_redirection ./file/fd_io_redirection.c
	gcc -o ./bin/fp ./file/fp.c
	gcc -o ./bin/fp_io ./file/fp_io.c