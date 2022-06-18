CFLAGS=-Wall -Wextra -Wshadow -Wno-unused-function -Wunused-result -Wno-unused-value -Wno-missing-braces -Wpedantic -Werror
CFLAGS+=-std=c99
CFLAGS+=-D_DEFAULT_SOURCE -DPLATFORM_DESKTOP
CFLAGS+=-I.
CFLAGS+=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# this makes sure that we can use a rule even if there's a file with the
# same name as a rule
.PHONY: build run

build:
	cc main.c helpers.c viridian.c $(CFLAGS) -o rpv

run: build
	./rpv
