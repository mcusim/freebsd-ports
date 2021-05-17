PORTNAME=	rcw
PORTVERSION=	20.12 # Layerscape SDK version
CATEGORIES=	sysutils
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/rcw/snapshot/
PKGNAMESUFFIX?=	-${BOARD}
DISTNAME=	bd6675518e6cb22f731c53407cc0631aa240f49f

MAINTAINER=	dsl@mcusim.org
COMMENT=	Hardware boot-time parameters for the SolidRun HoneyComb LX2

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+=	as:devel/binutils

USES=		gmake python:3.7+,build shebangfix
USE_GCC=	yes:build+
BINARY_ALIAS=	python3=${PYTHON_CMD} gcc=gcc${GCC_DEFAULT}

DESCR?=		${.CURDIR}/pkg-descr

NO_ARCH=	yes

MAKE_ARGS+=	RCW_VERSION=${PORTVERSION}

BOARD=		lx2160acex7

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
	${MKDIR} ${WRKSRC}/${BOARD}/RCW
	echo "#include <configs/lx2160a_defaults.rcwi>" > ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_2000_700_3200.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_SD1_8.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_SD2_5.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_SD3_2.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${BOARD}/
	${INSTALL_DATA} ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${BOARD}/
	${INSTALL_DATA} ${DESCR} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${BOARD}/README

.include <bsd.port.mk>
