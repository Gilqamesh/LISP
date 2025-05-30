pwd := $(shell pwd)
tool-dir := $(pwd)/tools
src-dir := $(pwd)/src
generate-src := $(tool-dir)/generate-obj-types.c
generate-bin := gen
generate-inc := -g
repl-src := $(shell find $(src-dir) -name '*.c')
repl-bin := repl
repl-inc := -g -I$(src-dir) -I$(src-dir)/obj

.PHONY: all generate clean

all: $(generate-bin)
all: $(repl-bin)

$(generate-bin): $(generate-src)
	$(CC) -o $@ $^ $(generate-inc)

$(repl-bin): $(repl-src)
	$(CC) -o $@ $^ $(repl-inc)

generate: $(generate-bin)
	./$(generate-bin) $(tool-dir)/obj-types.txt $(src-dir)/obj

clean:
	rm -f $(generate-bin)
	rm -f $(repl-bin)
