--- plat/nxp/common/common.mk.orig	2021-05-20 15:51:54 UTC
+++ plat/nxp/common/common.mk
@@ -148,6 +148,11 @@ BOOT_DEV_SOURCES		=	${PLAT_DRIVERS_PATH}/sd/sd_mmc.c	\
 else ifeq (${BOOT_MODE}, flexspi_nor)
 $(eval $(call add_define,FLEXSPI_NOR_BOOT))
 BOOT_DEV_SOURCES		= ${PLAT_DRIVERS_PATH}/flexspi/nor/flexspi_nor.c
+else ifeq (${BOOT_MODE}, auto)
+$(eval $(call add_define,FLEXSPI_NOR_BOOT))
+BOOT_DEV_SOURCES		= ${PLAT_DRIVERS_PATH}/flexspi/nor/flexspi_nor.c \
+				  ${PLAT_DRIVERS_PATH}/sd/sd_mmc.c	\
+				  drivers/io/io_block.c
 endif
 
 # DDR driver needs to be enabled by default
