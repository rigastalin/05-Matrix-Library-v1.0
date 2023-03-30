CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
GCOV=-fprofile-arcs -ftest-coverage
FILE_LIB=s21_matrix
FILE_TEST=s21_matrix_test
REPORTDIR=gcovdir
OS=$(shell uname)
ifeq ($(OS), Darwin)
	LIBS=-lcheck
else
    LIBS=-lcheck -lpthread -lrt -lm -lsubunit
endif

all: clean $(FILE_LIB).a test gcov_report

$(FILE_LIB).a: $(FILE_LIB).c
	@ echo "*********LIBRARY MATRIX.A************"
	$(CC) -c $(FLAGS) $(FILE_LIB).c -o $(FILE_LIB).o
	ar rcs $(FILE_LIB).a $(FILE_LIB).o
	@ echo "*************************************"
	@ echo " "

test: clean $(FILE_LIB).a
	@ echo "***************TESTS*****************"
	$(CC) -c $(FLAGS) $(FILE_TEST).c -o $(FILE_TEST).o
	$(CC) $(FILE_TEST).o $(FILE_LIB).o $(LIBS) -o $(FILE_TEST)

	./$(FILE_TEST)
	@echo "*************************************"
	@echo " "

gcov_report: $(FILE_LIB).a
	@ echo "*************GCOV REPORT*************"
	rm -rf *.o *.a *.gcno *.gcda *.gcov *.info $(REPORTDIR)
	$(CC) $(GCOV) $(FILE_TEST).c $(LIBS) $(FILE_LIB).c -o $(FILE_LIB)

	./$(FILE_LIB)
	lcov -t "UNIT-TESTS OF $(FILE_LIB)" -o $(FILE_LIB).info -c -d .
	genhtml -o $(REPORTDIR) $(FILE_LIB).info
	@echo "*************************************"
	@echo " "

# check:
# 	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
# 	cppcheck *.c *.h
# 	python3 ../materials/linters/cpplint.py --extensions=c $(FILE_LIB).c $(FILE_LIB).h $(FILE_TEST).c
# 	@rm -f *.cfg

# leaks:
# ifeq ($(OS), Darwin)
# 	CK_FORK=no leaks --atExit -- ./s21_matrix_test
# else
# 	CK_FORK=no valgrind --tool=memcheck --leak-check=full ./s21_matrix_test
# endif

clean:
	rm -rf *.o *.a *.out *.gcno *.gcda *.gcov *.info $(REPORTDIR) $(FILE_TEST) $(FILE_LIB)
	@ echo " "
