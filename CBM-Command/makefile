# Program declarations
CC := cc65.exe
CA := ca65.exe
LD := ld65.exe
CL := cl65.exe
C1541 := c:\winvice\c1541.exe
X64 := c:\winvice\x64.exe -autostart
X128 := c:\winvice\x128.exe -autostart
T := c128
VIC_CONFIG := vic20-32k.cfg

CONFIG_SOURCES = \
	ConfigurationManager.c \
	Configuration.c \
	globals.c \
	screen.c \
	globalInput.c

SOURCES	= \
	AssemblerMethods.c \
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
	rm $(TITLE).d64
	cp $(TITLE)_master.d64 $(TITLE).d64
	cp c64\$(TITLE).c64 $(TITLE).c64
	cp c128\$(TITLE).c128 $(TITLE).c128
	cp vic20\$(TITLE).vic20 $(TITLE).vic20
	cp c64\$(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	cp c128\$(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
	cp vic20\$(CONFIG_TITLE).vic20 $(CONFIG_TITLE).vic20

	$(C1541) $(TITLE).d64 -write $(TITLE).c64 $(TITLE).c64
	$(C1541) $(TITLE).d64 -write $(TITLE).c128 $(TITLE).c128
	$(C1541) $(TITLE).d64 -write $(TITLE).vic20 $(TITLE).vic20
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).vic20 $(CONFIG_TITLE).vic20

	rm $(TITLE).c64
	rm $(TITLE).c128
	rm $(TITLE).vic20
	rm $(CONFIG_TITLE).c64
	rm $(CONFIG_TITLE).c128
	rm $(CONFIG_TITLE).vic20

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

