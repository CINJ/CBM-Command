# Program declarations
CC := cc65.exe
CA := ca65.exe
LD := ld65.exe
CL := cl65.exe

# POSIX-style programs
CHMOD := chmod.exe +w
CP := cp.exe
#MKDIR := mkdir.exe

# VICE programs
C1541 := c:\winvice\c1541.exe
X64 := c:\winvice\x64.exe -autostart
X128 := c:\winvice\x128.exe -autostart
XPET := c:\winvice\xpet.exe -autostart
XVIC := c:\winvice\xvic.exe -autostart
XPLUS4 := c:\winvice\xplus4.exe -autostart

T := c128

VIC_CONFIG := vic20-32k.cfg

ifeq "$(T)" "vic20"
LD_CONFIG := -C $(VIC_CONFIG)
endif

CONFIG_SOURCES := \
	Configuration.c \
	ConfigurationManager.c \
	globalInput.c \
	globals.c \
	screen.c

SOURCES	:= \
	CBM-Command.c \
	CBM-REL.c \
	Configuration.c \
	DriveMenu.c \
	drives.c \
	FileMenu.c \
	globalInput.c \
	globals.c \
	input.c \
	menus.c \
	screen.c \
	Viewer.c \
	builtStamp.c
# builtStamp.c should be last in the list.

ASMFILES := \
	res\common\driveRoutines.s \
	res\$(T)\PlatformSpecific.s

#DEBUG := --check-stack
CFLAGS := -Wl -D,__STACKSIZE__=$$400
CFLAGS1 := $(CFLAGS) $(DEBUG) #-m $(T)\cmd.map
CFLAGS2 := $(CFLAGS) #-m $(T)\cfg.map

TITLE := cbmcommand
CONFIG_TITLE := cbmcmdcfg

PROGRAM := $(TITLE).$(T)
CONFIG_PROGRAM := $(CONFIG_TITLE).$(T)

#LIBS := $(T)\cc65.lib

# Default target -- Builds for the C128
#.PHONY: all
ifeq "$(T)" "pet"
all: pet\$(PROGRAM)40 pet\$(PROGRAM)80 pet\$(CONFIG_PROGRAM)40 pet\$(CONFIG_PROGRAM)80
else
all: $(T)\$(PROGRAM) $(T)\$(CONFIG_PROGRAM)
endif

# Launch VICE
#.PHONY: vice
vice: clean $(T)\$(PROGRAM)
ifeq "$(T)" "c64"
		$(X64) $(T)\$(PROGRAM)
endif
ifeq "$(T)" "c128"
		$(X128) $(T)\$(PROGRAM)
endif
ifeq "$(T)" "pet"
		$(XPET) $(T)\$(TITLE).pet80
#		$(XPET) $(T)\$(TITLE).pet40
endif
ifeq "$(T)" "vic20"
		$(XVIC) $(T)\$(PROGRAM)
endif
ifeq "$(T)" "plus4"
		$(XPLUS4) $(T)\$(PROGRAM)
endif

#.PHONY: D64
D64: all
	$(RM) $(TITLE).d64
	$(CP) $(TITLE)_master.d64 $(TITLE).d64
	$(CHMOD) $(TITLE).d64

	$(C1541) $(TITLE).d64 -write c64\$(TITLE).c64
	$(C1541) $(TITLE).d64 -write c128\$(TITLE).c128
#	$(C1541) $(TITLE).d64 -write pet\$(TITLE).pet80
#	$(C1541) $(TITLE).d64 -write pet\$(TITLE).pet40
	$(C1541) $(TITLE).d64 -write vic20\$(TITLE).vic20
	$(C1541) $(TITLE).d64 -write plus4\$(TITLE).plus4

	$(C1541) $(TITLE).d64 -write c64\$(CONFIG_TITLE).c64
	$(C1541) $(TITLE).d64 -write c128\$(CONFIG_TITLE).c128
#	$(C1541) $(TITLE).d64 -write pet\$(CONFIG_TITLE).pet80
#	$(C1541) $(TITLE).d64 -write pet\$(CONFIG_TITLE).pet40
	$(C1541) $(TITLE).d64 -write vic20\$(CONFIG_TITLE).vic20
	$(C1541) $(TITLE).d64 -write plus4\$(CONFIG_TITLE).plus4

# Build our programs
$(T)\$(PROGRAM) pet\$(PROGRAM)40: $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) $(CFLAGS1) -Or -t $(T) $(LD_CONFIG) -o $@ $+

pet\$(PROGRAM)80: $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) -D _PET80_ $(CFLAGS1) -Or -t pet -o $@ $+

$(T)\$(CONFIG_PROGRAM) pet\$(CONFIG_PROGRAM)40: $(CONFIG_SOURCES) res\$(T)\PlatformSpecific.s $(LIBS)
		$(CL) $(CFLAGS2) -Or -t $(T) $(LD_CONFIG) -o $@ $+

pet\$(CONFIG_PROGRAM)80: $(CONFIG_SOURCES) res\pet\PlatformSpecific.s $(LIBS)
		$(CL) -D _PET80_ $(CFLAGS2) -Or -t pet -o $@ $+

# Our cleaning targets, for managing the project
#.PHONY: mostly-clean clean zap
mostly-clean:
		$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.s)
		$(RM) $(CONFIG_SOURCES:.c=.o) $(CONFIG_SOURCES:.c=.s)
		$(RM) $(ASMFILES:.s=.o)

clean: mostly-clean
ifeq "$(T)" "pet"
		$(RM) ${wildcard pet/$(TITLE).pet*} ${wildcard pet/$(CONFIG_TITLE).pet*}
else
		$(RM) $(T)\$(PROGRAM) $(T)\$(CONFIG_PROGRAM)
endif

zap: clean
	$(RM) $(TITLE).d64
