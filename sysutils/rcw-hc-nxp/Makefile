# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	rcw
PORTVERSION=	20.12
CATEGORIES=	sysutils

MAINTAINER=	dsl@mcusim.org
COMMENT=	Hardware boot-time parameters for the SolidRun HoneyComb LX2

LICENSE=	BSD3CLAUSE

PKGNAMESUFFIX?=	-hc-nxp

BUILD_DEPENDS+=	as:devel/binutils

USES=		gmake shebangfix python:3.7+,build
USE_GCC=	yes:build
BINARY_ALIAS=	gcc=${LOCALBASE}/bin/gcc${GCC_DEFAULT} \
		python3=${PYTHON_CMD} python=${PYTHON_CMD}

RCW_DIR=	share/rcw/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${RCW_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	RCW_VERSION=${PORTVERSION}

NO_ARCH=	yes

BOARD=		lx2160acex7

# RCW repository (from Layerscape SDK)
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/rcw/snapshot/
DISTNAME=	bd6675518e6cb22f731c53407cc0631aa240f49f

# Configuration variables
DDR_SPEED?=	3200 # 1600 MHz clock
SERDES_1?=	8
SERDES_2?=	5
SERDES_3?=	2

PLIST_FILES+=	${RCW_DIR}/${BOARD}.rcw \
		${RCW_DIR}/${BOARD}.bin \
		${RCW_DIR}/README

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
	${MKDIR} ${WRKSRC}/${BOARD}/RCW
	echo "#include <configs/lx2160a_defaults.rcwi>" > ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_2000_700_${DDR_SPEED}.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_SD1_${SERDES_1}.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_SD2_${SERDES_2}.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw
	echo "#include <configs/lx2160a_SD3_${SERDES_3}.rcwi>" >> ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw

do-install:
	${MKDIR} ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/${BOARD}/RCW/${BOARD}.rcw ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/${BOARD}/RCW/${BOARD}.bin ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${DESCR} ${STAGEDIR}/${INST}/README

.include <bsd.port.mk>
