CSRC = $(wildcard *.c)
CPROGS = $(patsubst %.c,%,$(CSRC))

CPPSRC = $(wildcard *.cc)
CPPPROGS = $(patsubst %.cc,%,$(CPPSRC))
CPPFLAGS = -std=c++11
COMMONFLAGS = -Wall -pedantic -Wno-long-long -O2 -Werror

all: $(CPROGS) $(CPPPROGS)

%: %.c
	gcc $(COMMONFLAGS) -o $@ $< -lm

%: %.cc
	g++ $(COMMONFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -f $(CPROGS) $(CPPPROGS)
