#Name of project
PROJECT = simpleserial-ascon
TARGET = simpleserial-ascon

SRC +=  simpleserial-ascon.c ascon.c 
# ^ This line is correct for adding to C compilation, but linking might need special handling

# Path to firmware build system (ONE LEVEL UP)
CHIPWHISPERER_PATH = ..

CRYPTO_TARGET = NONE

EXTRA_OPTS = NO_EXTRA_OPTS
CFLAGS += -D$(EXTRA_OPTS)
# Source files for ASCON implementation
# Add the object file for ascon.c to the C_OBJS variable before the include
C_OBJS += $(OBJDIR)/ascon.o

include ../simpleserial/Makefile.simpleserial

FIRMWAREPATH = ../.
include $(FIRMWAREPATH)/Makefile.inc