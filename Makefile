export CC = gcc

server:
	make -C client/ all

client:
	make -C client/ all	

clean:
	make -C client/ clean
	make -C server/ clean