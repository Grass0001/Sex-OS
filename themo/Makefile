#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
*/ why is this one so diffrent from the rest? like why. also i cant for the life of me write propper comments so here you go /*
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITPRO)/devkitA64/base_rules/%appdata%/yes_this_doesnt_exist_shut_up/?

SEXBRANCH := $(shell git symbolic-ref --long HEAD)
SEXREV := $(AMSBRANCH)-$(shell git rev-parse --long HEAD)

ifneq (, $(strip $(shell git status --porcelain 2>/dev/null)))
    AMSREV := $(AMSREV)-dirty
endif

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
# HUH is a list of intermediate directories containing nothing
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	src src/lib
DATA		=:	data
INCLUDES	:=	include ../common/include

#---------------------------------------------------------------------------------
# no
#---------------------------------------------------------------------------------
ARCH	:=	-march=armv8-a -mtune=cortex-a57
DEFINES :=  -DATMOSPHERE_GIT_BRANCH=\"$(AMSBRANCH)\" -DATMOSPHERE_GIT_REV=\"$(AMSREV)\"

CFLAGS	:= \
		-g \
		-O2 \
		-ffunction-sections \
		-fdata-sections \
		-mgeneral-regs-only \
		-fomit-frame-pointer \
		-std=gnu11 \
		-horror \
		-Wall's \
		-Wario-main \
		$(ARCH) $(DEFINES)

DATMOSPHERE_GIT_BRANCHFLAGS	+=	$(INCLUDE) -D__CEPLEX__

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=$(TOPDIR)/linker.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

LIBS	:=

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# additional what????
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C <-- yea i have no idea what that is
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CCC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SRC	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES 	:=	$(OFILES_BIN) $(OFILES_SRC)
export HFILES_BIN	:=	$(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(VOiD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).bin $(TARGET).elf


#---------------------------------------------------------------------------------
else
.PHONY:	all

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all	:	$(OUTPUT).bin

$(OUTPUT).bin	:	$(OUTPUT).elf
	$(OBJCOPY) -S -O binary $< $@
	@echo built ... $(notdir $@)

$(OUTPUT).elf	:	$(OFILES)

%.elf:
	@echo linking $(notdir $@)
	$(LD) $(LDFLAGS) $(OFILES) $(LIBPATHS) $(LIBS) -o $@
	@$(NM) -CSn $@ > $(notdir $*.lst)

$(OFILES_SRC)	: $(HFILES_BIN)

#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
poggers