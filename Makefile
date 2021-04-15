PROJECT             = Chip8-emu
BUILD_DIR           ?= build
APP_BIN             = $(BUILD_DIR)/$(PROJECT)
APP_SOURCES         = $(shell find src -name '*.c')
APP_OBJS            = $(patsubst %.c,$(BUILD_DIR)/%.o,$(APP_SOURCES))
COMMON_CFLAGS       = -Wall -Wextra $(shell pkg-config --cflags --libs sdl2) -Iinc/
CFLAGS              += $(COMMON_CFLAGS)
CC		    = gcc

ifneq ($(V),)
  SILENCE           =
else
  SILENCE           = @
endif

SHOW_COMMAND        := @printf "%-15s%s\n"
SHOW_CC             := $(SHOW_COMMAND) "[ $(CC) ]"
SHOW_CLEAN          := $(SHOW_COMMAND) "[ CLEAN ]"

all: $(APP_BIN)
.PHONY: all

$(APP_BIN): $(APP_OBJS)
	$(SHOW_CC) $@
	$(SILENCE)$(CC) $(CFLAGS) -o $@ $(APP_OBJS)

$(BUILD_DIR)/%.o: %.c
	$(SHOW_CC) $@
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(SHOW_CLEAN) $(BUILD_DIR)
	$(SILENCE)rm -rf $(BUILD_DIR)
.PHONY: clean



