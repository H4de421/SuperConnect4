export CC = gcc

client: FORCE
	make -C client/ all	
	mv server/cli_exec .

server: FORCE
	make -C server/ all
	mv server/ser_exec .

clean:
	make -C client/ clean
	make -C server/ clean
	rm -f ser_exec
	rm -f cli_exec

FORCE: