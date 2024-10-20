MAIN := main.cc
PROG := prog
CPP_Ver := c++11
PROG_DBG := $(PROG)_dbg
PROG_EXEC := $(PROG).out
PROG_DBG_EXEC := $(PROG_DBG).out
PPM_FILE := img.ppm

img_output: $(MAIN) build
	echo "====writing output===="
	./$(PROG_EXEC) > $(PPM_FILE)
	open $(PPM_FILE)

build:
	echo "====starting build===="
	clang++ -std=$(CPP_Ver) $(MAIN) -o $(PROG_EXEC)

debug:
	clang++ -std=$(CPP_Ver) $(MAIN) -g -o $(PROG_DBG_EXEC)

clean:
	rm -f *.out *.ppm

