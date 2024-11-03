PACKAGE = hellotcl
VERSION = 1.0

HELLOTCL_CFLAGS = 

TCL = /usr
TCL_VERSION = 8.6
TCL_CFLAGS = -I$(TCL)/include
TCL_LDFLAGS = -L$(TCL)/lib64 -ltcl$(TCL_VERSION)
TCLSH = $(TCL)/bin/tclsh$(TCL_VERSION)

#TCL = /opt/tclpro
#TCL_VERSION = 8.3
#TCL_CFLAGS = -I$(TCL)/include -DUSE_TCL_STUBS=1
#TCL_LDFLAGS = -L$(TCL)/linux-ix86/lib -ltclstub$(TCL_VERSION)
#TCLSH = $(TCL)/linux-ix86/bin/tclsh$(TCL_VERSION)

#TCL = /opt/tcl80
#TCL_VERSION = 8.0
#TCL_CFLAGS = -I$(TCL)/include
#TCL_LDFLAGS = -L$(TCL)/lib -ltcl$(TCL_VERSION)

DEFINES += -DTCL_MEM_DEBUG -D_DEBUG -DDEBUG
DEFINES += -DTCLCMD_DEBUG
DEFINES += -DTCLXBASE_DEBUG
DEFINES += -DTCLDBF_DEBUG

CPPFLAGS = -g -Wall -fPIC \
    $(HELLOTCL_CFLAGS) $(TCL_CFLAGS) $(CPPTCL_CFLAGS) $(DEFINES)
LDFLAGS = -g -lstdc++ \
    $(HELLOTCL_LDFLAGS) $(TCL_LDFLAGS) $(CPPTCL_LDFLAGS)

LIB = $(PACKAGE)$(VERSION).so

OBJS = hellotcl.o tclcmd.o

# rules

all: $(LIB) pkgIndex.tcl

clean:
	-rm $(OBJS) $(LIB) pkgIndex.tcl

test: $(LIB)
	env TCLLIBPATH=. $(TCLSH) hellotcl.test -verbose bps

debug: $(LIB)
	env TCLLIBPATH=. gdb -args $(TCLSH) hellotcl.test -verbose bps

$(LIB): $(OBJS)
	cc -shared $(LDFLAGS) -o $(LIB) $(OBJS)

pkgIndex.tcl:
	@echo package ifneeded $(PACKAGE) $(VERSION) '[list load [file join $$dir $(LIB)] $(PACKAGE)]' > pkgIndex.tcl
