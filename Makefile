# Lab 6 Makefile

STD=-std=c++20
OPT=-g
# redefine this to wherever lab3 is
CXXFLAGS=${STD} ${OPT}
CFLAGS=${OPT}

%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $<

%.o: ${BASEDIR}/%.cxx
	$(CXX) -c $(CXXFLAGS) $<

LLISTSRCS=rosterllistmain.cxx rosterllist.cxx rostertest.cxx
LLISTOBJS=$(LLISTSRCS:.cxx=.o) roster.o
HDRS=rosterllist.h
ALL=rosterllisttest

all: $(ALL)

rosterllisttest:	$(LLISTOBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f $(LLISTOBJS) $(ALL)
	/bin/rm -f rosterllist.tar
	/bin/rm -rf $(ALL:=.dSYM)


depend: $(LLISTSRCS)
	TMP=`mktemp -p .`; export TMP; \
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
	echo '# DEPENDENTS' >> $$TMP; \
	$(CXX) -MM $(INC) $+ >> $$TMP; \
	/bin/mv -f $$TMP Makefile

# DEPENDENTS
rosterllistmain.o: rosterllistmain.cxx person.h roster.h rosterllist.h
rosterllist.o: rosterllist.cxx person.h roster.h rosterllist.h
rostertest.o: rostertest.cxx person.h roster.h rosterllist.h
