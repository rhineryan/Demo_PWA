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


all: depend binfiles gammakk freegammakk freegammakk_km

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

gammakk: GammaKK.o $(GPUPWALIB)
		$(CC) GammaKK.o $(LDFLAGS) $(GAMMAKK_OBJS) \
		-o gammakk

freegammakk: FreeGammaKK.o $(GPUPWALIB)
		$(CC) FreeGammaKK.o $(LDFLAGS) $(GAMMAKK_OBJS) \
		-o freegammakk		

freegammakk_km: FreeGammaKK_km.o $(GPUPWALIB)
		$(CC) FreeGammaKK_km.o $(LDFLAGS) $(GAMMAKK_OBJS) \
		-o freegammakk_km		

$(GPUPWALIB): $(GPUPWADIR)/*.h $(GPUPWADIR)/*.cpp $(GPUPWADIR)/*.cl
		make -C $(GPUPWADIR) lib

include $(GPUPWA)/commands.mk

endif
endif


