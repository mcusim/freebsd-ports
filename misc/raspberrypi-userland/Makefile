# Created by: Mikael Urankar <mikael.urankar@gmail.com>

PORTNAME=	raspberrypi-userland
PORTVERSION=	20161026
CATEGORIES=	misc

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Various libraries for the Raspberry Pi

LICENSE=	BSD3CLAUSE

ONLY_FOR_ARCHS=	armv6 armv7

CONFLICTS_INSTALL=	libglvnd

USES=		cmake pkgconfig shebangfix

USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	gonzoua
GH_PROJECT=	userland
GH_TAGNAME=	e143b48

CMAKE_ARGS+=	-DVMCS_INSTALL_PREFIX=${PREFIX} \
		-DCMAKE_TOOLCHAIN_FILE=${WRKSRC}/makefiles/cmake/toolchains/arm-freebsd.cmake
SHEBANG_FILES=	host_applications/linux/apps/dtoverlay/dtoverlay-post \
		host_applications/linux/apps/dtoverlay/dtoverlay-pre

OPTIONS_DEFINE=	EXAMPLES DEBUG
EXAMPLES_DESC=	Install test applications source code (hello_pi)
EXAMPLES_LIB_DEPENDS=	libfreetype.so:print/freetype2

DEBUG_CFLAGS_OFF=	-DNDEBUG

LLD_UNSAFE=	yes

post-patch:
	@${REINPLACE_CMD} -e "s|/opt/vc|${PREFIX}|g" \
		${WRKSRC}/makefiles/cmake/vmcs.cmake \
		${WRKSRC}/host_applications/linux/apps/hello_pi/Makefile.include
	@${REINPLACE_CMD} -e "s|CMAKE_C_COMPILER cc|CMAKE_C_COMPILER ${CC}|g" \
		-e "s|CMAKE_CXX_COMPILER c++|CMAKE_C_COMPILER ${CXX}|g" \
		-e "s|CMAKE_ASM_COMPILER as|CMAKE_C_COMPILER ${CC}|g" \
		${WRKSRC}/makefiles/cmake/toolchains/arm-freebsd.cmake
# patches for hello_pi example
	@${REINPLACE_CMD} -e "s|make|gmake|g" \
		${WRKSRC}/host_applications/linux/apps/hello_pi/rebuild.sh
	@${REINPLACE_CMD} -e "s|gcc|cc|g" \
		${WRKSRC}/host_applications/linux/apps/hello_pi/hello_fft/makefile
	@${REINPLACE_CMD} -e "s|linux|sys|g" \
		${WRKSRC}/host_applications/linux/apps/hello_pi/hello_fft/mailbox.h
	@${REINPLACE_CMD} -e "s|LOCALBASE|${LOCALBASE}|g" \
		${WRKSRC}/host_applications/linux/apps/hello_pi/Makefile.include
.for file in hello_fft/gpu_fft.txt hello_teapot/triangle.c hello_teapot/video.c hello_videocube/video.c
	@${REINPLACE_CMD} -e "s|/opt/vc/src|${EXAMPLESDIR}|g" \
		${WRKSRC}/host_applications/linux/apps/hello_pi/${file}
.endfor

post-install-EXAMPLES-on:
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	@(cd ${WRKSRC}/host_applications/linux/apps/hello_pi && ${COPYTREE_SHARE} . ${STAGEDIR}${EXAMPLESDIR}/hello_pi)

.include <bsd.port.mk>
