--- plat/nxp/tools/pbl_ch3.mk.orig	2021-05-20 16:57:45 UTC
+++ plat/nxp/tools/pbl_ch3.mk
@@ -5,7 +5,7 @@
 #
 # Author   Ruchika Gupta <ruchika.gupta@nxp.com>
 #
-SHELL=/bin/bash
+SHELL=/usr/local/bin/bash
 
 CREATE_PBL	?=	${PLAT_TOOL_PATH}/create_pbl${BIN_EXT}
 BYTE_SWAP	?=	${PLAT_TOOL_PATH}/byte_swap${BIN_EXT}
