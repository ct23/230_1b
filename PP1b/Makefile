# A simple makefile
#    When ready, add testGetNTokens testPass1 assembler to all:
all:	testLabelTable

testLabelTable: assembler.h \
	LabelTable.o \
	printDebug.o \
	printError.o \
    	testLabelTable.o
	gcc -g LabelTable.o printDebug.o printError.o testLabelTable.o \
	    	-o testLabelTable

testGetNTokens: 	assembler.h \
	getToken.o \
	getNTokens.o \
	printDebug.o \
	printError.o \
    	testGetNTokens.o
	gcc -g testGetNTokens.o getNTokens.o getToken.o \
	    printDebug.o printError.o -o testGetNTokens

testPass1: 	assembler.h \
    	LabelTable.o \
	getToken.o \
	getNTokens.o \
	pass1.o \
	printDebug.o \
	printError.o \
	testPass1.o
	gcc -g LabelTable.o getNTokens.o getToken.o pass1.o \
	    printDebug.o printError.o testPass1.o -o testPass1

assembler: 	assembler.h \
    	LabelTable.o \
	getToken.o \
	getNTokens.o \
	pass1.o \
	pass2.o \
	printDebug.o \
	printError.o \
	assembler.o
	gcc -g LabelTable.o getNTokens.o getToken.o pass1.o pass2.o \
	    printDebug.o printError.o assembler.o -o assembler

#assembler.h: LabelTable.h getToken.h printFuncs.h
assembler.h: LabelTable.h printFuncs.h
	touch assembler.h

LabelTable.o: LabelTable.h LabelTable.c
	gcc -c -g LabelTable.c 

printDebug.o: printFuncs.h printDebug.c
	gcc -c -g printDebug.c

printError.o: printFuncs.h printError.c
	gcc -c -g printError.c

testLabelTable.o: assembler.h LabelTable.h testLabelTable.c
	gcc -c -g testLabelTable.c

getToken.o: getToken.h getToken.c
	gcc -c -g getToken.c

getNTokens.o: getToken.h getNTokens.c
	gcc -c -g getNTokens.c

testGetNTokens.o: assembler.h testGetNTokens.c
	gcc -c -g testGetNTokens.c

pass1.o: assembler.h pass1.c
	gcc -c -g pass1.c

testPass1.o: assembler.h testPass1.c
	gcc -c -g testPass1.c

pass2.o: assembler.h pass2.c
	gcc -c -g pass2.c

assembler.o: assembler.h assembler.c
	gcc -c -g assembler.c

clean: 
	rm -rf *.o testLabelTable testGetNTokens testPass1 assembler
