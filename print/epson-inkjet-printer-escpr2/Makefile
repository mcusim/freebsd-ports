PORTNAME=	epson-inkjet-printer-escpr2
DISTVERSION=	1.1.33
DISTVERSIONSUFFIX=	-1lsb3.2
CATEGORIES=	print
MASTER_SITES=	https://download3.ebz.epson.net/dsc/f/03/00/12/70/17/20c6da0381ea4966200302d61fc42b0acaea4040/:i386 \
		https://download3.ebz.epson.net/dsc/f/03/00/12/70/17/379e828e9552ca4dc49c7cfcc3c665bd4da1336c/:amd64 \
		https://download3.ebz.epson.net/dsc/f/03/00/12/70/17/b157323e14b6199f708c120307ef3ebe0e11231f/:SOURCE
EXTRACT_SUFX=	.rpm
DISTFILES_amd64=	${DISTNAME}.x86_64${EXTRACT_SUFX}:amd64
DISTFILES_i386=	${DISTNAME}.i486${EXTRACT_SUFX}:i386
EXTRACT_ONLY=	${_DISTFILES}

MAINTAINER=	tatsuki_makino@hotmail.com
COMMENT=	Epson Inkjet Printer Driver 2 (ESC/P-R) for Linux

LICENSE=	EPSON LGPL21
LICENSE_COMB=	multi
LICENSE_NAME_EPSON=	SEIKO EPSON CORPORATION SOFTWARE LICENSE AGREEMENT
LICENSE_FILE_EPSON=	${WRKSRC}/${PKGNAME}/COPYING.EPSON
LICENSE_FILE_LGPL21=	${WRKSRC}/${PKGNAME}/COPYING.LIB
LICENSE_PERMS_EPSON=	no-dist-mirror no-dist-sell no-pkg-mirror no-pkg-sell
LICENSE_DISTFILES_EPSON=	${DISTNAME}.i486${EXTRACT_SUFX} \
				${DISTNAME}.x86_64${EXTRACT_SUFX} \
				${DISTNAME}.src${EXTRACT_SUFX}
LEGAL_TEXT=	License does not permit public sharing and revenue earning, and restricts exports

RUN_DEPENDS=	${LOCALBASE}/libexec/cups/filter/gstoraster:print/cups-filters \
		cupsfilter:print/cups

USES=		linux
USE_LINUX=	cups-libs
PLIST_SUB=	LINUXBASE=${LINUXBASE}
NO_WRKSUBDIR=	yes
NO_BUILD=	yes
SRC_DISTFILES=	${DISTNAME}.src${EXTRACT_SUFX}:SOURCE
# PORTSCOUT=ignore:1 MASTER_SITES is changed in each version
PORTSCOUT=	ignore:1

.include <bsd.port.options.mk>

.if ${ARCH} == amd64
PLIST_SUB+=	ARCH_AMD64=""
PLIST_SUB+=	ARCH_I386="@comment "
.elif ${ARCH} == i386
PLIST_SUB+=	ARCH_AMD64="@comment "
PLIST_SUB+=	ARCH_I386=""
.endif

post-extract:
	(cd ${EXTRACT_WRKDIR} && \
		${EXTRACT_CMD} ${EXTRACT_BEFORE_ARGS} ${DISTNAME}.tar.gz \
		${EXTRACT_AFTER_ARGS} -- ${PKGNAME}/COPYING.\*)
	${FIND} -- ${WRKSRC}/opt/${PORTNAME}/ppds/Epson -iname \*.ppd.gz \
		-exec ${GUNZIP_CMD} -- {} +

post-patch:
	${FIND} -- ${WRKSRC}/opt/${PORTNAME}/ppds/Epson -iname \*.ppd \
		-exec ${SED} -i '' -e '/^\*cupsFilter:/s,/opt/${PORTNAME}/,${LINUXBASE}&,' -- {} \; \
		-exec ${GZIP_CMD} -- {} \;

do-install:
	(cd ${WRKSRC} && \
		${FIND} opt | ${CPIO} -dumpl --quiet ${STAGEDIR}${LINUXBASE})
	${MKDIR} ${STAGEDIR}${PREFIX}/share/cups/model
	${LN} -s -f ${LINUXBASE}/opt/${PORTNAME}/ppds/Epson \
		${STAGEDIR}${PREFIX}/share/cups/model/${PORTNAME}

.include <bsd.port.mk>
