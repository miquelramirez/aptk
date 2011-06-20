#!/bin/sh
#
# Makefile for FF v 1.0
#


####### FLAGS

TYPE	= 
ADDONS	= 

CC      = gcc


CFLAGS  =  -O6 -Wall -ansi $(TYPE) $(ADDONS)
#CFLAGS	=  -g -pg -Wall -ansi $(TYPE) $(ADDONS) 
# -g -pg

LIBS    = -lm


####### Files

PDDL_PARSER_SRC	= scan-fct_pddl.tab.c \
	scan-ops_pddl.tab.c \
	scan-probname.tab.c \
	lex.fct_pddl.c \
	lex.ops_pddl.c 

PDDL_PARSER_OBJ = scan-fct_pddl.tab.o \
	scan-ops_pddl.tab.o 


SOURCES 	= main.c \
	memory.c \
	output.c \
	parse.c \
	expressions.c \
	inst_pre.c \
	inst_easy.c \
	inst_hard.c \
	inst_final.c \
	relax.c \
	search.c \
	utility.c

LIB_SOURCES = libff.c \
	memory.c \
	output.c \
	parse.c \
	expressions.c \
	inst_pre.c \
	inst_easy.c \
	inst_hard.c \
	inst_final.c \
	relax.c \
	search.c \
	utility.c


OBJECTS 	= $(SOURCES:.c=.o)
LIB_OBJECTS	= $(LIB_SOURCES:.c=.o)

####### Implicit rules

.SUFFIXES:

.SUFFIXES: .c .o

.c.o:; $(CC) -c $(CFLAGS) $<

####### Build rules

libff: $(LIB_OBJECTS) $(PDDL_PARSER_OBJ)
	ar cru libff.a $(LIB_OBJECTS) $(PDDL_PARSER_OBJ)

ff: $(OBJECTS) $(PDDL_PARSER_OBJ)
	$(CC) -static -o ff $(OBJECTS) $(PDDL_PARSER_OBJ) $(CFLAGS) $(LIBS)

# pddl syntax
scan-fct_pddl.tab.c: scan-fct_pddl.y lex.fct_pddl.c
	bison -pfct_pddl -bscan-fct_pddl scan-fct_pddl.y

scan-ops_pddl.tab.c: scan-ops_pddl.y lex.ops_pddl.c
	bison -pops_pddl -bscan-ops_pddl scan-ops_pddl.y

lex.fct_pddl.c: lex-fct_pddl.l
	flex -Pfct_pddl lex-fct_pddl.l

lex.ops_pddl.c: lex-ops_pddl.l
	flex -Pops_pddl lex-ops_pddl.l

test_lib: test_main.cxx
	g++ -static -o test_lib test_main.cxx -lff -L./

# misc
clean:
	rm -f *.o *.bak *~ *% core *_pure_p9_c0_400.o.warnings test_lib \
        \#*\# $(RES_PARSER_SRC) $(PDDL_PARSER_SRC)

veryclean: clean
	rm -f ff H* J* K* L* O* graph.* *.symbex gmon.out \
	$(PDDL_PARSER_SRC) \
	lex.fct_pddl.c lex.ops_pddl.c lex.probname.c \
	*.output

depend:
	makedepend -- $(SOURCES)  $(LIB_SOURCES) $(PDDL_PARSER_SRC) test_main.cxx

lint:
	lclint -booltype Bool $(SOURCES) 2> output.lint

# DO NOT DELETE

