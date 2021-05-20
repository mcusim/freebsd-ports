--- plat/nxp/soc-lx2160/lx2160acex7/ddr_init.c.orig	2021-05-20 15:55:40 UTC
+++ plat/nxp/soc-lx2160/lx2160acex7/ddr_init.c
@@ -0,0 +1,77 @@
+/*
+ * Copyright 2019 SolidRun ltd.
+ *
+ * SPDX-License-Identifier: BSD-3-Clause
+ *
+ * Author Rabeeh Khoury <rabeeh@solid-run.com>
+ */
+
+#include <platform_def.h>
+#include <stdint.h>
+#include <stdio.h>
+#include <stdlib.h>
+#include <stdbool.h>
+#include <debug.h>
+#include <errno.h>
+#include <utils.h>
+#include <string.h>
+#include <ddr.h>
+#include <i2c.h>
+
+int ddr_board_options(struct ddr_info *priv)
+{
+	struct memctl_opt *popts = &priv->opt;
+
+	popts->vref_dimm = 0x24;		/* range 1, 83.4% */
+	popts->rtt_override = 0;
+	popts->rtt_park = 240;
+	popts->otf_burst_chop_en = 0;
+	popts->burst_length = DDR_BL8;
+	popts->trwt_override = 1;
+	popts->bstopre = 0;			/* auto precharge */
+	popts->addr_hash = 1;
+	popts->trwt = 0x3;
+	popts->twrt = 0x3;
+	popts->trrt = 0x3;
+	popts->twwt = 0x3;
+	popts->vref_phy = 0x60;	/* 75% */
+	popts->odt = 48;
+	popts->phy_tx_impedance = 48;
+
+	return 0;
+}
+
+long long _init_ddr(void)
+{
+	int spd_addr[] = { 0x51, 0x53 };
+	struct ddr_info info;
+	struct sysinfo sys;
+	long long dram_size;
+
+	zeromem(&sys, sizeof(sys));
+	get_clocks(&sys);
+	debug("platform clock %lu\n", sys.freq_platform);
+	debug("DDR PLL1 %lu\n", sys.freq_ddr_pll0);
+	debug("DDR PLL2 %lu\n", sys.freq_ddr_pll1);
+
+	zeromem(&info, sizeof(info));
+
+	/* Set two DDRC. Unused DDRC will be removed automatically. */
+	info.num_ctlrs = 2;
+	info.spd_addr = spd_addr;
+	info.ddr[0] = (void *)NXP_DDR_ADDR;
+	info.ddr[1] = (void *)NXP_DDR2_ADDR;
+	info.phy[0] = (void *)NXP_DDR_PHY1_ADDR;
+	info.phy[1] = (void *)NXP_DDR_PHY2_ADDR;
+	info.clk = get_ddr_freq(&sys, 0);
+	if (!info.clk)
+		info.clk = get_ddr_freq(&sys, 1);
+	info.dimm_on_ctlr = 1;
+
+	dram_size = dram_init(&info);
+
+	if (dram_size < 0)
+		ERROR("DDR init failed.\n");
+
+	return dram_size;
+}
