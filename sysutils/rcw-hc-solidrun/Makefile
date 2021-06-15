# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	rcw
DISTVERSION=	${RCW_VERSION}
USE_GITHUB=	yes
GH_ACCOUNT=	SolidRun
GH_PROJECT=	rcw
GH_TAGNAME=	${RCW_COMMIT}
CATEGORIES=	sysutils
PKGNAMESUFFIX?=	-hc-solidrun

MAINTAINER=	dsl@mcusim.org
COMMENT=	Hardware boot-time parameters for the SolidRun HoneyComb LX2

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+=	as:devel/binutils \
		isc-envsubst:devel/envsubst

USES=		gmake python:3.7+,build shebangfix
USE_GCC=	yes:build
BINARY_ALIAS=	python3=${PYTHON_CMD} gcc=gcc${GCC_DEFAULT}

RCW_DIR=	share/rcw/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${RCW_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	RCW_VERSION=${RCW_VERSION}

NO_ARCH=	yes

BOARD=		lx2160acex7

# SolidRun's fork of RCW from NXP's Layerscape SDK
RCW_VERSION?=	g20210313
RCW_COMMIT?=	bf3f2f45

# Configuration variables
DDR_SPEED?=	3200 # 1600 MHz clock
SERDES_1?=	8
SERDES_2?=	5
SERDES_3?=	2

PLIST_FILES+=	${RCW_DIR}/${BOARD}.rcw \
		${RCW_DIR}/${BOARD}.bin \
		${RCW_DIR}/README

do-configure:
	${MKDIR} ${WRKSRC}/${BOARD}/RCW

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
