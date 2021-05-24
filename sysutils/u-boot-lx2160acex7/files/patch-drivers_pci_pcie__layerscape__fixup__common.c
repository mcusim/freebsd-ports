--- drivers/pci/pcie_layerscape_fixup_common.c.orig	2021-05-12 16:46:41 UTC
+++ drivers/pci/pcie_layerscape_fixup_common.c
@@ -18,8 +18,9 @@ void ft_pci_setup(void *blob, bd_t *bd)
 	uint svr;
 
 	svr = SVR_SOC_VER(get_svr());
-
-	if (svr == SVR_LX2160A && IS_SVR_REV(get_svr(), 1, 0))
+	/* Rev 1 LX2160A have svr = 0x873610 */
+	if ((svr == SVR_LX2160A || svr == (SVR_LX2160A | 0x10)) &&
+	    IS_SVR_REV(get_svr(), 1, 0))
 		ft_pci_setup_ls_gen4(blob, bd);
 	else
 #endif /* CONFIG_PCIE_LAYERSCAPE_GEN4 */
