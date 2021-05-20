--- plat/nxp/soc-lx2160/aarch64/lx2160.S.orig	2021-05-20 15:52:23 UTC
+++ plat/nxp/soc-lx2160/aarch64/lx2160.S
@@ -668,6 +668,10 @@ _soc_sys_off:
       * spurious timeout reset request
       * workaround: MASK RESET REQ RPTOE
       */
+    mov x3, #NXP_GPIO3_ADDR
+    mov w1, #0x01000000
+    str w1, [x3]
+
     ldr  x0, =NXP_RESET_ADDR
     ldr  w1, =RSTRQMR_RPTOE_MASK
     str  w1, [x0, #RST_RSTRQMR1_OFFSET]
