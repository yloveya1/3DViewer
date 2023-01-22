CC 			=	gcc
CFLAGS 		=	-Wall -Wextra -std=c11
GCOV_FLAGS 	= 	-fprofile-arcs -ftest-coverage
CHECK_FLAGS =	-lcheck -lm -lpthread 
FLAGS 		=	$(CFLAGS) $(CHECK_FLAGS) $(GCOV_FLAGS)
GFLAGS 		=	$(FLAGS)

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	CHECK_FLAGS += -lsubunit -lrt
endif

vpath 			%.o objs_test
vpath 			%.d objs_test

SRCSTEST 	= 	$(wildcard back/*.c test/*.c)
OBJSTEST 	= 	$(SRCSTEST:%.c=objs_test/%.o)
DEPENDSTEST = 	$(OBJSTEST:%.o=%.d)
OBJTESTDIR 	= 	objs_test/back objs_test/test

NAME 		= 	tests
REPORT_NAME = 	report

.PHONY: all tests gcov_report clean install uninstall dvi dist

all: gcov_report install

install:
	cmake -S ./3D_Viewer -B ./install
	make -C ./install

open:
ifeq ($(UNAME), Darwin)
	open ./install/3D_Viewer.app
endif
ifeq ($(UNAME), Linux)
	./install/3D_Viewer
endif

uninstall:
	rm -rf ./install

tests: $(OBJSTEST)
	@rm -rf $(wildcard objs_test/*.gcda objs_test/test/*.gcda)
	$(CC) $(OBJSTEST) -o $(NAME) $(GFLAGS)
	./tests

-include $(DEPENDS) $(DEPENDSTEST)

clean:
	@rm -rf objs_test *.info *.a $(REPORT_NAME) $(NAME) finish *.tgz

objs_test/%.o: %.c
	@mkdir -p $(OBJTESTDIR)
	$(CC) -MMD -o $@ -c $< $(FLAGS)

gcov_report: GFLAGS += -lgcov
gcov_report: tests
	./$(NAME)
	lcov -t "$(REPORT_NAME)" -o objs_test/$(REPORT_NAME).info -c -d .
	genhtml objs_test/$(REPORT_NAME).info -o finish

dist:
	rm -rf 3D_Viewer.1.0
	mkdir 3D_Viewer.1.0
	cp -r Makefile 3D_Viewer test back QtGifImage-master 3D_Viewer.1.0/
	tar cvzf ./3D_Viewer.tgz 3D_Viewer.1.0/
	rm -rf 3D_Viewer.1.0/

# Helpers
debug: tests
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./test

san: FLAGS += -fsanitize=address -g
san: tests
	./tests

h:
ifeq ($(UNAME), Linux)
	firefox finish/index.html
endif
ifeq ($(UNAME), Darwin)
	open finish/index.html
endif
