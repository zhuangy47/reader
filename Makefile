CHARMDIR = ../
CHARMC = $(CHARMDIR)/bin/charmc $(OPTS)


default: all
all: reader


reader : main.o reader.o
	$(CHARMC) -language charm++ -o reader main.o reader.o

main.o : main.C main.h main.decl.h main.def.h reader.decl.h
	$(CHARMC) -o main.o main.C

main.decl.h main.def.h : main.ci
	$(CHARMC) main.ci

reader.o : reader.C reader.h reader.decl.h reader.def.h main.decl.h
	$(CHARMC) -o reader.o reader.C

reader.decl.h reader.def.h : reader.ci
	$(CHARMC) reader.ci


clean:
	rm -f main.decl.h main.def.h main.o
	rm -f reader.decl.h reader.def.h reader.o
	rm -f reader charmrun
