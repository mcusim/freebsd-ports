--- plat/nxp/soc-lx2160/lx2160acex7/platform.mk.orig	2021-05-20 15:55:53 UTC
+++ plat/nxp/soc-lx2160/lx2160acex7/platform.mk
@@ -0,0 +1,16 @@
+#
+# Copyright 2019 SolidRun ltd.
+#
+# SPDX-License-Identifier: BSD-3-Clause
+#
+# Author Rabeeh Khoury <rabeeh@solid-run.com>
+
+# board-specific build parameters
+BOOT_MODE	:= 	flexspi_nor
+BOARD		:=	acex7
+
+ # get SoC common build parameters
+include plat/nxp/soc-lx2160/soc.mk
+
+BL2_SOURCES	+=	${BOARD_PATH}/ddr_init.c
+
