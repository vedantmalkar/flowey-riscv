flowey: src/cpu.c src/decoder.c src/execute.c src/memory.c src/sim.c
	gcc -Wall src/*.c -o flowey

clean:
	rm -rf flowey

run: flowey
	./flowey

.PHONY: clean run
