# Program declarations
CC := cc65.exe
CA := ca65.exe
LD := ld65.exe
CL := cl65.exe
C1541 := C:\Program Files\Vice Team\WinVICE 1.22 Setup\WinVICE-1.22\c1541.exe
X64 := C:\Program Files\Vice Team\WinVICE 1.22 Setup\WinVICE-1.22\x64.exe -autostart
X128 := C:\Program Files\Vice Team\WinVICE 1.22 Setup\WinVICE-1.22\x128.exe -autostart
T := c128
VIC_CONFIG := vic20-32k.cfg
RM := del
CP := copy

CONFIG_SOURCES = \
	ConfigurationManager.c \
	Configuration.c \
	globals.c \
	screen.c \
	globalInput.c

SOURCES	= \
	CBM-Command.c \
	CommandMenu.c \
	Configuration.c \
	DriveMenu.c \
	drives.c \
	FileMenu.c \
	globals.c \
	input.c \
	menus.c \
	OptionMenu.c \
	screen.c  \
	globalInput.c \
	Viewer.c

ASMFILES= \
	res\common\driveRoutines.s \
	res\$(T)\PlatformSpecific.s

PROGRAM	=cbmcommand.$(T)
CONFIG_PROGRAM =cbmcmdcfg.$(T)

TITLE	=$(PROGRAM:.$(T)=)
CONFIG_TITLE =$(CONFIG_PROGRAM:.$(T)=)

LIBS	=$(T).lib

# Default target - Builds for the C64
all: $(PROGRAM)

# Launch VICE
vice: clean $(PROGRAM)
ifeq "$(T)" "c64"
		$(X64) $(T)\$(PROGRAM)
else
		$(X128) $(T)\$(PROGRAM)
endif

D64: all
	$(RM) $(TITLE).d64
	$(CP) $(TITLE)_master.d64 $(TITLE).d64
	$(CP) c64\$(TITLE).c64 $(TITLE).c64
	$(CP) c128\$(TITLE).c128 $(TITLE).c128
#	$(CP) pet\$(TITLE).pet $(TITLE).pet
	$(CP) vic20\$(TITLE).vic20 $(TITLE).vic20
	$(CP) plus4\$(TITLE).plus4 $(TITLE).plus4

	$(CP) c64\$(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	$(CP) c128\$(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
#	$(CP) pet\$(CONFIG_TITLE).pet $(CONFIG_TITLE).pet
	$(CP) vic20\$(CONFIG_TITLE).vic20 $(CONFIG_TITLE).vic20
	$(CP) plus4\$(CONFIG_TITLE).plus4 $(CONFIG_TITLE).plus4

	$(C1541) $(TITLE).d64 -write $(TITLE).c64 $(TITLE).c64
	$(C1541) $(TITLE).d64 -write $(TITLE).c128 $(TITLE).c128
#	$(C1541) $(TITLE).d64 -write $(TITLE).pet $(TITLE).pet
	$(C1541) $(TITLE).d64 -write $(TITLE).vic20 $(TITLE).vic20
	$(C1541) $(TITLE).d64 -write $(TITLE).plus4 $(TITLE).plus4

	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
#	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).pet $(CONFIG_TITLE).pet
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).vic20 $(CONFIG_TITLE).vic20
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).plus4 $(CONFIG_TITLE).plus4

	$(RM) $(TITLE).c64
	$(RM) $(TITLE).c128
#	$(RM) $(TITLE).pet
	$(RM) $(TITLE).vic20
	$(TITLE).plus4

	$(RM) $(CONFIG_TITLE).c64
	$(RM) $(CONFIG_TITLE).c128
#	$(RM) $(CONFIG_TITLE).pet
	$(RM) $(CONFIG_TITLE).vic20
	$(RM) $(CONFIG_TITLE).plus4

# Build our program
$(PROGRAM): $(SOURCES) $(ASMFILES)
ifeq "$(T)" "vic20"
		$(CL) -O -t $(T) -C $(VIC_CONFIG) -o $(T)\$(PROGRAM) $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) -O -t $(T) -C $(VIC_CONFIG) -o $(T)\$(CONFIG_PROGRAM) $(CONFIG_SOURCES) $(ASMFILES) $(LIBS)
else
		$(CL) -O -t $(T) -o $(T)\$(PROGRAM) $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) -O -t $(T) -o $(T)\$(CONFIG_PROGRAM) $(CONFIG_SOURCES) $(ASMFILES) $(LIBS)
endif

# Our phony targets for managing the project
#.PHONY: clean
clean: 
		$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.s)
		$(RM) $(CONFIG_SOURCES:.c=.o) $(CONFIG_SOURCES:.c=.s)
		$(RM) $(ASMFILES:.s=.o)
		$(RM) $(T)/$(PROGRAM)
		$(RM) $(T)/$(CONFIG_PROGRAM)

