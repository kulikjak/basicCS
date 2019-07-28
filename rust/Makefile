RUST_SRC = $(wildcard *.rs)
RUST_PROGS = $(patsubst %.rs,%,$(RUST_SRC))

FLAGS = -O

all: $(RUST_SRC) $(RUST_PROGS)

%: %.rs
	rustc $(FLAGS) -o $@ $<

clean:
	rm -f $(RUST_PROGS)

.PHONY: all clean
