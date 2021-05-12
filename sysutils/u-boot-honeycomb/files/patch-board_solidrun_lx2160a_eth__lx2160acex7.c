--- board/solidrun/lx2160a/eth_lx2160acex7.c.orig	2021-05-12 16:57:49 UTC
+++ board/solidrun/lx2160a/eth_lx2160acex7.c
@@ -0,0 +1,196 @@
+// SPDX-License-Identifier: GPL-2.0+
+/*
+ * Copyright 2019 SolidRun ltd.
+ *
+ */
+
+#include <common.h>
+#include <command.h>
+#include <netdev.h>
+#include <malloc.h>
+#include <fsl_mdio.h>
+#include <miiphy.h>
+#include <phy.h>
+#include <fm_eth.h>
+#include <i2c.h>
+#include <tlv_eeprom.h>
+#include <asm/io.h>
+#include <exports.h>
+#include <asm/arch/fsl_serdes.h>
+#include <fsl-mc/fsl_mc.h>
+#include <fsl-mc/ldpaa_wriop.h>
+#include <fsl-mc/fsl_mc_private.h>
+
+DECLARE_GLOBAL_DATA_PTR;
+
+int select_i2c_ch_pca9547(u8 ch);
+
+void setup_retimer_25g(int chnum)
+{
+	int i, ret;
+	u8 reg;
+	struct udevice *dev;
+
+	select_i2c_ch_pca9547(0xb); /* SMB_CLK / DATA interface */
+	/*
+	 * Assumption is that LX2 TX --> RT1 RX is at 0x22 and
+	 * RT2 TX --> LX2 RX is at 0x23.
+	 */
+	ret = i2c_get_chip_for_busnum(0, 0x23, 1, &dev);
+	if (ret) {
+		/*
+		 * On HoneyComb and ClearFog CX ver 1.1 / 1.2 there is no retimer
+		 * assembled; silently return.
+		 */
+		return;
+	}
+	ret = dm_i2c_read(dev, 0xf1, &reg, 1); /* Get full device ID */
+	if (ret) {
+		printf ("ERROR: Could not get retimer device ID\n");
+		return;
+	}
+	if (reg != 0x10) {
+		printf ("ERROR : DS250DF410 retimer not found\n");
+		return;
+	}
+	if (chnum > 0)
+		printf ("Setting up retimer channels 1..%d as 25Gbps\n",chnum);
+	if (chnum < 4)
+		printf ("Setting up retimer channels %d..4 as 10Gbps\n",chnum+1);
+
+	dm_i2c_reg_write(dev, 0xff, 0x1); /* Enable channel specific access */
+	/*
+	 * Setup 25Gbps channel on 0..chnum.
+	 * Notice that the ingress retimer is mirrorly mapped with the SERDES
+	 * number, so SERDES #0 is connected to channel #3, SERDES 1 to channel
+	 * #2 ...
+	 */
+	for (i = 0 ; i < chnum; i++) { /* Setup channels 0..chnum as 25g */
+		dm_i2c_reg_write(dev, 0xfc, 1 << i);
+		dm_i2c_reg_write(dev, 0x00, 0x4); /* Reset channel registers */
+		dm_i2c_reg_write(dev, 0x0a, 0xc); /* Assert CDR reset */
+		dm_i2c_reg_write(dev, 0x3d, 0x8f); /* Enable pre/post and set main cursor to 0xf */
+		dm_i2c_reg_write(dev, 0x3e, 0x44); /* Set pre-cursor to -4 */
+		/* Set post-cursor of channel #0 to -4 */
+		dm_i2c_reg_write(dev, 0x3f, 0x44);
+		dm_i2c_reg_write(dev, 0x0a, 0x00); /* Release CDR */
+	}
+	if (chnum < 4) {
+		/* Setup the rest of the channels as 10g */
+		for (i = chnum ; i < 4; i++) {
+			dm_i2c_reg_write(dev, 0xfc, 1 << i);
+			dm_i2c_reg_write(dev, 0x00, 0x4); /* Reset channel registers */
+			dm_i2c_reg_write(dev, 0x0a, 0xc); /* Assert CDR reset */
+			dm_i2c_reg_write(dev, 0x3d, 0x8f); /* Enable pre/post and set main cursor to 0xf */
+			dm_i2c_reg_write(dev, 0x3e, 0x44); /* Set pre-cursor to -4 */
+			/* Set post-cursor of channel #0 to -4 */
+			dm_i2c_reg_write(dev, 0x3f, 0x44);
+			dm_i2c_reg_write(dev, 0x2f, 0x04); /* Set rate to 10.3125 Gbps */
+			dm_i2c_reg_write(dev, 0x0a, 0x00); /* Release CDR */
+		}
+		ret = i2c_get_chip_for_busnum(0, 0x22, 1, &dev);
+		if (ret) {
+			printf ("ERROR: Retimer at address 0x22 not found\n");
+			return;
+		}
+		ret = dm_i2c_read(dev, 0xf1, &reg, 1); /* Get full device ID */
+		if (ret) {
+			printf ("ERROR: Could not get retimer device ID\n");
+			return;
+		}
+		if (reg != 0x10) {
+			printf ("ERROR : DS250DF410 retimer not found\n");
+			return;
+		}
+		dm_i2c_reg_write(dev, 0xff, 0x1); /* Enable channel specific access */
+		for (i = chnum ; i < 4; i++) {
+			dm_i2c_reg_write(dev, 0xfc, 1 << i);
+			dm_i2c_reg_write(dev, 0x00, 0x4); /* Reset channel registers */
+			dm_i2c_reg_write(dev, 0x0a, 0xc); /* Assert CDR reset */
+			dm_i2c_reg_write(dev, 0x2f, 0x04); /* Set rate to 10.3125 Gbps */
+			dm_i2c_reg_write(dev, 0x0a, 0x00); /* Release CDR */
+		}
+	}
+}
+
+int board_eth_init(bd_t *bis)
+{
+#if defined(CONFIG_FSL_MC_ENET)
+	struct memac_mdio_info mdio_info;
+	struct memac_mdio_controller *reg;
+	int i, interface;
+	struct mii_dev *dev;
+	struct ccsr_gur *gur = (void *)(CONFIG_SYS_FSL_GUTS_ADDR);
+	u32 srds_s1;
+
+	srds_s1 = in_le32(&gur->rcwsr[28]) &
+				FSL_CHASSIS3_RCWSR28_SRDS1_PRTCL_MASK;
+	srds_s1 >>= FSL_CHASSIS3_RCWSR28_SRDS1_PRTCL_SHIFT;
+
+	reg = (struct memac_mdio_controller *)CONFIG_SYS_FSL_WRIOP1_MDIO1;
+	mdio_info.regs = reg;
+	mdio_info.name = DEFAULT_WRIOP_MDIO1_NAME;
+
+	/* Register the EMI 1 */
+	fm_memac_mdio_init(bis, &mdio_info);
+
+	wriop_set_phy_address(WRIOP1_DPMAC17, 0,
+			      RGMII_PHY_ADDR1);
+	reg = (struct memac_mdio_controller *)CONFIG_SYS_FSL_WRIOP1_MDIO2;
+	switch (srds_s1) {
+		case 8:
+			setup_retimer_25g(0);
+			break;
+		case 13:
+		case 14:
+		case 15:
+		case 16:
+		case 17:
+		case 21:
+			/* Setup 25gb retimer on lanes e,f,g,h */
+			setup_retimer_25g(4);
+			break;
+		case 18:
+		case 19:
+			/* Setup 25gb retimer on lanes e,f and 10g on g,h */
+			setup_retimer_25g(2);
+			break;
+
+		default:
+		printf("SerDes1 protocol 0x%x is not supported on LX2160ACEX7\n",
+		       srds_s1);
+	}
+	wriop_set_phy_address(WRIOP1_DPMAC17, 0,
+			      RGMII_PHY_ADDR1);
+	interface = wriop_get_enet_if(WRIOP1_DPMAC17);
+	switch (interface) {
+	case PHY_INTERFACE_MODE_RGMII:
+	case PHY_INTERFACE_MODE_RGMII_ID:
+		dev = miiphy_get_dev_by_name(DEFAULT_WRIOP_MDIO1_NAME);
+		wriop_set_mdio(WRIOP1_DPMAC17, dev);
+	}
+
+	mac_read_from_eeprom();
+	cpu_eth_init(bis);
+#endif /* CONFIG_FSL_MC_ENET */
+
+	return pci_eth_init(bis);
+}
+
+#if defined(CONFIG_RESET_PHY_R)
+void reset_phy(void)
+{
+#if defined(CONFIG_FSL_MC_ENET)
+	mc_env_boot();
+#endif
+}
+#endif /* CONFIG_RESET_PHY_R */
+
+int fdt_fixup_board_phy(void *fdt)
+{
+	int ret;
+
+	ret = 0;
+
+	return ret;
+}
