SHELL := bash
PRINT := echo -e
RM := rm -rf

CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size

CFLAGS = -mmcu=$(MCU) -Os -Wall
LDFLAGS =

SRCS = vasilebot.c


CONFIG_FILE := config.mk


ifneq ($(MAKECMDGOALS),config)
    ifneq ($(MAKECMDGOALS),clean_config)
        ifneq ($(wildcard $(CONFIG_FILE)),)
            include $(CONFIG_FILE)
        else
            $(error No config file. Please run 'make config')
        endif
    endif
endif


default: build


print_config_banner:
	@$(PRINT) "Choose board:"
	@$(PRINT) "\t[0] VasileBot v1"
	@$(PRINT) "\t[1] Arduino Uno"
	@$(PRINT) -n "Your choice: "

read_config: print_config_banner
	$(eval CHOICE := $(shell read choice rest && echo $$choice))

config: read_config clean
	@if [ $(CHOICE) -eq 0 ];\
	then\
		$(PRINT) "BOARD := VASILEBOT_V1"				> $(CONFIG_FILE);\
		$(PRINT) "MCU := atmega328p"					>> $(CONFIG_FILE);\
		$(PRINT) "UPLOAD := ./bootloadHID -r vasilebot.hex"	>> $(CONFIG_FILE);\
		$(PRINT) "SRCS += board_vasilebot_v1.c"			>> $(CONFIG_FILE);\
		$(PRINT) "CFLAGS += -DBOARD_VASILEBOT_V1"		>> $(CONFIG_FILE);\
	elif [ $(CHOICE) -eq 1 ];\
	then\
		$(PRINT) "BOARD := ARDUINO_LEONARDO"			> $(CONFIG_FILE);\
		$(PRINT) "MCU := atmega32u4"					>> $(CONFIG_FILE);\
		$(PRINT) "UPLOAD := avrdude -p \$$(MCU) -P /dev/ttyACM0 -c avr109"\
		    "-U flash:w:vasilebot.hex"						>> $(CONFIG_FILE);\
		$(PRINT) "SRCS += board_arduino_leonardo.c"		>> $(CONFIG_FILE);\
		$(PRINT) "CFLAGS += -DBOARD_ARDUINO_LEONARDO"	>> $(CONFIG_FILE);\
	fi

clean_config: clean
	@$(RM) $(CONFIG_FILE)


build: vasilebot.hex

vasilebot.hex: vasilebot.elf
	$(OBJCOPY)  -j .text -j .data -O ihex $^ $@
	$(SIZE) $@

vasilebot.elf: $(SRCS)
	echo $(SRCS)
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
