PORTNAME=	emby-server
PORTVERSION=	4.6.2.0
PORTREVISION=	1
CATEGORIES=	multimedia
MASTER_SITES=	https://github.com/MediaBrowser/Emby.Releases/releases/download/${PORTVERSION}/ \
		https://mediabrowser.github.io/embytools/
DISTNAME=	embyserver-netframework_${PORTVERSION}
DISTFILES=	${DISTNAME}.zip \
		ffdetect-${FFVERSION}-x64_freebsd12.tar.xz \
		ffmpeg-${FFVERSION}.tar.gz \
		license.docx
DIST_SUBDIR=	${PORTNAME}
EXTRACT_ONLY=	${DISTNAME}.zip \
		ffdetect-${FFVERSION}-x64_freebsd12.tar.xz \
		ffmpeg-${FFVERSION}.tar.gz

MAINTAINER=	driesm.michiels@gmail.com
COMMENT=	Media server to organize, play & stream audio/video to various devices

LICENSE=	UNKNOWN
LICENSE_NAME=	custom
LICENSE_FILE=	${DISTDIR}/${DIST_SUBDIR}/license.docx
LICENSE_PERMS=	dist-mirror no-dist-sell pkg-mirror no-pkg-sell auto-accept

ONLY_FOR_ARCHS=	amd64

BUILD_DEPENDS=	nasm:devel/nasm
LIB_DEPENDS=	libass.so:multimedia/libass \
		libdrm.so:graphics/libdrm \
		libfontconfig.so:x11-fonts/fontconfig \
		libfreetype.so:print/freetype2 \
		libfribidi.so:converters/fribidi \
		libgnutls.so:security/gnutls \
		libmfx.so:multimedia/intel-media-sdk \
		libogg.so:audio/libogg \
		libopus.so:audio/opus \
		libpng.so:graphics/png \
		libraw.so:graphics/libraw \
		libtheora.so:multimedia/libtheora \
		libva.so:multimedia/libva \
		libvorbis.so:audio/libvorbis \
		libvpx.so:multimedia/libvpx \
		libwebp.so:graphics/webp \
		libx264.so:multimedia/libx264 \
		libx265.so:multimedia/x265 \
		libzvbi.so:devel/libzvbi

USES=		compiler:c11 gmake iconv localbase:ldflags mono pkgconfig sqlite
USE_RC_SUBR=	${PORTNAME}

HAS_CONFIGURE=	yes
CONFIGURE_ARGS=	--cc="${CC}" \
		--disable-alsa \
		--disable-doc \
		--disable-ffplay \
		--disable-libxcb \
		--disable-outdev=xv \
		--disable-sdl2 \
		--disable-shared \
		--disable-sndio \
		--disable-v4l2-m2m \
		--disable-vdpau \
		--disable-xlib \
		--enable-fontconfig \
		--enable-gnutls \
		--enable-gpl \
		--enable-iconv \
		--enable-libass \
		--enable-libdrm \
		--enable-libfreetype \
		--enable-libfribidi \
		--enable-libmfx \
		--enable-libopus \
		--enable-libtheora \
		--enable-libvorbis \
		--enable-libvpx \
		--enable-libwebp \
		--enable-libx264 \
		--enable-libx265 \
		--enable-libzvbi \
		--enable-optimizations \
		--enable-static \
		--enable-vaapi \
		--enable-version3

MAKE_ENV=	V=1

NOPRECIOUSMAKEVARS=	yes
SUB_FILES=	ImageMagickSharp.dll.config \
		SQLitePCLRaw.provider.sqlite3.dll.config
SUB_LIST=	GROUP=${GROUPS} \
		PORTNAME=${PORTNAME} \
		RC_NAME=emby_server \
		USER=${USERS}

WRKSRC=		${WRKDIR}/ffmpeg-${FFVERSION}_public

USERS=		emby
GROUPS=		emby

OPTIONS_DEFINE=		LAME SMB X11
OPTIONS_DEFAULT=	LAME SMB X11

LAME_LIB_DEPENDS=	libmp3lame.so:audio/lame
LAME_CONFIGURE_ENABLE=	libmp3lame

SMB_USES=		samba:lib
SMB_CONFIGURE_ENABLE=	libsmbclient

X11_LIB_DEPENDS=	libMagickWand-6.so:graphics/ImageMagick6
X11_LIB_DEPENDS_OFF=	libMagickWand-6.so:graphics/ImageMagick6-nox11
X11_USES=		xorg
X11_USE=		xorg=x11

FFVERSION=	2020_05_23

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/emby-server/system
	(${INSTALL_DATA} ${WRKDIR}/ImageMagickSharp.dll.config ${STAGEDIR}${PREFIX}/lib/emby-server/system)
	(${INSTALL_DATA} ${WRKDIR}/SQLitePCLRaw.provider.sqlite3.dll.config ${STAGEDIR}${PREFIX}/lib/emby-server/system)
	(cd ${WRKDIR}/system && ${COPYTREE_SHARE} . ${STAGEDIR}${PREFIX}/lib/emby-server/system)
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/emby-server/bin
	(${INSTALL_PROGRAM} ${WRKDIR}/bin/ffdetect ${STAGEDIR}${PREFIX}/lib/emby-server/bin)
	(${INSTALL_PROGRAM} ${WRKSRC}/ffmpeg ${STAGEDIR}${PREFIX}/lib/emby-server/bin)
	(${INSTALL_PROGRAM} ${WRKSRC}/ffprobe ${STAGEDIR}${PREFIX}/lib/emby-server/bin)

.include <bsd.port.mk>
