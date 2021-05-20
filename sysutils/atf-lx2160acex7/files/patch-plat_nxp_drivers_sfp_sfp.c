--- plat/nxp/drivers/sfp/sfp.c.orig	2021-05-20 15:52:15 UTC
+++ plat/nxp/drivers/sfp/sfp.c
@@ -56,9 +56,10 @@ static int set_gpio_bitnum(uint8_t * gpio_base_addr, u
 
 	val = sfp_read32(gpdat);
 
+#if 0 /* Reading from GPIO is not functional without enabling the input buffer (register 0x18). For now ignore it */
 	if (!(val & bit_num))
 		return ERROR_GPIO_SET_FAIL;
-
+#endif
        /*
 	* Add delay so that Efuse gets the power when GPIO is enabled.
 	*/
@@ -93,9 +94,10 @@ static int reset_gpio_bitnum(uint8_t * gpio_base_addr,
 
 	val = sfp_read32(gpdat);
 
+#if 0
 	if (val & bit_num)
 		return ERROR_GPIO_RESET_FAIL;
-
+#endif
 	return 0;
 }
 
@@ -433,46 +435,6 @@ int provision_fuses(unsigned long long fuse_scr_addr)
 	if (memcmp(fuse_hdr->barker, barker, sizeof(barker)))
 		return error_handler(ERROR_FUSE_BARKER);
 
-	 /* Check if GPIO pin to be set for POVDD */
-	if ((fuse_hdr->flags >> FLAG_POVDD_SHIFT) & 0x1) {
-		/*
-		 * Subtract 1 from fuse_hdr povdd_gpio value as
-		 * for 0x1 value, bit 0 is to be set
-		 * for 0x20 value i.e 32, bit 31 i.e. 0x1f is to be set.
-		 * 0x1f - 0x00 : GPIO_1
-		 * 0x3f - 0x20 : GPIO_2
-		 * 0x5f - 0x40 : GPIO_3
-		 * 0x7f - 0x60 : GPIO_4
-		 */
-		povdd_gpio_val = (fuse_hdr->povdd_gpio - 1) & GPIO_SEL_MASK;
-
-		/* Right shift by 5 to divide by 32 */
-		gpio_num = povdd_gpio_val >> 5;
-		bit_num = 1 << (31 - (povdd_gpio_val & GPIO_BIT_MASK));
-
-		switch (gpio_num) {
-			case 0:
-				gpio = (uint8_t *)NXP_GPIO1_ADDR;
-				break;
-			case 1:
-				gpio = (uint8_t *)NXP_GPIO2_ADDR;
-				break;
-			case 2:
-				gpio = (uint8_t *)NXP_GPIO3_ADDR;
-				break;
-			case 3:
-				gpio = (uint8_t *)NXP_GPIO4_ADDR;
-				break;
-			default:
-				ret = ERROR_POVDD_GPIO_FAIL;
-				return error_handler(ret);
-		}
-
-		ret = set_gpio_bitnum(gpio, bit_num);
-		if (ret != 0)
-			return error_handler(ret);
-	}
-
 	/*
 	 * Check for Write Protect (WP) fuse. If blown then do
 	 *  no fuse provisioning.
@@ -480,6 +442,9 @@ int provision_fuses(unsigned long long fuse_scr_addr)
 	if (sfp_read32(&sfp_ccsr_regs->ospr) & 0x1)
 		return 0;
 
+	/* Configure PPWM to match 800MHz platform clock */
+	sfp_write32((void *)SFP_SFPCR_ADDR, 0x960);
+
 	 /* Check if SRKH to be blown or not */
 	if ((fuse_hdr->flags >> FLAG_SRKH_SHIFT) & 0x1) {
 		INFO("Fuse: Program SRKH\n");
@@ -530,6 +495,48 @@ int provision_fuses(unsigned long long fuse_scr_addr)
 		if (ret != 0)
 			return error_handler(ret);
 	}
+
+	 /* Check if GPIO pin to be set for POVDD */
+	if ((fuse_hdr->flags >> FLAG_POVDD_SHIFT) & 0x1) {
+		/*
+		 * Subtract 1 from fuse_hdr povdd_gpio value as
+		 * for 0x1 value, bit 0 is to be set
+		 * for 0x20 value i.e 32, bit 31 i.e. 0x1f is to be set.
+		 * 0x1f - 0x00 : GPIO_1
+		 * 0x3f - 0x20 : GPIO_2
+		 * 0x5f - 0x40 : GPIO_3
+		 * 0x7f - 0x60 : GPIO_4
+		 */
+		NOTICE("POVDD_GPIO = %d\n",fuse_hdr->povdd_gpio);
+		povdd_gpio_val = (fuse_hdr->povdd_gpio - 1) & GPIO_SEL_MASK;
+
+		/* Right shift by 5 to divide by 32 */
+		gpio_num = povdd_gpio_val >> 5;
+		bit_num = 1 << (31 - (povdd_gpio_val & GPIO_BIT_MASK));
+
+		switch (gpio_num) {
+			case 0:
+				gpio = (uint8_t *)NXP_GPIO1_ADDR;
+				break;
+			case 1:
+				gpio = (uint8_t *)NXP_GPIO2_ADDR;
+				break;
+			case 2:
+				gpio = (uint8_t *)NXP_GPIO3_ADDR;
+				break;
+			case 3:
+				gpio = (uint8_t *)NXP_GPIO4_ADDR;
+				break;
+			default:
+				ret = ERROR_POVDD_GPIO_FAIL;
+				return error_handler(ret);
+		}
+
+		ret = set_gpio_bitnum(gpio, bit_num);
+		if (ret != 0)
+			return error_handler(ret);
+	}
+
 	 /* Program SFP fuses from mirror registers */
 	sfp_write32((void *)SFP_INGR_ADDR, SFP_INGR_PROGFB_CMD);
 
@@ -538,17 +545,17 @@ int provision_fuses(unsigned long long fuse_scr_addr)
 		ingr = sfp_read32(SFP_INGR_ADDR);
 	} while (ingr & SFP_INGR_PROGFB_CMD);
 
-	 /* Check for SFP fuse programming error */
-	sfp_cmd_status = sfp_read32(SFP_INGR_ADDR) & SFP_INGR_ERROR_MASK;
-	if (sfp_cmd_status != 0)
-		return error_handler(ERROR_PROGFB_CMD);
-
 	/* Reset the gpio pin set to enable povdd */
 	if ((fuse_hdr->flags >> FLAG_POVDD_SHIFT) & 0x1) {
 		ret = reset_gpio_bitnum(gpio, bit_num);
 		if (ret != 0)
 			return error_handler(ret);
 	}
+	 /* Check for SFP fuse programming error */
+	sfp_cmd_status = sfp_read32(SFP_INGR_ADDR) & SFP_INGR_ERROR_MASK;
+	if (sfp_cmd_status != 0)
+		return error_handler(ERROR_PROGFB_CMD);
+
 
 	return 0;
 }
