all: src/file

src/file:
	gcc -o ./bin/file/fd ./file/fd.c
	gcc -o ./bin/file/fd_io ./file/fd_io.c
	gcc -o ./bin/file/fd_offset ./file/fd_offset.c
	gcc -o ./bin/file/fd_io_redirection ./file/fd_io_redirection.c
	gcc -o ./bin/file/fp ./file/fp.c
	gcc -o ./bin/file/fp_io ./file/fp_io.c
	gcc -o ./bin/file/binary_io ./file/binary_io.c
	gcc -o ./bin/file/formatted_io ./file/formatted_io.c