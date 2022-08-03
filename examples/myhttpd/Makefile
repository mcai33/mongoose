PROG ?= example

all: $(PROG)
	./$(PROG)

$(PROG):
	$(CC) main.c mongoose.c net.c -I. $(CFLAGS) $(EXTRA) -o $(PROG)

clean:
	rm -rf $(PROG) *.o *.dSYM *.gcov *.gcno *.gcda *.obj *.exe *.ilk *.pdb
