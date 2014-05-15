PROJECT = report_system
CFG = Release
CC = g++

OBJ_DIR = ../obj
OUTPUT_DIR = ../bin
TARGET = repsys
C_INCLUDE_DIRS = 
C_PREPROC = 
CFLAGS = -pipe  -Wall -g0 -O2 -frtti -fexceptions 
RC_INCLUDE_DIRS = 
RC_PREPROC = 
RCFLAGS = 
LIB_DIRS = 
LIBS = 
LDFLAGS = -pipe -s 

SRC_OBJS = \
	$(OBJ_DIR)/main.o \
  $(OBJ_DIR)/report_generator.o \
  $(OBJ_DIR)/parameters_array.o \

# Linking
define build_target
@echo Linking...
@$(CC) -o "$(OUTPUT_DIR)\$(TARGET)" $(SRC_OBJS) $(LIB_DIRS) $(LIBS) $(LDFLAGS)
endef

# Compiling
define compile_source
@echo Compiling $<
@$(CC) $(CFLAGS) $(C_PREPROC) $(C_INCLUDE_DIRS) -c "$<" -o "$@"
endef

.PHONY: print_header directories

$(TARGET): print_header directories $(SRC_OBJS)
	$(build_target)

.PHONY: clean cleanall

cleanall:
	@echo Deleting intermediate files for '$(PROJECT) - $(CFG)'
	-@del $(OBJ_DIR)\*.o
	-@del "$(OUTPUT_DIR)\$(TARGET)"
	-@rmdir "$(OUTPUT_DIR)"

clean:
	@echo Deleting intermediate files for '$(PROJECT) - $(CFG)'
	-@del $(OBJ_DIR)\*.o

print_header:
	@echo ---------- Configuration: $(PROJECT) - $(CFG) ----------

directories:
	-@if not exist "$(OUTPUT_DIR)\$(NULL)" mkdir "$(OUTPUT_DIR)"
	-@if not exist "$(OBJ_DIR)\$(NULL)" mkdir "$(OBJ_DIR)"
# There are not work:
#	-@mkdir -p "$(OUTPUT_DIR)"
#	-@mkdir -p "$(OBJ_DIR)"

$(OBJ_DIR)/main.o: main.cpp \
report_generator.h \
parameters_array.h \
parameter.h \
text_parameter.h \
functional_parameter.h
	$(compile_source)

$(OBJ_DIR)/report_generator.o: report_generator.cpp \
report_generator.h \
parameters_array.h \
parameter.h \
text_parameter.h \
functional_parameter.h
	$(compile_source)

$(OBJ_DIR)/parameters_array.o: parameters_array.cpp \
parameters_array.h \
parameter.h \
text_parameter.h \
functional_parameter.h
	$(compile_source)
