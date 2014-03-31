ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)
ROOTGLIBS := $(shell root-config --glibs)

FASTJETLIBS := $(shell fastjet-config --cxxflags --libs)

GSLCFLAGS := $(shell gsl-config --cflags)
GSLLIBS := $(shell gsl-config --libs)

PYTHIACFLAGS := -I$(PYTHIA8)/include
PYTHIALIBS =  -L$(PYTHIA8)/lib/archive -lpythia8 -llhapdfdummy

#my sources and libraries
LIBS = -I. -I./include/

all: remove ls
	@echo "compile via: make 'ProgramName'"

clean:
	rm -fv *.exe

remove:
	rm -fR *.exe.dSYM

ls: 
	ls -lh -G --color

#Compile each program
PROGRAM = Boost Boost2

Boost Boost2:
	g++ $@.cpp -o $@.exe -lm -g -Wall $(ROOTCFLAGS) $(ROOTLIBS) $(ROOTGLIBS) $(LIBS) $(FASTJETLIBS) $(GSLCFLAGS) $(GSLLIBS) $(PYTHIACFLAGS) $(PYTHIALIBS)
	rm -fr $@.exe.dSYM

