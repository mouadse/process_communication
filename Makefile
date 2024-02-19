CC=clang
CFLAGS=-Wall
EXE=example
SOURCE=main.c

all: $(EXE)

$(EXE): $(SOURCE)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "\033[32mCompilation successful! $(EXE) is ready.\033[0m"

clean:
	@if [ -z "$(wildcard *.o $(EXE) *.dSYM *.out)" ]; then \
		echo "No object files found, skipping deletion."; \
	else \
		rm -rf *.o $(EXE) *.dSYM *.out; \
		echo "\033[31mRemoving object files, executable, and temporary files...\033[0m";\
	fi

.PHONY: clean all
