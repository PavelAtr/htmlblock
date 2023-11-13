STRIP ?= strip
PREFIX ?= /usr/local

build:
	$(CXX) -static env.c filter.c normalize.cpp main.c -o htmlblock
	$(STRIP) htmlblock

install:
	install htmlblock $(PREFIX)/bin/

clean:
	rm htmlblock
