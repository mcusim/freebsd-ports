PORTNAME=	stress-ng
DISTVERSION=	0.12.10
PORTREVISION=	0
CATEGORIES=	benchmarks
MASTER_SITES=	http://kernel.ubuntu.com/~cking/tarballs/stress-ng/

MAINTAINER=	pizzamig@FreeBSD.org
COMMENT=	Stress test benchmarks

LICENSE=	GPLv2+
LICENSE_FILE=	${WRKSRC}/COPYING

BROKEN_aarch64=	Fails to link: missing sbrk

USES=		compiler:c11 gmake tar:xz

ALL_TARGET=	# empty

PLIST_FILES=	bin/stress-ng man/man1/stress-ng.1.gz

OPTIONS_DEFINE=	LIBINOTIFY
OPTIONS_DEFAULT=	LIBINOTIFY
LIBINOTIFY_DESC=	Install the kevent based libinotify to enable its stress

LIBINOTIFY_CFLAGS	+=	-I${LOCALBASE}/include
LIBINOTIFY_LDFLAGS	+=	-L${LOCALBASE}/lib -linotify
LIBINOTIFY_LIB_DEPENDS=	libinotify.so:devel/libinotify

post-patch:
	${REINPLACE_CMD} -e \
		's/int main(void)/int main(void) __attributes__((noinline))/' \
		${WRKSRC}/stress-atomic.c

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/stress-ng ${STAGEDIR}${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/stress-ng.1 ${STAGEDIR}${MAN1PREFIX}/man/man1

.include <bsd.port.mk>
