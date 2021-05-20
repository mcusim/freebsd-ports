--- plat/nxp/common/ls_io_storage.c.orig	2021-05-20 15:52:06 UTC
+++ plat/nxp/common/ls_io_storage.c
@@ -450,6 +450,12 @@ int plat_get_image_source(unsigned int image_id, uintp
 	int result;
 	const struct plat_io_policy *policy;
 
+	if ((image_id >= FUSE_FIP_IMAGE_ID) && (image_id <= FUSE_UP_IMAGE_ID)) {
+		NOTICE("Trying FUSE IO FIRST\n");
+		result = plat_get_fuse_image_source(image_id, dev_handle,
+						       image_spec);
+		return result;
+	}
 	if (image_id < ARRAY_SIZE(policies)) {
 
 		policy = &policies[image_id];
@@ -461,12 +467,6 @@ int plat_get_image_source(unsigned int image_id, uintp
 	} else {
 		VERBOSE("Trying alternative IO\n");
 		result = plat_get_alt_image_source(image_id, dev_handle,
-						       image_spec);
-	}
-
-	if (result != 0) {
-		VERBOSE("Trying FUSE IO\n");
-		result = plat_get_fuse_image_source(image_id, dev_handle,
 						       image_spec);
 	}
 
