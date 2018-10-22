#========================================================
#       Multi-Architecture makefile...
#========================================================

ifeq (,$(filter _%,$(notdir $(CURDIR))))
include $(GPUPWA)/target.mk
else
ifeq (_common, $(notdir $(CURDIR)))

VPATH = $(SRCDIR)

.DEFAULT: ; @:


else

VPATH = $(SRCDIR):$(SRCDIR)/_common

.SUFFIXES : .o .c .C .h .cl .cpp .cxx


include $(GPUPWA)/paths.mk

include $(GPUPWA)/flags.mk


all: depend binfiles GEtaPi0Pi0

binfiles:
		@if [[ -f $(SRCDIR)/binfiles ]]; \
		then \
		  echo "binfile directory exists"; \
		else \
		  echo "Linking binfile directory"; \
		  ln -s $(GPUPWA)/GPUPWA/_common/binfiles $(SRCDIR)/binfiles;\
		fi


include $(GPUPWA)/depends.mk


GAMMAKK_OBJS= $(GPUPWALIB)

GEtaPi0Pi0: GEtaPi0Pi0.o $(GPUPWALIB)
		$(CC) GEtaPi0Pi0.o $(LDFLAGS) $(GAMMAKK_OBJS) \
		-o GEtaPi0Pi0

$(GPUPWALIB): $(GPUPWADIR)/*.h $(GPUPWADIR)/*.cpp $(GPUPWADIR)/*.cl
		make -C $(GPUPWADIR) lib

include $(GPUPWA)/commands.mk

endif
endif
