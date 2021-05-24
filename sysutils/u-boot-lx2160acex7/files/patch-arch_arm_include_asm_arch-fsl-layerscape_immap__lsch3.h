--- arch/arm/include/asm/arch-fsl-layerscape/immap_lsch3.h.orig	2021-05-12 16:46:03 UTC
+++ arch/arm/include/asm/arch-fsl-layerscape/immap_lsch3.h
@@ -65,6 +65,9 @@
 #define I2C7_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01060000)
 #define I2C8_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01070000)
 #endif
+#define GPIO3_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01320000)
+#define GPIO3_GPDIR_ADDR			(GPIO3_BASE_ADDR + 0x0)
+#define GPIO3_GPDAT_ADDR			(GPIO3_BASE_ADDR + 0x8)
 #define GPIO4_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01330000)
 #define GPIO4_GPDIR_ADDR			(GPIO4_BASE_ADDR + 0x0)
 #define GPIO4_GPDAT_ADDR			(GPIO4_BASE_ADDR + 0x8)
