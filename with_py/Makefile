TARGET?=prog
SOURCES=ex_001.c

.PHONY: all
all: $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) $^ -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(SOURCES:.c=.o) $(TARGET)
