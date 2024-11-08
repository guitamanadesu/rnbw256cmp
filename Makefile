PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
TARGET = rnbw256cmp

all: $(TARGET)

$(TARGET): main.c
	$(CC) -o $(TARGET) main.c

install: $(TARGET)
	install -d $(BINDIR)
	install $(TARGET) $(BINDIR)

clean:
	rm -f $(TARGET)

.PHONY: all install clean