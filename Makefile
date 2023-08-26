CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -fanalyzer -pedantic
CHECK_FLAGS := -lcheck
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CHECK_FLAGS += -lsubunit -lm
endif
LCOV_FLAGS := -fprofile-arcs -ftest-coverage

LIB_SRC_DIR := gui/slots lib main_window.c
LIB_SRC_DIR := $(addprefix ../src/, $(LIB_SRC_DIR))
LIB_SRC := $(wildcard $(addsuffix /*.c, $(LIB_SRC_DIR)))
TESTS_SRC_DIR := tests
TESTS_SRC_DIR := $(addprefix ../src/, $(TESTS_SRC_DIR))
TESTS_SRC := $(wildcard $(addsuffix /*.c, $(TESTS_SRC_DIR)))

OBJ_DIR := obj
OBJS := $(notdir $(LIB_SRC) $(TESTS_SRC))
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJS:.c=.o))

TARGET := s21_3dviewer
LIB_NAME := s21_3dviewer.a

VPATH := .:$(LIB_SRC_DIR):$(TESTS_SRC_DIR)

.PHONY : all build test gcov_report check_linters fix_linters cppcheck \
	clean_report clean_obj clean_lib clean

vpath %.o $(OBJ_DIR)/
##############################  BUILD TARGETS  #########################################
all : clean build s21_3dviewer.a check_linters test gcov_report

build : $(notdir $(OBJS))
	gcc $(OBJS) -o $(TARGET) $(CHECK_FLAGS) --coverage

%.o : %.c
	mkdir -p $(OBJ_DIR)
	gcc $< -c $(CFLAGS) $(LCOV_FLAGS) $(addprefix -I, $(LIB_SRC_DIR) \
		$(TESTS_SRC_DIR)) -MD -pipe -o $(OBJ_DIR)/$@
%.c : ;
include $(wildcard *.d)


#need fix
s21_3dviewer.a : $(notdir $(OBJS))
	ar rcv $(LIB_NAME) $(LIB_SRC:.c=.o)
	ranlib $(LIB_NAME)

test : $(TARGET)
	./$(TARGET)

gcov_report: $(wildcard *.[cho])
	lcov -t "$(TARGET)" -o $(TARGET).info -c -d $(OBJ_DIR)
	genhtml -o report $(TARGET).info
	rm -rf $(wildcard *.gc* *.info)


##############################  CHECK TARGETS  #########################################
check_linters : $(wildcard *.c)
	cp ../materials/linters/.clang-format .
	clang-format -n $(wildcard  *.[ch] */*.[ch])
	rm -f .clang-format

fix_linters : $(wildcard *.c)
	cp ../materials/linters/.clang-format .
	clang-format -i $(wildcard  *.[ch] */*.[ch])
	rm -f .clang-format

cppcheck :
	cppcheck --enable=all --suppress=missingIncludeSystem .

valgrind :
	valgrind --leak-check=full \
             --track-origins=yes \
             --verbose \
             --log-file=valgrind-out.txt \
             ./$(TARGET)


##############################  CLEAN TARGETS  #########################################
clean : clean_lib clean_obj clean_report

clean_report:
	rm -rf report
	rm -rf $(wildcard *.gc* *.info)

clean_lib:
	rm -f $(wildcard  *.a)
	rm -f $(TARGET)

clean_obj:
	rm -fr $(OBJ_DIR)
