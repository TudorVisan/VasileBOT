SHELL := bash
PRINT := echo -e
RM := rm -rf

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size

CFLAGS = -mmcu=$(MCU) -Os -Wall
LDFLAGS =


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
ifeq ($(CHOICE),0)
	@$(PRINT) "BOARD := VASILEBOT_V1" > $(CONFIG_FILE)
	@$(PRINT) "MCU := atmega328p" > $(CONFIG_FILE)
	@$(PRINT) "UPLOAD := ./bootloadHID -r vasilebot.hex" > $(CONFIG_FILE)
else
    ifeq ($(CHOICE),1)
	@$(PRINT) "BOARD := ARDUINO_LEONARDO" > $(CONFIG_FILE)
	@$(PRINT) "MCU := atmega32u4" > $(CONFIG_FILE)
	@$(PRINT) "UPLOAD := avrdude -p $$(MCU) -P /dev/ttyACM0 -c avr109"\
	    "-U flash:w:vasilebot.hex" > $(CONFIG_FILE)
    endif
endif

clean_config: clean
	@$(RM) $(CONFIG_FILE)


build: vasilebot.hex

vasilebot.hex: vasilebot.elf
	$(OBJCOPY)  -j .text -j .data -O ihex $^ $@
	$(SIZE) $@

vasilebot.elf: vasilebot.c
ifeq ($(BOARD),VASILEBOT_V1)
	$(eval CFLAGS += -DBOARD_VASILEBOT_V1)
else
    ifeq ($(BOARD),ARDUINO_LEONARDO)
	$(eval CFLAGS += -DBOARD_ARDUINO_LEONARDO)
    endif
endif
	$(CC) -o $@ $(CFLAGS) $^

clean:
	@$(RM) vasilebot.elf vasilebot.hex


print_upload_warning: vasilebot.hex
ifeq ($(BOARD),VASILEBOT_V1)
	@$(PRINT) "Press reset and button 1, then release reset, release"\
	    "button 1, then you may proceed..."
else
    ifeq ($(BOARD),ARDUINO_LEONARDO)
	@$(PRINT) "Press reset button and wait for the LED to start blinking"\
	    "in a weird way, then you may proceed..."
    endif
endif

upload: print_upload_warning
	$(UPLOAD)
