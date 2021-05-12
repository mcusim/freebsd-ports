--- include/configs/lx2160a_common.h.orig	2021-05-12 16:46:48 UTC
+++ include/configs/lx2160a_common.h
@@ -119,6 +119,11 @@
 #define CONFIG_SYS_I2C_RTC_ADDR		0x51  /* Channel 3*/
 
 /* EEPROM */
+#undef CONFIG_SYS_EEPROM_BUS_NUM
+#undef CONFIG_SYS_I2C_EEPROM_ADDR
+#undef CONFIG_SYS_I2C_EEPROM_ADDR_LEN
+#undef CONFIG_SYS_EEPROM_PAGE_WRITE_BITS
+#undef CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS
 #define CONFIG_ID_EEPROM
 #define CONFIG_SYS_I2C_EEPROM_NXID
 #define CONFIG_SYS_EEPROM_BUS_NUM		0
@@ -242,9 +247,20 @@ int select_i2c_ch_pca9547_sec(unsigned char ch);
 	"esbc_validate 0x80680000 ;"		\
 	"fsl_mc start mc 0x80a00000 0x80e00000\0"
 
+#define SD2_MC_INIT_CMD				\
+	"mmc dev 1; mmc read 0x80a00000 0x5000 0x1200;"	\
+	"mmc read 0x80e00000 0x7000 0x800;"	\
+	"env exists secureboot && "		\
+	"mmc read 0x80640000 0x3200 0x20 && "	\
+	"mmc read 0x80680000 0x3400 0x20 && "	\
+	"esbc_validate 0x80640000 && "		\
+	"esbc_validate 0x80680000 ;"		\
+	"fsl_mc start mc 0x80a00000 0x80e00000\0"
+
 #define EXTRA_ENV_SETTINGS			\
 	"hwconfig=fsl_ddr:bank_intlv=auto\0"	\
-	"ramdisk_addr=0x800000\0"		\
+	"ramdisk_addr=0x90000000\0"		\
+	"ramdisk_addr_r=0x90000000\0"		\
 	"ramdisk_size=0x2000000\0"		\
 	"fdt_high=0xa0000000\0"			\
 	"initrd_high=0xffffffffffffffff\0"	\
@@ -255,9 +271,9 @@ int select_i2c_ch_pca9547_sec(unsigned char ch);
 	"scripthdraddr=0x80080000\0"		\
 	"fdtheader_addr_r=0x80100000\0"		\
 	"kernelheader_addr_r=0x80200000\0"	\
-	"kernel_addr_r=0x81000000\0"		\
+	"kernel_addr_r=0x81100000\0"		\
 	"kernelheader_size=0x40000\0"		\
-	"fdt_addr_r=0x90000000\0"		\
+	"fdt_addr_r=0x81000000\0"		\
 	"load_addr=0xa0000000\0"		\
 	"kernel_size=0x2800000\0"		\
 	"kernel_addr_sd=0x8000\0"		\
@@ -268,6 +284,7 @@ int select_i2c_ch_pca9547_sec(unsigned char ch);
 	BOOTENV					\
 	"mcmemsize=0x70000000\0"		\
 	XSPI_MC_INIT_CMD				\
+	"nvme_need_init=true\0" \
 	"scan_dev_for_boot_part="		\
 		"part list ${devtype} ${devnum} devplist; "	\
 		"env exists devplist || setenv devplist 1; "	\
@@ -323,6 +340,7 @@ int select_i2c_ch_pca9547_sec(unsigned char ch);
 	func(MMC, mmc, 0) \
 	func(MMC, mmc, 1) \
 	func(SCSI, scsi, 0) \
+	func(NVME, nvme, 0) \
 	func(DHCP, dhcp, na)
 #include <config_distro_bootcmd.h>
 
