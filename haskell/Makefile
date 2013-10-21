CDIR=$(CURDIR)/c
HFLAGS=-I$(CDIR) -L$(CDIR)

all: OspStructs

OspStructs.hs:
	hsc2hs OspStructs.hsc2hs

OspStructs: $(CDIR)/osp_structs.o $(CDIR)/osp_structs.h OspStructs.hs
	ghc $(HFLAGS) -main-is OspStructs --make OspStructs.hs $(CDIR)/osp_structs.c

clean:
	rm *.hi
	rm *.o
	rm OspStructs
	rm OspStructs.hs
	rm $(CDIR)/osp_structs.o
