SHELL := bash
PRINT := echo -e
RM := rm -rf

MCU := atmega328p

CC := avr-gcc
CFLAGS := -mmcu=$(MCU) -Os -Wall
OBJCOPY := avr-objcopy
SIZE := avr-size


CONFIG_FILE := config.mk


ifneq ($(MAKECMDGOALS),config)
    ifneq ($(wildcard $(CONFIG_FILE)),)
        include $(CONFIG_FILE)
    else
        $(error No config file. Please run 'make config')
    endif
endif


default: build


print_config_banner:
	@$(PRINT) "Choose board:"
	@$(PRINT) "\t[0] VasileBot v1"
	@$(PRINT) "\t[1] Arduino Uno"
	@$(PRINT) -n "Your choice: "

config: print_config_banner clean
	$(eval CHOICE := $(shell read choice rest && echo $$choice))
	@$(PRINT) "BOARD := $(CHOICE)" > $(CONFIG_FILE)


build: vasilebot.hex

vasilebot.hex: vasilebot.elf
	$(OBJCOPY)  -j .text -j .data -O ihex $^ $@
	$(SIZE) $@

vasilebot.elf: vasilebot.c
ifeq ($(BOARD),0)
	$(eval CFLAGS += -DBOARD_VASILEBOT_V1)
else
    ifeq ($(BOARD),1)
	$(eval CFLAGS += -DBOARD_ARDUINO_UNO)
    endif
endif

	$(CC) -o $@ $(CFLAGS) $^


clean_config: clean
	@$(RM) $(CONFIG_FILE)

clean:
	@$(RM) vasilebot.elf vasilebot.hex
