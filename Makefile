tool-dir := tools
src-dir := src
test-dir := tests

src := $(shell find $(src-dir) -name '*.c')
cflag := -g -I$(src-dir)
cin := 
lflag := -lbacktrace -lm
cout := $(src:$(src-dir)/%.c=$(src-dir)/%.o)

tool-src := $(shell find $(tool-dir) -name '*.c')
tool-cflag := -I$(tool-dir)
tool-cout := $(tool-src:$(tool-dir)/%.c=$(tool-dir)/%.o)
tool-lin :=
tool-lflag :=
tool-lout := $(tool-src:$(tool-dir)/%.c=$(tool-dir)/%)

test-src := $(shell find $(test-dir) -name '*.c')
test-cflag := $(cflag) -I$(test-dir)
test-cout := $(test-src:$(test-dir)/%.c=$(test-dir)/%.o)
test-lin := $(cout)
test-lflag := $(lflag)
test-lout := $(test-src:$(test-dir)/%.c=$(test-dir)/%)

.PHONY: all clean \
		tools \
		tests tests-run

all: tools
all: tests

$(src-dir)/%.o: $(src-dir)/%.c
	$(CC) -c $< $(cflag) -MMD -MP -MF $(<:.c=.d) -o $@

$(tool-dir)/%.o: $(tool-dir)/%.c
	$(CC) -c $< $(tool-cflag) -MMD -MP -MF $(<:.c=.d) -o $@

$(tool-dir)/%: $(tool-lin) $(tool-dir)/%.o
	$(CC) $^ $(tool-lflag) -o $@

$(test-dir)/%.o: $(test-dir)/%.c 
	$(CC) -c $< $(test-cflag) -MMD -MP -MF $(<:.c=.d) -o $@

$(test-dir)/%: $(test-lin) $(test-dir)/%.o
	$(CC) $^ $(test-lflag) -o $@

tools: $(tool-lout)

tests: $(test-lout)

tests-run: tests
	@for test in $(test-lout); do \
		echo "Running $$test"; \
		./$$test; \
	done

clean:
	rm -f $(cout) $(src:%.c=%.d)
	rm -f $(tool-lout) $(tool-cout) $(tool-src:%.c=%.d)
	rm -f $(test-lout) $(test-cout) $(test-src:%.c=%.d)

-include $(src:%.c=%.d) $(tool-src:%.c=%.d) $(test-src:%.c=%.d)
