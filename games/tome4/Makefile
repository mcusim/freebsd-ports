PORTNAME=	tome4
DISTVERSION?=	1.7.3
PORTREVISION?=	0
CATEGORIES=	games
MASTER_SITES=	https://te4.org/dl/t-engine/ \
		SF/lifanov-ports-distfiles/${PORTNAME}/:icons
DISTFILES=	t-engine4-src-${DISTVERSION}${EXTRACT_SUFX} \
		${PORTNAME}.png:icons
EXTRACT_ONLY=	t-engine4-src-${DISTVERSION}${EXTRACT_SUFX}

MAINTAINER=	pkubaj@FreeBSD.org
COMMENT=	Epic tactical turn-based roguelike adventure

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	premake4:devel/premake4
LIB_DEPENDS=	libvorbisfile.so:audio/libvorbis \
		libpng.so:graphics/png

USES=		gl gmake openal:al sdl tar:bzip2 xorg
USE_SDL=	image2 sdl2 ttf2
USE_GL=		gl glu
SUB_FILES=	tome4

MAKE_JOBS_UNSAFE=	yes

DESKTOP_ENTRIES="ToME 4" "" "${PORTNAME}" \
		"${PORTNAME}" "Game;RolePlaying;" ""

PLIST_SUB=	PORTVERSION=${PORTVERSION}
WRKSRC=		${WRKDIR}/t-engine4-src-${DISTVERSION}
MAKE_ARGS+=	config=release verbose=yes ARCH="" CC=${CC} CXX=${CXX}
LDFLAGS_i386=	-Wl,-znotext

.include <bsd.port.options.mk>

.if ${ARCH} == powerpc
USES+=		compiler:gcc-c++11-lib
.else
USES+=		compiler:c++11-lang
.endif

pre-build:
	@${REINPLACE_CMD} 's|%%LOCALBASE%%|${LOCALBASE}|' ${WRKSRC}/premake4.lua
.if ${ARCH} == aarch64 || ${ARCH:Mpowerpc64*} || ${ARCH} == riscv64
	(cd ${WRKSRC} && premake4 --lua=default gmake)
.else
	(cd ${WRKSRC} && premake4 gmake)
	@${ECHO} '.NOTPARALLEL:' >> ${WRKSRC}/build/buildvm.make
	@${ECHO} '.NOTPARALLEL:' >> ${WRKSRC}/build/luajit2.make
.endif
	@${REINPLACE_CMD} 's|-lpthread|-pthread|' ${WRKSRC}/build/TEngine.make

do-install:
	@${MKDIR} ${STAGEDIR}${DATADIR}
	${INSTALL_PROGRAM} ${WRKSRC}/t-engine ${STAGEDIR}${DATADIR}
	${INSTALL_SCRIPT} ${WRKDIR}/tome4 ${STAGEDIR}${PREFIX}/bin
	(cd ${WRKSRC}; ${COPYTREE_SHARE} "bootstrap game" ${STAGEDIR}${DATADIR})
	${INSTALL_DATA} ${_DISTDIR}/${PORTNAME}.png \
		${STAGEDIR}${PREFIX}/share/pixmaps

.include <bsd.port.mk>
