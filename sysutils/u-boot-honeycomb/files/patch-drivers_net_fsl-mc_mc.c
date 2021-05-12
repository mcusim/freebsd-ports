--- drivers/net/fsl-mc/mc.c.orig	2021-05-12 16:46:31 UTC
+++ drivers/net/fsl-mc/mc.c
@@ -929,7 +929,7 @@ unsigned long mc_get_dram_block_size(void)
 	return dram_block_size;
 }
 
-int fsl_mc_ldpaa_init(bd_t *bis)
+__weak int fsl_mc_ldpaa_init(bd_t *bis)
 {
 	int i;
 
