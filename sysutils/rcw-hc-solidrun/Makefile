# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	rcw
DISTVERSION=	g20210313
CATEGORIES=	sysutils

MAINTAINER=	dsl@mcusim.org
COMMENT=	Hardware boot-time parameters for SolidRun HoneyComb LX2

LICENSE=	BSD3CLAUSE

PKGNAMESUFFIX?=	-hc-solidrun

USES=		gmake shebangfix python:3.7+,build tcl:4.5+,build
USE_GCC=	yes:build

BUILD_DEPENDS+=	as:devel/binutils isc-envsubst:devel/envsubst

BINARY_ALIAS=	gcc=${LOCALBASE}/bin/gcc${GCC_DEFAULT} \
		tclsh=${LOCALBASE}/bin/tclsh${TCLTK_DEFAULT} \
		python3=${PYTHON_CMD} python=${PYTHON_CMD}

RCW_DIR=	share/rcw/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${RCW_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	RCW_VERSION=${DISTVERSION}

NO_ARCH=	yes

BOARD=		lx2160acex7

# SolidRun's fork of RCW (from Layerscape SDK)
USE_GITHUB=	yes
GH_ACCOUNT=	SolidRun
GH_TAGNAME=	bf3f2f45

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

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
