
include $(TOPDIR)/config.mk

LIB	:= $(obj)libspi_nandflash.a

COBJS-$(CONFIG_FH_SPI_NAND) += spi-nand-base.o spi-nand-bbt.o spi-nand-device.o spi-nand-ids.o spi-nand-util.o

COBJS	:= $(COBJS-y)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB): $(obj).depend $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
