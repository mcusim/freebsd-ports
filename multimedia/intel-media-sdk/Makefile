PORTNAME=	intel-media-sdk
DISTVERSIONPREFIX=	intel-mediasdk-
DISTVERSION=	21.2.2
CATEGORIES=	multimedia

MAINTAINER=	jbeich@FreeBSD.org
COMMENT=	Hardware video decoding/encoding/filtering on Intel GPUs

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386
ONLY_FOR_ARCHS_REASON=	Only Intel GPUs on x86 are supported

LIB_DEPENDS=	libva.so:multimedia/libva
RUN_DEPENDS=	cmrtlib>0:multimedia/cmrtlib
TEST_DEPENDS=	googletest>0:devel/googletest

USES=		cmake:testing compiler:c++11-lib localbase:ldflags pkgconfig
USE_GITHUB=	yes
USE_LDCONFIG=	yes
GH_ACCOUNT=	Intel-Media-SDK
GH_PROJECT=	MediaSDK
CMAKE_ON=	BUILD_TOOLS
CMAKE_TESTING_ON=	BUILD_TESTS USE_SYSTEM_GTEST
PLIST_SUB=	ARCH_SUFX=${ARCH:S/i386/32/:S/amd//:S/x86_//}
# https://github.com/Intel-Media-SDK/MediaSDK/issues/1844
LLD_UNSAFE=	yes

OPTIONS_DEFINE=	OPENCL WAYLAND X11
OPTIONS_DEFAULT=OPENCL WAYLAND X11
OPTIONS_SUB=	yes

OPENCL_BUILD_DEPENDS=	${LOCALBASE}/include/CL/opencl.h:devel/opencl
OPENCL_LIB_DEPENDS=	libOpenCL.so:devel/ocl-icd
OPENCL_CMAKE_BOOL=	ENABLE_OPENCL

X11_BUILD_DEPENDS=	${LOCALBASE}/include/xcb/dri3.h:x11/libxcb
X11_LIB_DEPENDS=	libva-x11.so:multimedia/libva
X11_CMAKE_BOOL=		ENABLE_X11 ENABLE_X11_DRI3

WAYLAND_LIB_DEPENDS=	libdrm_intel.so:graphics/libdrm \
			libwayland-client.so:graphics/wayland
WAYLAND_CMAKE_BOOL=	ENABLE_WAYLAND

post-patch:
# Pick git commit from port and use reproducible time
	@${REINPLACE_CMD} -e "/COMMAND/s/date/& -r `${AWK} '/TIMESTAMP/ \
			{ print \$$3 }' ${DISTINFO_FILE}`/" \
		-e '/set( *git_commit/s/"[^"]*"/"${DISTVERSIONFULL}"/' \
		${WRKSRC}/builder/FindFunctions.cmake \
		${WRKSRC}/builder/FindGlobals.cmake
# Don't assume GCC and glibc libraries are available
	@${REINPLACE_CMD} -e 's/ -lstdc++ -ldl//' \
		${WRKSRC}/api/mfx_dispatch/linux/pkg-config*.cmake

.include <bsd.port.mk>
