pwd := $(shell pwd)
tool-dir := $(pwd)/tools
src-dir := $(pwd)/src
generate-src := $(tool-dir)/generate-obj-types.c
generate-bin := gen
repl-src := $(shell find $(src-dir) -name '*.c')
repl-bin := repl

.PHONY: all generate clean

all: $(generate-bin)
all: $(repl-bin)

$(generate-bin): $(generate-src)
	$(CC) -o $@ $^

$(repl-bin): $(repl-src)
	$(CC) -o $@ $^ -I$(src-dir) -I$(src-dir)/obj

generate: $(generate-bin)
	./$(generate-bin) $(tool-dir)/obj-types.txt $(src-dir)/obj

clean:
	rm -f $(generate-bin)
	rm -f $(repl-bin)
