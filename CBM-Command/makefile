# Program declarations
CC := cc65.exe
CA := ca65.exe
LD := ld65.exe
CL := cl65.exe
C1541 := c:\winvice\c1541.exe
X64 := c:\winvice\x64.exe -autostart
X128 := c:\winvice\x128.exe -autostart
T := c128

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
	globalInput.c

ASMFILES= \
	res\common\driveRoutines.s \
	res\$(T)\PlatformSpecific.s

#	res\common\Common.s \
#	res\$(T)\Text.s \
#	res\common\CommandMenu.s \
#	res\common\DriveMenu.s \
#	res\$(T)\FileMenu.s \
#	res\$(T)\OptionsMenu.s \

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

A2Disk: T:=apple2enh
A2Disk: all
	cp PRODOS203.DSK a2cmd.dsk
	cp apple2enh\cbmcommand.apple2enh a2command.bin
	java -jar AppleCommander-1.3.5.jar -cc65 a2cmd.dsk a2command bin < a2command.bin
	rm a2command.bin

D64: all
	cp c64\$(TITLE).c64 $(TITLE).c64
	cp c128\$(TITLE).c128 $(TITLE).c128
	cp c64\$(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	cp c128\$(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
	$(C1541) -format $(TITLE),id d64 $(TITLE).d64
	$(C1541) $(TITLE).d64 -write loadcbmcmd loadcbmcmd
	$(C1541) $(TITLE).d64 -write $(TITLE).c64 $(TITLE).c64
	$(C1541) $(TITLE).d64 -write $(TITLE).c128 $(TITLE).c128
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
	rm $(TITLE).c64
	rm $(TITLE).c128
	rm $(CONFIG_TITLE).c64
	rm $(CONFIG_TITLE).c128

# Build our program
#$(PROGRAM): $(SOURCES:.c=.o) $(ASMFILES:.s=.o)
#		$(LD) -t $(T) -o $(T)\$@ $^ $(LIBS)

$(PROGRAM): $(SOURCES) $(ASMFILES)
		$(CL) -O -t $(T) -o $(T)\$(PROGRAM) $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) -O -t $(T) -o $(T)\$(CONFIG_PROGRAM) $(CONFIG_SOURCES) $(ASMFILES) $(LIBS)

# Assemble 
$(SOURCES:.c=.o): $(SOURCES:.c=.s)
	$(foreach F, $(SOURCES:.c=.s), \
		$(shell	$(CA) -t $(T) $(F)))

# Compile 
$(SOURCES:.c=.s): $(SOURCES)
#	$(foreach F, $(SOURCES), \
#		$(shell $(CC) -Oi -t $(T) $(F)))
		
		

# Assemble our resources
$(ASMFILES:.s=.o): $(ASMFILES)
	$(foreach F, $(ASMFILES), \
		$(shell	$(CA) -t $(T) $(F)))

# Our phony targets for managing the project
#.PHONY: clean
clean: 
		$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.s)
		$(RM) $(CONFIG_SOURCES:.c=.o) $(CONFIG_SOURCES:.c=.s)
		$(RM) $(ASMFILES:.s=.o)
		$(RM) $(T)/$(PROGRAM)
		$(RM) $(T)/$(CONFIG_PROGRAM)

