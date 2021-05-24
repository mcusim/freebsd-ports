--- board/solidrun/lx2160a/lx2160a.c.orig	2021-05-12 16:58:02 UTC
+++ board/solidrun/lx2160a/lx2160a.c
@@ -0,0 +1,371 @@
+// SPDX-License-Identifier: GPL-2.0+
+/*
+ * Copyright 2019-2021 SolidRun ltd.
+ */
+
+#include <common.h>
+#include <clock_legacy.h>
+#include <dm.h>
+#include <dm/platform_data/serial_pl01x.h>
+#include <i2c.h>
+#include <malloc.h>
+#include <errno.h>
+#include <netdev.h>
+#include <fsl_ddr.h>
+#include <fsl_sec.h>
+#include <asm/io.h>
+#include <fdt_support.h>
+#include <linux/libfdt.h>
+#include <fsl-mc/fsl_mc.h>
+#include <env_internal.h>
+#include <efi_loader.h>
+#include <asm/arch/mmu.h>
+#include <hwconfig.h>
+#include <asm/arch/clock.h>
+#include <asm/arch/config.h>
+#include <asm/arch/fsl_serdes.h>
+#include <asm/arch/soc.h>
+#include "../../freescale/common/vid.h"
+#include <fsl_immap.h>
+#include <asm/arch-fsl-layerscape/fsl_icid.h>
+#include <asm/gic-v3.h>
+
+#ifdef CONFIG_EMC2301
+#include "../common/emc2301.h"
+#endif
+
+
+DECLARE_GLOBAL_DATA_PTR;
+
+static struct pl01x_serial_platdata serial0 = {
+#if CONFIG_CONS_INDEX == 0
+	.base = CONFIG_SYS_SERIAL0,
+#elif CONFIG_CONS_INDEX == 1
+	.base = CONFIG_SYS_SERIAL1,
+#else
+#error "Unsupported console index value."
+#endif
+	.type = TYPE_PL011,
+};
+
+U_BOOT_DEVICE(nxp_serial0) = {
+	.name = "serial_pl01x",
+	.platdata = &serial0,
+};
+
+static struct pl01x_serial_platdata serial1 = {
+	.base = CONFIG_SYS_SERIAL1,
+	.type = TYPE_PL011,
+};
+
+U_BOOT_DEVICE(nxp_serial1) = {
+	.name = "serial_pl01x",
+	.platdata = &serial1,
+};
+
+int select_i2c_ch_pca9547(u8 ch)
+{
+	int ret;
+
+#ifndef CONFIG_DM_I2C
+	ret = i2c_write(I2C_MUX_PCA_ADDR_PRI, 0, 1, &ch, 1);
+#else
+	struct udevice *dev;
+
+	ret = i2c_get_chip_for_busnum(0, I2C_MUX_PCA_ADDR_PRI, 1, &dev);
+	if (!ret)
+		ret = dm_i2c_write(dev, 0, &ch, 1);
+#endif
+	if (ret) {
+		puts("PCA: failed to select proper channel\n");
+		return ret;
+	}
+
+	return 0;
+}
+
+static void uart_get_clock(void)
+{
+	serial0.clock = get_serial_clock();
+	serial1.clock = get_serial_clock();
+}
+
+int board_early_init_f(void)
+{
+#ifdef CONFIG_SYS_I2C_EARLY_INIT
+	i2c_early_init_f();
+#endif
+	/* get required clock for UART IP */
+	uart_get_clock();
+
+#ifdef CONFIG_EMC2301
+	select_i2c_ch_pca9547(I2C_MUX_CH_EMC2301);
+	emc2301_init();
+	set_fan_speed(I2C_EMC2301_PWM);
+	select_i2c_ch_pca9547(I2C_MUX_CH_DEFAULT);
+#endif
+	fsl_lsch3_early_init_f();
+	return 0;
+}
+
+#ifdef CONFIG_OF_BOARD_FIXUP
+int board_fix_fdt(void *fdt)
+{
+	char *reg_name, *old_str, *new_str;
+	const char *reg_names;
+	int names_len, old_str_len, new_str_len, remaining_str_len;
+	struct str_map {
+		char *old_str;
+		char *new_str;
+	} reg_names_map[] = {
+		{ "ccsr", "dbi" },
+		{ "pf_ctrl", "ctrl" }
+	};
+	int off = -1, i;
+
+	if (IS_SVR_REV(get_svr(), 1, 0))
+		return 0;
+
+	off = fdt_node_offset_by_compatible(fdt, -1, "fsl,lx2160a-pcie");
+	while (off != -FDT_ERR_NOTFOUND) {
+		fdt_setprop(fdt, off, "compatible", "fsl,ls-pcie",
+			    strlen("fsl,ls-pcie") + 1);
+
+		reg_names = fdt_getprop(fdt, off, "reg-names", &names_len);
+		if (!reg_names)
+			continue;
+
+		reg_name = (char *)reg_names;
+		remaining_str_len = names_len - (reg_name - reg_names);
+		i = 0;
+		while ((i < ARRAY_SIZE(reg_names_map)) && remaining_str_len) {
+			old_str = reg_names_map[i].old_str;
+			new_str = reg_names_map[i].new_str;
+			old_str_len = strlen(old_str);
+			new_str_len = strlen(new_str);
+			if (memcmp(reg_name, old_str, old_str_len) == 0) {
+				/* first only leave required bytes for new_str
+				 * and copy rest of the string after it
+				 */
+				memcpy(reg_name + new_str_len,
+				       reg_name + old_str_len,
+				       remaining_str_len - old_str_len);
+				/* Now copy new_str */
+				memcpy(reg_name, new_str, new_str_len);
+				names_len -= old_str_len;
+				names_len += new_str_len;
+				i++;
+			}
+
+			reg_name = memchr(reg_name, '\0', remaining_str_len);
+			if (!reg_name)
+				break;
+
+			reg_name += 1;
+
+			remaining_str_len = names_len - (reg_name - reg_names);
+		}
+
+		fdt_setprop(fdt, off, "reg-names", reg_names, names_len);
+		off = fdt_node_offset_by_compatible(fdt, off,
+						    "fsl,lx2160a-pcie");
+	}
+
+	return 0;
+}
+#endif
+
+int esdhc_status_fixup(void *blob, const char *compat)
+{
+	/* Enable both esdhc DT nodes for LX2160ARDB */
+	do_fixup_by_compat(blob, compat, "status", "okay",
+			   sizeof("okay"), 1);
+	return 0;
+}
+
+#if defined(CONFIG_VID)
+int i2c_multiplexer_select_vid_channel(u8 channel)
+{
+	return select_i2c_ch_pca9547(channel);
+}
+
+#endif
+
+int checkboard(void)
+{
+	enum boot_src src = get_boot_src();
+	char buf[64];
+	cpu_name(buf);
+	printf("Board: %s-CEX7, ", buf);
+
+	if (src == BOOT_SOURCE_SD_MMC) {
+		puts("SD\n");
+	} else if (src == BOOT_SOURCE_SD_MMC2) {
+		puts("eMMC\n");
+	} else {
+		puts("FlexSPI DEV#0\n");
+	}
+	puts("SERDES1 Reference: Clock1 = 161.13MHz Clock2 = 100MHz\n");
+	puts("SERDES2 Reference: Clock1 = 100MHz Clock2 = 100MHz\n");
+	puts("SERDES3 Reference: Clock1 = 100MHz Clock2 = 100Hz\n");
+	return 0;
+}
+
+int config_board_mux(void)
+{
+	return 0;
+}
+
+unsigned long get_board_sys_clk(void)
+{
+	return 100000000;
+}
+
+unsigned long get_board_ddr_clk(void)
+{
+	return 100000000;
+}
+
+int board_init(void)
+{
+#ifdef CONFIG_ENV_IS_NOWHERE
+	gd->env_addr = (ulong)&default_environment[0];
+#endif
+
+	select_i2c_ch_pca9547(I2C_MUX_CH_DEFAULT);
+
+#ifdef CONFIG_FSL_CAAM
+	sec_init();
+#endif
+
+	return 0;
+}
+
+void detail_board_ddr_info(void)
+{
+	int i;
+	u64 ddr_size = 0;
+
+	puts("\nDDR    ");
+	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
+		ddr_size += gd->bd->bi_dram[i].size;
+	print_size(ddr_size, "");
+	print_ddr_info(0);
+}
+
+#ifdef CONFIG_MISC_INIT_R
+int misc_init_r(void)
+{
+	config_board_mux();
+
+	return 0;
+}
+#endif
+
+#ifdef CONFIG_FSL_MC_ENET
+extern int fdt_fixup_board_phy(void *fdt);
+
+void fdt_fixup_board_enet(void *fdt)
+{
+	int offset;
+
+	offset = fdt_path_offset(fdt, "/soc/fsl-mc");
+
+	if (offset < 0)
+		offset = fdt_path_offset(fdt, "/fsl-mc");
+
+	if (offset < 0) {
+		printf("%s: fsl-mc node not found in device tree (error %d)\n",
+		       __func__, offset);
+		return;
+	}
+
+	if (get_mc_boot_status() == 0 &&
+	    (is_lazy_dpl_addr_valid() || get_dpl_apply_status() == 0)) {
+		fdt_status_okay(fdt, offset);
+		fdt_fixup_board_phy(fdt);
+	} else {
+		fdt_status_fail(fdt, offset);
+	}
+}
+
+void board_quiesce_devices(void)
+{
+	fsl_mc_ldpaa_exit(gd->bd);
+}
+#endif
+
+#ifdef CONFIG_OF_BOARD_SETUP
+
+int ft_board_setup(void *blob, bd_t *bd)
+{
+	int i;
+	bool mc_memory_bank = false;
+
+	u64 *base;
+	u64 *size;
+	u64 mc_memory_base = 0;
+	u64 mc_memory_size = 0;
+	u16 total_memory_banks;
+
+	ft_cpu_setup(blob, bd);
+
+	fdt_fixup_mc_ddr(&mc_memory_base, &mc_memory_size);
+
+	if (mc_memory_base != 0)
+		mc_memory_bank = true;
+
+	total_memory_banks = CONFIG_NR_DRAM_BANKS + mc_memory_bank;
+
+	base = calloc(total_memory_banks, sizeof(u64));
+	size = calloc(total_memory_banks, sizeof(u64));
+
+	/* fixup DT for the three GPP DDR banks */
+	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
+		base[i] = gd->bd->bi_dram[i].start;
+		size[i] = gd->bd->bi_dram[i].size;
+	}
+
+#ifdef CONFIG_RESV_RAM
+	/* reduce size if reserved memory is within this bank */
+	if (gd->arch.resv_ram >= base[0] &&
+	    gd->arch.resv_ram < base[0] + size[0])
+		size[0] = gd->arch.resv_ram - base[0];
+	else if (gd->arch.resv_ram >= base[1] &&
+		 gd->arch.resv_ram < base[1] + size[1])
+		size[1] = gd->arch.resv_ram - base[1];
+	else if (gd->arch.resv_ram >= base[2] &&
+		 gd->arch.resv_ram < base[2] + size[2])
+		size[2] = gd->arch.resv_ram - base[2];
+#endif
+
+	if (mc_memory_base != 0) {
+		for (i = 0; i <= total_memory_banks; i++) {
+			if (base[i] == 0 && size[i] == 0) {
+				base[i] = mc_memory_base;
+				size[i] = mc_memory_size;
+				break;
+			}
+		}
+	}
+
+	fdt_fixup_memory_banks(blob, base, size, total_memory_banks);
+
+#ifdef CONFIG_USB
+	fsl_fdt_fixup_dr_usb(blob, bd);
+#endif
+
+#ifdef CONFIG_FSL_MC_ENET
+	fdt_fsl_mc_fixup_iommu_map_entry(blob);
+	fdt_fixup_board_enet(blob);
+#endif
+	printf ("Releasing fan controller full speed gpio\n");
+	/*
+	 * Set the GPIO to be input; the on-COM pullup will disable the full speed
+	 * signal.
+	 */
+	out_le32(GPIO3_GPDIR_ADDR, (~(1 << 29) &
+		in_le32(GPIO3_GPDIR_ADDR)));
+	return 0;
+}
+#endif
