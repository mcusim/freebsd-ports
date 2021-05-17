# Created by: Dmitry Salychev <dsl@mcusim.org>
# $FreeBSD$

PORTNAME=	rcw
PORTVERSION=	20.12 # Layerscape SDK version
CATEGORIES=	sysutils
PKGNAMESUFFIX?=	-${BOARD}
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/rcw/snapshot/
DISTNAME=	bd6675518e6cb22f731c53407cc0631aa240f49f

BOARD=		lx2160acex7

MAINTAINER=	dsl@mcusim.org
COMMENT=	Hardware boot-time parameters for the SolidRun HoneyComb LX2

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+=	gcc:lang/gcc \
		as:devel/binutils

USES=		gmake python:3.7+,build shebangfix
BINARY_ALIAS=	python3=${PYTHON_CMD}

DESCR?=		${.CURDIR}/pkg-descr

NO_ARCH=	yes

MAKE_ARGS+=	RCW_VERSION=${PORTVERSION}

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
	${MKDIR} ${WRKSRC}/${MODEL}/RCW
	echo "#include <configs/lx2160a_defaults.rcwi>" > ${WRKSRC}/${MODEL}/RCW/${MODEL}.rcw
	echo "#include <configs/lx2160a_2000_700_3200.rcwi>" >> ${WRKSRC}/${MODEL}/RCW/${MODEL}.rcw
	echo "#include <configs/lx2160a_SD1_8.rcwi>" >> ${WRKSRC}/${MODEL}/RCW/${MODEL}.rcw
	echo "#include <configs/lx2160a_SD2_5.rcwi>" >> ${WRKSRC}/${MODEL}/RCW/${MODEL}.rcw
	echo "#include <configs/lx2160a_SD3_2.rcwi>" >> ${WRKSRC}/${MODEL}/RCW/${MODEL}.rcw

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${BOARD}/
	${INSTALL_DATA} ${WRKSRC}/${MODEL}/RCW/${MODEL}.rcw ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${BOARD}/
	${INSTALL_DATA} ${DESCR} ${STAGEDIR}/${INST}/README

.include <bsd.port.mk>
