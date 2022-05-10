# This is the name that our final kernel executable will have.
# Change as needed.
override KERNEL := kernel.elf

# It is highly recommended to use a custom built cross toolchain to build a kernel.
# We are only using "cc" as a placeholder here. It may work by using
# the host system's toolchain, but this is not guaranteed.
ifeq ($(origin CC), default)
CC := cc
endif

# Likewise, "ld" here is just a placeholder and your mileage may vary if using the
# host's "ld".
ifeq ($(origin LD), default)
LD := ld
endif

# User controllable CFLAGS.
CFLAGS ?= -O2 -g -Wall -Wextra -Wpedantic -pipe
CPPFLAGS ?= -g -Wall -Wextra -Wpedantic -pipe

# User controllable linker flags. We set none by default.
LDFLAGS ?=

# Internal C flags that should not be changed by the user.
override INTERNALCFLAGS :=   \
	-I.                  \
	-std=c11             \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-stack-check     \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD

override INTERNALCPPFLAGS :=   \
	-std=c++11                 \
	-ffreestanding             \
	-fno-exceptions            \
	-fno-stack-protector       \
	-fno-omit-frame-pointer    \
	-fno-rtti                  \
	-fno-pic                   \
	-mabi=sysv                 \
	-mno-80387                 \
	-mno-mmx                   \
	-mno-3dnow                 \
	-mno-sse                   \
	-mno-sse2                  \
	-mno-red-zone              \
	-mcmodel=kernel            \

# Internal linker flags that should not be changed by the user.
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

# Use find to glob all *.c files in the directory and extract the object names.
override CFILES := $(shell find ./ -type f -name '*.c')
override CPPFILES := $(shell find ./ -type f -name '*.cpp')
override OBJ := $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
override HEADER_DEPS := $(CFILES:.c=.d)

# Default target.
.PHONY: all
all: $(KERNEL)

limine.h:
	curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $@

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

# Compilation rules for *.c files.
-include $(HEADER_DEPS)
%.o: %.c limine.h
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

%.o: %.cpp limine.h
	$(CC) $(CPPFLAGS) $(INTERNALCPPFLAGS) -c $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f limine.h