.PHONY: all engine hello_world clean

all: engine hello_world

engine:
	$(MAKE) -C engine

hello_world:
	$(MAKE) -C examples/hello_world

clean:
	$(MAKE) -C engine clean
	$(MAKE) -C examples/hello_world clean