main.o: ff.h /usr/include/stdlib.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
main.o: /usr/include/sys/types.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/time.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/sys/timeb.h
main.o: /usr/include/sys/times.h memory.h /usr/include/string.h output.h
main.o: parse.h expressions.h inst_pre.h inst_easy.h inst_hard.h inst_final.h
main.o: relax.h search.h
memory.o: /usr/include/string.h /usr/include/features.h
memory.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
memory.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h ff.h
memory.o: /usr/include/stdlib.h /usr/include/sys/types.h
memory.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
memory.o: /usr/include/time.h /usr/include/endian.h
memory.o: /usr/include/bits/endian.h /usr/include/sys/select.h
memory.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
memory.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
memory.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
memory.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
memory.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
memory.o: /usr/include/bits/sys_errlist.h /usr/include/strings.h
memory.o: /usr/include/ctype.h /usr/include/sys/timeb.h
memory.o: /usr/include/sys/times.h memory.h inst_pre.h
output.o: ff.h /usr/include/stdlib.h /usr/include/features.h
output.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
output.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
output.o: /usr/include/sys/types.h /usr/include/bits/types.h
output.o: /usr/include/bits/typesizes.h /usr/include/time.h
output.o: /usr/include/endian.h /usr/include/bits/endian.h
output.o: /usr/include/sys/select.h /usr/include/bits/select.h
output.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
output.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
output.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
output.o: /usr/include/_G_config.h /usr/include/wchar.h
output.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
output.o: /usr/include/strings.h /usr/include/ctype.h
output.o: /usr/include/sys/timeb.h /usr/include/sys/times.h utility.h
output.o: output.h
parse.o: ff.h /usr/include/stdlib.h /usr/include/features.h
parse.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
parse.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
parse.o: /usr/include/sys/types.h /usr/include/bits/types.h
parse.o: /usr/include/bits/typesizes.h /usr/include/time.h
parse.o: /usr/include/endian.h /usr/include/bits/endian.h
parse.o: /usr/include/sys/select.h /usr/include/bits/select.h
parse.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
parse.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
parse.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
parse.o: /usr/include/_G_config.h /usr/include/wchar.h
parse.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
parse.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/sys/timeb.h
parse.o: /usr/include/sys/times.h memory.h /usr/include/string.h output.h
parse.o: parse.h
expressions.o: /usr/include/string.h /usr/include/features.h
expressions.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
expressions.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h ff.h
expressions.o: /usr/include/stdlib.h /usr/include/sys/types.h
expressions.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
expressions.o: /usr/include/time.h /usr/include/endian.h
expressions.o: /usr/include/bits/endian.h /usr/include/sys/select.h
expressions.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
expressions.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
expressions.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
expressions.o: /usr/include/stdio.h /usr/include/libio.h
expressions.o: /usr/include/_G_config.h /usr/include/wchar.h
expressions.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
expressions.o: /usr/include/strings.h /usr/include/ctype.h
expressions.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
expressions.o: memory.h expressions.h
inst_pre.o: /usr/include/string.h /usr/include/features.h
inst_pre.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_pre.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h ff.h
inst_pre.o: /usr/include/stdlib.h /usr/include/sys/types.h
inst_pre.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
inst_pre.o: /usr/include/time.h /usr/include/endian.h
inst_pre.o: /usr/include/bits/endian.h /usr/include/sys/select.h
inst_pre.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
inst_pre.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
inst_pre.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
inst_pre.o: /usr/include/stdio.h /usr/include/libio.h
inst_pre.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_pre.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_pre.o: /usr/include/strings.h /usr/include/ctype.h
inst_pre.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_pre.o: memory.h expressions.h inst_pre.h
inst_easy.o: ff.h /usr/include/stdlib.h /usr/include/features.h
inst_easy.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_easy.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
inst_easy.o: /usr/include/sys/types.h /usr/include/bits/types.h
inst_easy.o: /usr/include/bits/typesizes.h /usr/include/time.h
inst_easy.o: /usr/include/endian.h /usr/include/bits/endian.h
inst_easy.o: /usr/include/sys/select.h /usr/include/bits/select.h
inst_easy.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
inst_easy.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
inst_easy.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
inst_easy.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_easy.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_easy.o: /usr/include/strings.h /usr/include/ctype.h
inst_easy.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_easy.o: memory.h /usr/include/string.h expressions.h inst_pre.h
inst_easy.o: inst_easy.h
inst_hard.o: ff.h /usr/include/stdlib.h /usr/include/features.h
inst_hard.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_hard.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
inst_hard.o: /usr/include/sys/types.h /usr/include/bits/types.h
inst_hard.o: /usr/include/bits/typesizes.h /usr/include/time.h
inst_hard.o: /usr/include/endian.h /usr/include/bits/endian.h
inst_hard.o: /usr/include/sys/select.h /usr/include/bits/select.h
inst_hard.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
inst_hard.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
inst_hard.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
inst_hard.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_hard.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_hard.o: /usr/include/strings.h /usr/include/ctype.h
inst_hard.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_hard.o: memory.h /usr/include/string.h expressions.h inst_pre.h
inst_hard.o: inst_hard.h
inst_final.o: ff.h /usr/include/stdlib.h /usr/include/features.h
inst_final.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_final.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
inst_final.o: /usr/include/sys/types.h /usr/include/bits/types.h
inst_final.o: /usr/include/bits/typesizes.h /usr/include/time.h
inst_final.o: /usr/include/endian.h /usr/include/bits/endian.h
inst_final.o: /usr/include/sys/select.h /usr/include/bits/select.h
inst_final.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
inst_final.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
inst_final.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
inst_final.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_final.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_final.o: /usr/include/strings.h /usr/include/ctype.h
inst_final.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_final.o: memory.h /usr/include/string.h expressions.h inst_pre.h
inst_final.o: inst_final.h
relax.o: ff.h /usr/include/stdlib.h /usr/include/features.h
relax.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
relax.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
relax.o: /usr/include/sys/types.h /usr/include/bits/types.h
relax.o: /usr/include/bits/typesizes.h /usr/include/time.h
relax.o: /usr/include/endian.h /usr/include/bits/endian.h
relax.o: /usr/include/sys/select.h /usr/include/bits/select.h
relax.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
relax.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
relax.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
relax.o: /usr/include/_G_config.h /usr/include/wchar.h
relax.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
relax.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/sys/timeb.h
relax.o: /usr/include/sys/times.h output.h memory.h /usr/include/string.h
relax.o: expressions.h relax.h search.h
search.o: ff.h /usr/include/stdlib.h /usr/include/features.h
search.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
search.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
search.o: /usr/include/sys/types.h /usr/include/bits/types.h
search.o: /usr/include/bits/typesizes.h /usr/include/time.h
search.o: /usr/include/endian.h /usr/include/bits/endian.h
search.o: /usr/include/sys/select.h /usr/include/bits/select.h
search.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
search.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
search.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
search.o: /usr/include/_G_config.h /usr/include/wchar.h
search.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
search.o: /usr/include/strings.h /usr/include/ctype.h
search.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h memory.h
search.o: /usr/include/string.h expressions.h relax.h search.h
utility.o: /usr/include/string.h /usr/include/features.h
utility.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
utility.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h utility.h
utility.o: ff.h /usr/include/stdlib.h /usr/include/sys/types.h
utility.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
utility.o: /usr/include/time.h /usr/include/endian.h
utility.o: /usr/include/bits/endian.h /usr/include/sys/select.h
utility.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
utility.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
utility.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
utility.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
utility.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
utility.o: /usr/include/bits/sys_errlist.h /usr/include/strings.h
utility.o: /usr/include/ctype.h /usr/include/sys/timeb.h
utility.o: /usr/include/sys/times.h output.h
libff.o: libff.h ff.h /usr/include/stdlib.h /usr/include/features.h
libff.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
libff.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
libff.o: /usr/include/sys/types.h /usr/include/bits/types.h
libff.o: /usr/include/bits/typesizes.h /usr/include/time.h
libff.o: /usr/include/endian.h /usr/include/bits/endian.h
libff.o: /usr/include/sys/select.h /usr/include/bits/select.h
libff.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
libff.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
libff.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
libff.o: /usr/include/_G_config.h /usr/include/wchar.h
libff.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
libff.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/sys/timeb.h
libff.o: /usr/include/sys/times.h memory.h /usr/include/string.h output.h
libff.o: parse.h expressions.h inst_pre.h inst_easy.h inst_hard.h
libff.o: inst_final.h
memory.o: /usr/include/string.h /usr/include/features.h
memory.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
memory.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h ff.h
memory.o: /usr/include/stdlib.h /usr/include/sys/types.h
memory.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
memory.o: /usr/include/time.h /usr/include/endian.h
memory.o: /usr/include/bits/endian.h /usr/include/sys/select.h
memory.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
memory.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
memory.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
memory.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
memory.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
memory.o: /usr/include/bits/sys_errlist.h /usr/include/strings.h
memory.o: /usr/include/ctype.h /usr/include/sys/timeb.h
memory.o: /usr/include/sys/times.h memory.h inst_pre.h
output.o: ff.h /usr/include/stdlib.h /usr/include/features.h
output.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
output.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
output.o: /usr/include/sys/types.h /usr/include/bits/types.h
output.o: /usr/include/bits/typesizes.h /usr/include/time.h
output.o: /usr/include/endian.h /usr/include/bits/endian.h
output.o: /usr/include/sys/select.h /usr/include/bits/select.h
output.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
output.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
output.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
output.o: /usr/include/_G_config.h /usr/include/wchar.h
output.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
output.o: /usr/include/strings.h /usr/include/ctype.h
output.o: /usr/include/sys/timeb.h /usr/include/sys/times.h utility.h
output.o: output.h
parse.o: ff.h /usr/include/stdlib.h /usr/include/features.h
parse.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
parse.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
parse.o: /usr/include/sys/types.h /usr/include/bits/types.h
parse.o: /usr/include/bits/typesizes.h /usr/include/time.h
parse.o: /usr/include/endian.h /usr/include/bits/endian.h
parse.o: /usr/include/sys/select.h /usr/include/bits/select.h
parse.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
parse.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
parse.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
parse.o: /usr/include/_G_config.h /usr/include/wchar.h
parse.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
parse.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/sys/timeb.h
parse.o: /usr/include/sys/times.h memory.h /usr/include/string.h output.h
parse.o: parse.h
expressions.o: /usr/include/string.h /usr/include/features.h
expressions.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
expressions.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h ff.h
expressions.o: /usr/include/stdlib.h /usr/include/sys/types.h
expressions.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
expressions.o: /usr/include/time.h /usr/include/endian.h
expressions.o: /usr/include/bits/endian.h /usr/include/sys/select.h
expressions.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
expressions.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
expressions.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
expressions.o: /usr/include/stdio.h /usr/include/libio.h
expressions.o: /usr/include/_G_config.h /usr/include/wchar.h
expressions.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
expressions.o: /usr/include/strings.h /usr/include/ctype.h
expressions.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
expressions.o: memory.h expressions.h
inst_pre.o: /usr/include/string.h /usr/include/features.h
inst_pre.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_pre.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h ff.h
inst_pre.o: /usr/include/stdlib.h /usr/include/sys/types.h
inst_pre.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
inst_pre.o: /usr/include/time.h /usr/include/endian.h
inst_pre.o: /usr/include/bits/endian.h /usr/include/sys/select.h
inst_pre.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
inst_pre.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
inst_pre.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
inst_pre.o: /usr/include/stdio.h /usr/include/libio.h
inst_pre.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_pre.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_pre.o: /usr/include/strings.h /usr/include/ctype.h
inst_pre.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_pre.o: memory.h expressions.h inst_pre.h
inst_easy.o: ff.h /usr/include/stdlib.h /usr/include/features.h
inst_easy.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_easy.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
inst_easy.o: /usr/include/sys/types.h /usr/include/bits/types.h
inst_easy.o: /usr/include/bits/typesizes.h /usr/include/time.h
inst_easy.o: /usr/include/endian.h /usr/include/bits/endian.h
inst_easy.o: /usr/include/sys/select.h /usr/include/bits/select.h
inst_easy.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
inst_easy.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
inst_easy.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
inst_easy.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_easy.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_easy.o: /usr/include/strings.h /usr/include/ctype.h
inst_easy.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_easy.o: memory.h /usr/include/string.h expressions.h inst_pre.h
inst_easy.o: inst_easy.h
inst_hard.o: ff.h /usr/include/stdlib.h /usr/include/features.h
inst_hard.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_hard.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
inst_hard.o: /usr/include/sys/types.h /usr/include/bits/types.h
inst_hard.o: /usr/include/bits/typesizes.h /usr/include/time.h
inst_hard.o: /usr/include/endian.h /usr/include/bits/endian.h
inst_hard.o: /usr/include/sys/select.h /usr/include/bits/select.h
inst_hard.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
inst_hard.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
inst_hard.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
inst_hard.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_hard.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_hard.o: /usr/include/strings.h /usr/include/ctype.h
inst_hard.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_hard.o: memory.h /usr/include/string.h expressions.h inst_pre.h
inst_hard.o: inst_hard.h
inst_final.o: ff.h /usr/include/stdlib.h /usr/include/features.h
inst_final.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
inst_final.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
inst_final.o: /usr/include/sys/types.h /usr/include/bits/types.h
inst_final.o: /usr/include/bits/typesizes.h /usr/include/time.h
inst_final.o: /usr/include/endian.h /usr/include/bits/endian.h
inst_final.o: /usr/include/sys/select.h /usr/include/bits/select.h
inst_final.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
inst_final.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
inst_final.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
inst_final.o: /usr/include/_G_config.h /usr/include/wchar.h
inst_final.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
inst_final.o: /usr/include/strings.h /usr/include/ctype.h
inst_final.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
inst_final.o: memory.h /usr/include/string.h expressions.h inst_pre.h
inst_final.o: inst_final.h
relax.o: ff.h /usr/include/stdlib.h /usr/include/features.h
relax.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
relax.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
relax.o: /usr/include/sys/types.h /usr/include/bits/types.h
relax.o: /usr/include/bits/typesizes.h /usr/include/time.h
relax.o: /usr/include/endian.h /usr/include/bits/endian.h
relax.o: /usr/include/sys/select.h /usr/include/bits/select.h
relax.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
relax.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
relax.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
relax.o: /usr/include/_G_config.h /usr/include/wchar.h
relax.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
relax.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/sys/timeb.h
relax.o: /usr/include/sys/times.h output.h memory.h /usr/include/string.h
relax.o: expressions.h relax.h search.h
search.o: ff.h /usr/include/stdlib.h /usr/include/features.h
search.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
search.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
search.o: /usr/include/sys/types.h /usr/include/bits/types.h
search.o: /usr/include/bits/typesizes.h /usr/include/time.h
search.o: /usr/include/endian.h /usr/include/bits/endian.h
search.o: /usr/include/sys/select.h /usr/include/bits/select.h
search.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
search.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
search.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
search.o: /usr/include/_G_config.h /usr/include/wchar.h
search.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
search.o: /usr/include/strings.h /usr/include/ctype.h
search.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h memory.h
search.o: /usr/include/string.h expressions.h relax.h search.h
utility.o: /usr/include/string.h /usr/include/features.h
utility.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
utility.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h utility.h
utility.o: ff.h /usr/include/stdlib.h /usr/include/sys/types.h
utility.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
utility.o: /usr/include/time.h /usr/include/endian.h
utility.o: /usr/include/bits/endian.h /usr/include/sys/select.h
utility.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
utility.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
utility.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
utility.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
utility.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
utility.o: /usr/include/bits/sys_errlist.h /usr/include/strings.h
utility.o: /usr/include/ctype.h /usr/include/sys/timeb.h
utility.o: /usr/include/sys/times.h output.h
scan-fct_pddl.tab.o: /usr/include/stdio.h /usr/include/features.h
scan-fct_pddl.tab.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
scan-fct_pddl.tab.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
scan-fct_pddl.tab.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
scan-fct_pddl.tab.o: /usr/include/libio.h /usr/include/_G_config.h
scan-fct_pddl.tab.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
scan-fct_pddl.tab.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
scan-fct_pddl.tab.o: ff.h /usr/include/stdlib.h /usr/include/sys/types.h
scan-fct_pddl.tab.o: /usr/include/time.h /usr/include/endian.h
scan-fct_pddl.tab.o: /usr/include/bits/endian.h /usr/include/sys/select.h
scan-fct_pddl.tab.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
scan-fct_pddl.tab.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
scan-fct_pddl.tab.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
scan-fct_pddl.tab.o: /usr/include/strings.h /usr/include/ctype.h
scan-fct_pddl.tab.o: /usr/include/sys/timeb.h /usr/include/sys/times.h
scan-fct_pddl.tab.o: memory.h parse.h lex.fct_pddl.c /usr/include/errno.h
scan-fct_pddl.tab.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
scan-fct_pddl.tab.o: /usr/include/asm/errno.h
scan-fct_pddl.tab.o: /usr/include/asm-generic/errno.h
scan-fct_pddl.tab.o: /usr/include/asm-generic/errno-base.h
scan-fct_pddl.tab.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
scan-fct_pddl.tab.o: /usr/include/bits/confname.h /usr/include/getopt.h
scan-ops_pddl.tab.o: /usr/include/stdio.h /usr/include/features.h
scan-ops_pddl.tab.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
scan-ops_pddl.tab.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
scan-ops_pddl.tab.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
scan-ops_pddl.tab.o: /usr/include/libio.h /usr/include/_G_config.h
scan-ops_pddl.tab.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
scan-ops_pddl.tab.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
scan-ops_pddl.tab.o: ff.h /usr/include/stdlib.h /usr/include/sys/types.h
scan-ops_pddl.tab.o: /usr/include/time.h /usr/include/endian.h
scan-ops_pddl.tab.o: /usr/include/bits/endian.h /usr/include/sys/select.h
scan-ops_pddl.tab.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
scan-ops_pddl.tab.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
scan-ops_pddl.tab.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
scan-ops_pddl.tab.o: /usr/include/strings.h /usr/include/ctype.h
scan-ops_pddl.tab.o: /usr/include/sys/timeb.h /usr/include/sys/times.h
scan-ops_pddl.tab.o: memory.h parse.h lex.ops_pddl.c /usr/include/errno.h
scan-ops_pddl.tab.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
scan-ops_pddl.tab.o: /usr/include/asm/errno.h
scan-ops_pddl.tab.o: /usr/include/asm-generic/errno.h
scan-ops_pddl.tab.o: /usr/include/asm-generic/errno-base.h
scan-ops_pddl.tab.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
scan-ops_pddl.tab.o: /usr/include/bits/confname.h /usr/include/getopt.h
lex.fct_pddl.o: /usr/include/stdio.h /usr/include/features.h
lex.fct_pddl.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
lex.fct_pddl.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
lex.fct_pddl.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
lex.fct_pddl.o: /usr/include/libio.h /usr/include/_G_config.h
lex.fct_pddl.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
lex.fct_pddl.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
lex.fct_pddl.o: /usr/include/errno.h /usr/include/bits/errno.h
lex.fct_pddl.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
lex.fct_pddl.o: /usr/include/asm-generic/errno.h
lex.fct_pddl.o: /usr/include/asm-generic/errno-base.h /usr/include/stdlib.h
lex.fct_pddl.o: /usr/include/sys/types.h /usr/include/time.h
lex.fct_pddl.o: /usr/include/endian.h /usr/include/bits/endian.h
lex.fct_pddl.o: /usr/include/sys/select.h /usr/include/bits/select.h
lex.fct_pddl.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
lex.fct_pddl.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
lex.fct_pddl.o: /usr/include/alloca.h ff.h /usr/include/strings.h
lex.fct_pddl.o: /usr/include/ctype.h /usr/include/sys/timeb.h
lex.fct_pddl.o: /usr/include/sys/times.h parse.h /usr/include/unistd.h
lex.fct_pddl.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
lex.fct_pddl.o: /usr/include/getopt.h
lex.ops_pddl.o: /usr/include/stdio.h /usr/include/features.h
lex.ops_pddl.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
lex.ops_pddl.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
lex.ops_pddl.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
lex.ops_pddl.o: /usr/include/libio.h /usr/include/_G_config.h
lex.ops_pddl.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
lex.ops_pddl.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
lex.ops_pddl.o: /usr/include/errno.h /usr/include/bits/errno.h
lex.ops_pddl.o: /usr/include/linux/errno.h /usr/include/asm/errno.h
lex.ops_pddl.o: /usr/include/asm-generic/errno.h
lex.ops_pddl.o: /usr/include/asm-generic/errno-base.h /usr/include/stdlib.h
lex.ops_pddl.o: /usr/include/sys/types.h /usr/include/time.h
lex.ops_pddl.o: /usr/include/endian.h /usr/include/bits/endian.h
lex.ops_pddl.o: /usr/include/sys/select.h /usr/include/bits/select.h
lex.ops_pddl.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
lex.ops_pddl.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
lex.ops_pddl.o: /usr/include/alloca.h ff.h /usr/include/strings.h
lex.ops_pddl.o: /usr/include/ctype.h /usr/include/sys/timeb.h
lex.ops_pddl.o: /usr/include/sys/times.h parse.h /usr/include/unistd.h
lex.ops_pddl.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
lex.ops_pddl.o: /usr/include/getopt.h
test_main.o: libff.h ff.h /usr/include/stdlib.h /usr/include/features.h
test_main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
test_main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
test_main.o: /usr/include/sys/types.h /usr/include/bits/types.h
test_main.o: /usr/include/bits/typesizes.h /usr/include/time.h
test_main.o: /usr/include/endian.h /usr/include/bits/endian.h
test_main.o: /usr/include/sys/select.h /usr/include/bits/select.h
test_main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
test_main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
test_main.o: /usr/include/alloca.h /usr/include/stdio.h /usr/include/libio.h
test_main.o: /usr/include/_G_config.h /usr/include/wchar.h
test_main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
test_main.o: /usr/include/strings.h /usr/include/ctype.h
test_main.o: /usr/include/sys/timeb.h /usr/include/sys/times.h output.h
