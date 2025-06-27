--- drivers/gpu/drm/amd/display/dc/os_types.h.orig	2025-02-23 20:00:56.187429000 +0100
+++ drivers/gpu/drm/amd/display/dc/os_types.h	2025-02-23 20:02:07.147828000 +0100
@@ -48,20 +48,24 @@
 
 #define dm_output_to_console(fmt, ...) DRM_DEBUG_KMS(fmt, ##__VA_ARGS__)
 
 #define dm_error(fmt, ...) DRM_ERROR(fmt, ##__VA_ARGS__)
 
 #if defined(CONFIG_DRM_AMD_DC_DCN) || defined(__FreeBSD__)
 #if defined(CONFIG_X86)
 #include <asm/fpu/api.h>
 #define DC_FP_START() kernel_fpu_begin()
 #define DC_FP_END() kernel_fpu_end()
+#elif defined(CONFIG_ARM64)
+#include <asm/neon.h>
+#define DC_FP_START() kernel_neon_begin()
+#define DC_FP_END() kernel_neon_end()
 #elif defined(CONFIG_PPC64)
 #ifdef __linux__
 #include <asm/switch_to.h>
 #include <asm/cputable.h>
 #define DC_FP_START() { \
 	if (cpu_has_feature(CPU_FTR_VSX_COMP)) { \
 		preempt_disable(); \
 		enable_kernel_vsx(); \
 	} else if (cpu_has_feature(CPU_FTR_ALTIVEC_COMP)) { \
 		preempt_disable(); \
