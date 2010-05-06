# Program declarations
CC := cc65.exe
CA := ca65.exe
LD := ld65.exe
CL := cl65.exe
C1541 := c:\winvice\c1541.exe
X64 := c:\winvice\x64.exe -autostart
X128 := c:\winvice\x128.exe -autostart
T := c128

SOURCES	= \
	AssemblerMethods.c \
	CBM-Command.c \
	CommandMenu.c \
	DriveMenu.c \
	drives.c \
	FileMenu.c \
	globals.c \
	input.c \
	menus.c \
	OptionMenu.c \
	screen.c 

ASMFILES= \
	res\$(T)\Text.s \
	res\common\Common.s \
	res\common\CommandMenu.s \
	res\common\DriveMenu.s \
	res\common\driveRoutines.s \
	res\$(T)\FileMenu.s \
	res\$(T)\OptionsMenu.s \
	res\$(T)\PlatformSpecific.s

PROGRAM	=cbmcommand.$(T)

TITLE	=$(PROGRAM:.$(T)=)

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
	cp c64\$(TITLE).c64 $(TITLE).c64
	cp c128\$(TITLE).c128 $(TITLE).c128
	$(C1541) -format $(TITLE),id d64 $(TITLE).d64
	$(C1541) $(TITLE).d64 -write $(TITLE).c64 $(TITLE).c64
	$(C1541) $(TITLE).d64 -write $(TITLE).c128 $(TITLE).c128
	rm $(PROGRAM)

# Build our program
#$(PROGRAM): $(SOURCES:.c=.o) $(ASMFILES:.s=.o)
#		$(LD) -t $(T) -o $(T)\$@ $^ $(LIBS)

$(PROGRAM): $(SOURCES) $(ASMFILES)
		$(CL) -O -t $(T) -o $(T)\$(PROGRAM) $(SOURCES) $(ASMFILES) $(LIBS)

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
		$(RM) $(ASMFILES:.s=.o)
		$(RM) $(T)/$(PROGRAM)

