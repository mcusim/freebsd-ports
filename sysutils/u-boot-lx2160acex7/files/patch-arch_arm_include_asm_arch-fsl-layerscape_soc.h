--- arch/arm/include/asm/arch-fsl-layerscape/soc.h.orig	2021-05-12 16:46:16 UTC
+++ arch/arm/include/asm/arch-fsl-layerscape/soc.h
@@ -77,7 +77,7 @@ enum boot_src {
 enum boot_src get_boot_src(void);
 #endif
 #endif
-#define SVR_WO_E		0xFFFFFE
+#define SVR_WO_E		0xFFFFEE
 
 #define SVR_MAJ(svr)		(((svr) >> 4) & 0xf)
 #define SVR_MIN(svr)		(((svr) >> 0) & 0xf)
