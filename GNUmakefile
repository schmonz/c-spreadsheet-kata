SILENT		?= @

THE_TESTS	=  check_spreadsheet
THE_LIBRARY	=  spreadsheet.a

CFLAGS		+= -g -O0 -Wall -Werror -Wextra -std=c99
CHECK_CFLAGS	:= $(shell pkg-config --cflags check 2>/dev/null)
CHECK_LIBS	:= $(shell pkg-config --libs check 2>/dev/null)

all: check

check: ${THE_TESTS}
	${SILENT}./${THE_TESTS}

valgrind: ${THE_TESTS}
	${SILENT}valgrind --leak-check=full --show-leak-kinds=all ./${THE_TESTS}

clean:
	${SILENT}rm -f .has_* *.o ${THE_TESTS} ${THE_LIBRARY}
	${SILENT}rm -rf *.dSYM

.PHONY: all check valgrind clean

.has_check:
ifeq (, ${CHECK_LIBS})
	${SILENT}echo "Please install Check (https://libcheck.github.io/check/)." && false
else
	${SILENT}touch .has_check
endif

${THE_TESTS}: .has_check ${THE_LIBRARY} check_spreadsheet.c
	${SILENT}${CC} ${CFLAGS} ${CHECK_CFLAGS} -o ${THE_TESTS} check_spreadsheet.c ${THE_LIBRARY} ${CHECK_LIBS}

${THE_LIBRARY}: spreadsheet.h spreadsheet.c
	${SILENT}${CC} ${CFLAGS} -c spreadsheet.c
	${SILENT}ar rc ${THE_LIBRARY} spreadsheet.o
	${SILENT}ranlib ${THE_LIBRARY}
