# Program declarations
CC := cc65.exe
CA := ca65.exe
LD := ld65.exe
CL := cl65.exe

C1541 := c:\winvice\c1541.exe
X64 := c:\winvice\x64.exe -autostart
X128 := c:\winvice\x128.exe -autostart
XPET := c:\winvice\xpet.exe -autostart
XVIC := c:\winvice\xvic.exe -autostart
XPLUS4 := c:\winvice\xplus4.exe -autostart
CP := cp

T := vic20

VIC_CONFIG := vic20-32k-big.cfg

ifeq "$(T)" "vic20"
LD_CONFIG := -C $(VIC_CONFIG)
endif

CONFIG_SOURCES = \
	ConfigurationManager.c \
	Configuration.c \
	globals.c \
	screen.c \
	globalInput.c

SOURCES	= \
	CBM-Command.c \
	Configuration.c \
	DriveMenu.c \
	drives.c \
	FileMenu.c \
	globals.c \
	input.c \
	menus.c \
	screen.c  \
	globalInput.c \
	Viewer.c

#	CommandMenu.c \
#	OptionMenu.c \

ASMFILES= \
	res\common\driveRoutines.s \
	res\$(T)\PlatformSpecific.s

PROGRAM	=cbmcommand.$(T)
CONFIG_PROGRAM =cbmcmdcfg.$(T)

TITLE	=$(PROGRAM:.$(T)=)
CONFIG_TITLE =$(CONFIG_PROGRAM:.$(T)=)

#LIBS	=$(T).lib

# Default target -- Builds for the VIC-20
#.PHONY: all
all: $(PROGRAM)

# Launch VICE
#.PHONY: vice
vice: clean $(PROGRAM)
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
	$(CP) c64\$(TITLE).c64 $(TITLE).c64
	$(CP) c128\$(TITLE).c128 $(TITLE).c128
	$(CP) pet\$(TITLE).pet80 $(TITLE).pet80
	$(CP) pet\$(TITLE).pet40 $(TITLE).pet40
	$(CP) vic20\$(TITLE).vic20 $(TITLE).vic20
	$(CP) plus4\$(TITLE).plus4 $(TITLE).plus4

	$(CP) c64\$(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	$(CP) c128\$(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
	$(CP) pet\$(CONFIG_TITLE).pet80 $(CONFIG_TITLE).pet80
	$(CP) pet\$(CONFIG_TITLE).pet40 $(CONFIG_TITLE).pet40
	$(CP) vic20\$(CONFIG_TITLE).vic20 $(CONFIG_TITLE).vic20
	$(CP) plus4\$(CONFIG_TITLE).plus4 $(CONFIG_TITLE).plus4

	$(C1541) $(TITLE).d64 -write $(TITLE).c64 $(TITLE).c64
	$(C1541) $(TITLE).d64 -write $(TITLE).c128 $(TITLE).c128
	$(C1541) $(TITLE).d64 -write $(TITLE).pet80 $(TITLE).pet80
#	$(C1541) $(TITLE).d64 -write $(TITLE).pet40 $(TITLE).pet40
	$(C1541) $(TITLE).d64 -write $(TITLE).vic20 $(TITLE).vic20
	$(C1541) $(TITLE).d64 -write $(TITLE).plus4 $(TITLE).plus4

	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c64 $(CONFIG_TITLE).c64
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).c128 $(CONFIG_TITLE).c128
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).pet80 $(CONFIG_TITLE).pet80
#	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).pet40 $(CONFIG_TITLE).pet40
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).vic20 $(CONFIG_TITLE).vic20
	$(C1541) $(TITLE).d64 -write $(CONFIG_TITLE).plus4 $(CONFIG_TITLE).plus4

	$(RM) $(TITLE).c64
	$(RM) $(TITLE).c128
	$(RM) $(TITLE).pet?0
	$(RM) $(TITLE).vic20
	$(RM) $(TITLE).plus4

	$(RM) $(CONFIG_TITLE).c64
	$(RM) $(CONFIG_TITLE).c128
	$(RM) $(CONFIG_TITLE).pet?0
	$(RM) $(CONFIG_TITLE).vic20
	$(RM) $(CONFIG_TITLE).plus4

# Build our programs
$(PROGRAM): $(SOURCES) $(ASMFILES)
ifeq "$(T)" "pet"
		$(CL) -D _PET80_ $(CPPFLAGS) -Or -t pet -o pet\$(TITLE).pet80 $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) -D _PET80_ $(CPPFLAGS) -Or -t pet -o pet\$(CONFIG_TITLE).pet80 $(CONFIG_SOURCES) res/pet/PlatformSpecific.s $(LIBS)
		$(CL) $(CPPFLAGS) -Or -t pet -o pet\$(TITLE).pet40 $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) $(CPPFLAGS) -Or -t pet -o pet\$(CONFIG_TITLE).pet40 $(CONFIG_SOURCES) res/pet/PlatformSpecific.s $(LIBS)
else
		$(CL) $(CPPFLAGS) -Or -t $(T) $(LD_CONFIG) -o $(T)\$(PROGRAM) $(SOURCES) $(ASMFILES) $(LIBS)
		$(CL) $(CPPFLAGS) -Or -t $(T) $(LD_CONFIG) -o $(T)\$(CONFIG_PROGRAM) $(CONFIG_SOURCES) res/$(T)/PlatformSpecific.s $(LIBS)
endif

# Our phony targets for managing the project
#.PHONY: clean
clean:
		$(RM) $(SOURCES:.c=.o) $(SOURCES:.c=.s)
		$(RM) $(CONFIG_SOURCES:.c=.o) $(CONFIG_SOURCES:.c=.s)
		$(RM) $(ASMFILES:.s=.o)
ifeq "$(T)" "pet"
		$(RM) pet/$(TITLE).pet* pet/$(CONFIG_TITLE).pet*
else
		$(RM) $(T)/$(PROGRAM) $(T)/$(CONFIG_PROGRAM)
endif

