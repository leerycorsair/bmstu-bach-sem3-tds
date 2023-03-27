CC = gcc
INCPATH = ./inc/
OUTPATH = ./out/
SRCPATH = ./src/

CFLAGS = -std=c99 -I$(INCPATH) -DNDEBUG -g0 -c
LFLAGS = 

.PHONY: clean
.NOTPARALLEL: release debug

release: dirs $(OUTPATH)release.lastbuildstate app.exe

debug: CFLAGS = -std=c99 -I$(INCPATH) -Werror -Wall -Wpedantic -Wextra -g3 -o3 -c
debug: LFLAGS = 
debug: dirs $(OUTPATH)debug.lastbuildstate app.exe


$(OUTPATH)debug.lastbuildstate:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)release.lastbuildstate
	touch $(OUTPATH)debug.lastbuildstate
	
$(OUTPATH)release.lastbuildstate:
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)debug.lastbuildstate
	touch $(OUTPATH)release.lastbuildstate

clean: 
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.lastbuildstate	

app.exe: dirs $(OUTPATH)main.o $(OUTPATH)io_lib.o $(OUTPATH)mem_manager.o $(OUTPATH)stack_processing.o
	gcc -o $@ $(OUTPATH)main.o $(OUTPATH)io_lib.o $(OUTPATH)mem_manager.o $(OUTPATH)stack_processing.o

$(OUTPATH)main.o: $(SRCPATH)main.c
	$(CC) $(CFLAGS) -o $@ $^
	
$(OUTPATH)io_lib.o: $(SRCPATH)io_lib.c
	$(CC) $(CFLAGS) -o $@ $<

$(OUTPATH)mem_manager.o: $(SRCPATH)mem_manager.c
	$(CC) $(CFLAGS) -o $@ $^
	
$(OUTPATH)stack_processing.o: $(SRCPATH)stack_processing.c
	$(CC) $(CFLAGS) -o $@ $<

	
dirs: $(INCPATH) $(OUTPATH) $(SRCPATH) $(FUNCTESTPATH) $(UNITTESTPATH)

$(INCPATH):
	mkdir $@

$(OUTPATH):
	mkdir $@

$(SRCPATH):
	mkdir $@

$(FUNCTESTPATH):
	mkdir $@

$(UNITTESTPATH):
	mkdir $@