all: src/error src/file src/thread

src/error:
	gcc -o ./bin/error/perror ./error/perror.c
	gcc -o ./bin/error/strerror_r ./error/strerror_r.c
	gcc -o ./bin/error/strerror ./error/strerror.c

src/file:
	gcc -o ./bin/file/binary_io ./file/binary_io.c
	gcc -o ./bin/file/buf_mode ./file/buf_mode.c
	gcc -o ./bin/file/epoll ./file/epoll.c
	gcc -o ./bin/file/fd_io_redirection ./file/fd_io_redirection.c
	gcc -o ./bin/file/fd_io ./file/fd_io.c
	gcc -o ./bin/file/fd_offset ./file/fd_offset.c
	gcc -o ./bin/file/fd ./file/fd.c
	gcc -o ./bin/file/formatted_io ./file/formatted_io.c
	gcc -o ./bin/file/fp_io ./file/fp_io.c
	gcc -o ./bin/file/fp_offset ./file/fp_offset.c
	gcc -o ./bin/file/fp ./file/fp.c
	gcc -o ./bin/file/poll ./file/poll.c
	gcc -o ./bin/file/select ./file/select.c
	gcc -o ./bin/file/vectored_io ./file/vectored_io.c

src/thread:
	gcc -pthread -o ./bin/thread/bug ./thread/bug.c
	gcc -pthread -o ./bin/thread/mutex ./thread/mutex.c
	gcc -pthread -o ./bin/thread/pthread ./thread/pthread.c
	gcc -pthread -o ./bin/thread/thread_pool ./thread/thread_pool.c