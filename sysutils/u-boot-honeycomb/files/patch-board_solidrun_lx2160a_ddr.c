--- board/solidrun/lx2160a/ddr.c.orig	2021-05-12 16:57:45 UTC
+++ board/solidrun/lx2160a/ddr.c
@@ -0,0 +1,20 @@
+// SPDX-License-Identifier: GPL-2.0+
+/*
+ * Copyright 2019 SolidRun ltd.
+ */
+
+#include <common.h>
+#include <fsl_ddr_sdram.h>
+#include <fsl_ddr_dimm_params.h>
+
+DECLARE_GLOBAL_DATA_PTR;
+
+int fsl_initdram(void)
+{
+	gd->ram_size = tfa_get_dram_size();
+
+	if (!gd->ram_size)
+		gd->ram_size = fsl_ddr_sdram_size();
+
+	return 0;
+}
