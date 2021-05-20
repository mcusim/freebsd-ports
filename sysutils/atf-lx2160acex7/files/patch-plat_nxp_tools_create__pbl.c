--- plat/nxp/tools/create_pbl.c.orig	2021-05-20 15:52:41 UTC
+++ plat/nxp/tools/create_pbl.c
@@ -67,6 +67,7 @@ typedef enum {
 	FLXSPI_NOR_BOOT,
 	FLXSPI_NAND_BOOT,
 	FLXSPI_NAND4K_BOOT,
+	AUTO_BOOT,
 	MAX_BOOT    /* must be last item in list */
 } boot_src_t;
 
@@ -141,6 +142,7 @@ char *boot_src_string[] = {
 	"FLXSPI_NOR_BOOT",
 	"FLXSPI_NAND_BOOT",
 	"FLXSPI_NAND4K_BOOT",
+	"AUTODETECT"
 };
 
 enum stop_command {
@@ -194,7 +196,7 @@ struct pbl_image {
 #define SOC_LS2088 2088
 #define SOC_LX2160 2160
 
-static uint32_t pbl_size;
+static uint32_t pbl_size = 0;
 bool sb_flag = false;
 
 /***************************************************************************
@@ -503,7 +505,6 @@ int add_boot_ptr_cmd(FILE *fp_rcw_pbi_op)
 			goto bootptr_err;
 		}
 	}
-
 	printf("\nBoot Location Pointer= %x\n", BYTE_SWAP_32(pblimg.ep));
 	ret = SUCCESS;
 
@@ -697,6 +698,8 @@ int main(int argc, char **argv)
 	int ret = FAILURE;
 	bool bootptr_flag = false;
 	enum stop_command flag_stop_cmd = CRC_STOP_COMMAND;;
+	int skip = 0;
+	uint32_t saved_src;
 
 	/* Initializing the global structure to zero. */
 	memset(&pblimg, 0x0, sizeof(struct pbl_image));
@@ -797,6 +800,8 @@ int main(int argc, char **argv)
 				pblimg.boot_src = FLXSPI_NAND_BOOT;
 			else if (!strcmp(optarg, "flexspi_nand2k"))
 				pblimg.boot_src = FLXSPI_NAND4K_BOOT;
+			else if (!strcmp(optarg, "auto"))
+				pblimg.boot_src = AUTO_BOOT;
 			else {
 				printf("CMD Error: Invalid boot source.\n");
                 		goto exit_main;
@@ -902,13 +907,14 @@ int main(int argc, char **argv)
     			printf("%s: Error reading PBI Cmd.\n", __func__);
     			goto exit_main;
     		}
-    		while (word != 0x808f0000 && word != 0x80ff0000) {
+		saved_src = pblimg.src_addr;
+		while (word != 0x808f0000 && word != 0x80ff0000) {
     			pbl_size++;
 			/* 11th words in RCW has PBL length. Update it
 			 * with new length. 2 comamnds get added 
 			 * Block copy + CCSR Write/CSF header write 
 			 */	
-    			if (pbl_size == 11) {
+			if ((pbl_size == 11) && (pblimg.boot_src != AUTO_BOOT)) {
     				word_1 = (word & PBI_LEN_MASK)
     					+ (PBI_LEN_ADD << 20);
     				word = word & ~PBI_LEN_MASK;
@@ -923,8 +929,44 @@ int main(int argc, char **argv)
     					goto exit_main;
     				}
     			}
-    			if (fwrite(&word, sizeof(word),	NUM_MEM_BLOCK,
-    				fp_rcw_pbi_op) != NUM_MEM_BLOCK) {
+			if (pblimg.boot_src == AUTO_BOOT) {
+				if (word == 0x80000008) {
+					printf ("Found SD boot at %d\n",pbl_size);
+					pblimg.boot_src = SD_BOOT;
+					add_blk_cpy_cmd(fp_rcw_pbi_op, args);
+					pblimg.boot_src = AUTO_BOOT;
+					pblimg.src_addr = saved_src;
+					if (bootptr_flag == true) {
+						add_boot_ptr_cmd(fp_rcw_pbi_op);
+						skip = 6;
+					} else skip=4;
+				}
+				if (word == 0x80000009) {
+					printf ("Found eMMC boot at %d\n",pbl_size);
+					pblimg.boot_src = EMMC_BOOT;
+					add_blk_cpy_cmd(fp_rcw_pbi_op, args);
+					pblimg.boot_src = AUTO_BOOT;
+					pblimg.src_addr = saved_src;
+					if (bootptr_flag == true) {
+						add_boot_ptr_cmd(fp_rcw_pbi_op);
+						skip = 6;
+					} else skip=4;
+				}
+				if (word == 0x8000000f) {
+					printf ("Found SPI boot at %d\n",pbl_size);
+					pblimg.boot_src = FLXSPI_NOR_BOOT;
+					add_blk_cpy_cmd(fp_rcw_pbi_op, args);
+					pblimg.boot_src = AUTO_BOOT;
+					pblimg.src_addr = saved_src;
+					if (bootptr_flag == true) {
+						add_boot_ptr_cmd(fp_rcw_pbi_op);
+						skip = 6;
+					} else skip=4;
+				}
+			}
+			if (!skip &&
+				(fwrite(&word, sizeof(word),	NUM_MEM_BLOCK,
+					fp_rcw_pbi_op) != NUM_MEM_BLOCK)) {
     				printf("%s: [CH3] Error in Writing PBI Words\n",
     					__func__);
     				goto exit_main;
@@ -941,8 +983,9 @@ int main(int argc, char **argv)
 			} else if (word == STOP_CMD_ARM_CH3){
 				flag_stop_cmd = STOP_COMMAND;
 			}
+			if (skip) skip--;
     		}
-		if (bootptr_flag == true) {
+		if ((pblimg.boot_src != AUTO_BOOT) && (bootptr_flag == true)) {
     			/* Add command to set boot_loc ptr */
     			ret = add_boot_ptr_cmd(fp_rcw_pbi_op);
     			if (ret != SUCCESS) {
@@ -953,18 +996,19 @@ int main(int argc, char **argv)
 		}
 
     		/* Write acs write commands to output file */
-    		ret = add_blk_cpy_cmd(fp_rcw_pbi_op, args);
-    		if (ret != SUCCESS) {
-    			printf("%s: Function add_blk_cpy_cmd return failure.\n",
-    				 __func__);
-    			goto exit_main;
-    		}
-
+		if (pblimg.boot_src != AUTO_BOOT) {
+			ret = add_blk_cpy_cmd(fp_rcw_pbi_op, args);
+			if (ret != SUCCESS) {
+				printf("%s: Function add_blk_cpy_cmd return failure.\n",
+					 __func__);
+				goto exit_main;
+			}
+		}
 		/* Add stop command after adding pbi commands */
-	        ret = add_pbi_stop_cmd(fp_rcw_pbi_op, flag_stop_cmd);
-    		if (ret != SUCCESS) {
-    			goto exit_main;
-    		}
+		ret = add_pbi_stop_cmd(fp_rcw_pbi_op, flag_stop_cmd);
+		if (ret != SUCCESS) {
+			goto exit_main;
+		}
 
             break;
 
