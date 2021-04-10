# OOB
# goldlinux makefile refitted for venglinux
TARGET_EXEC ?= venglinux
BUILD_NUMBER_FILE=obj/b.txt
BUILD_DIR ?= ./build
OBJECT_DIR ?= ./obj
SRC_DIRS ?= ./src
RESOURCE_DIRS ?= ./rsc
RELEASE_DIRS ?= ./release

ARGS ?= dev
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
GSRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(OBJECT_DIR)/%.o)
RSCS := $(shell find $(RESOURCE_DIRS))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -DDEBUG -g

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -lIrrlicht -ldl -o $@ $(LDFLAGS)

# c source
$(OBJECT_DIR)/%.c.o: %.c $(BUILD_NUMBER_FILE)
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(BUILD_NUMBER_CFLAGS) -c $< -o $@

# c++ source
$(OBJECT_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(BUILD_NUMBER_CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)/src
	$(RM) -r $(OBJECT_DIR)

.PHONY: run

run: $(BUILD_DIR)/$(TARGET_EXEC)
	cd build && ./venglinux $(ARGS)

debug: $(BUILD_DIR)/$(TARGET_EXEC)
	cd build && gdb --args ./venglinux $(ARGS)

package: preprun LICENSE README.md
	cp ./LICENSE ./build/
	cp ./README.md ./build/

prepare:
	mkdir build
	mkdir objs

-include $(DEPS)

MKDIR_P ?= mkdir -p

include buildnumber.mak
