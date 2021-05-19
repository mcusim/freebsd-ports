# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	atf
PORTVERSION=	${LSDK_VERSION}
CATEGORIES=	sysutils
MASTER_SITES=	${LSDK_SITES}
PKGNAMESUFFIX?=	-${PLAT}
DISTNAME=	${LSDK_COMMIT}

MAINTAINER=	dsl@mcusim.org
COMMENT=	ARM TF-A for platform ${PLAT}

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+=	${COMPILER}:devel/${COMPILER} \
		u-boot.bin:sysutils/u-boot-honeycomb \
		lx2160acex7.bin:sysutils/rcw-lx2160acex7

USES=		gmake

SSP_UNSAFE=	yes
ATF_DIR=	share/atf/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${ATF_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	V=1 CROSS_COMPILE=${CROSS_COMPILE} ${ARCHFLAGS}

NO_ARCH=	yes

CROSS_COMPILE=	aarch64-none-elf-
ARCHFLAGS=	ARCH=arm
COMPILER?=	${CROSS_COMPILE}gcc

PLAT=		lx2160acex7

# NXP's Layerscape SDK version
LSDK_VERSION?=	20.12
LSDK_COMMIT?=	9225ad51f026975fa6b86db800f43c55db11fa4d
LSDK_SITES?=	https://source.codeaurora.org/external/qoriq/qoriq-components/atf/snapshot/

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
#(cd ${WRKSRC}; ${SETENV} ${CONFIGURE_ENV} ${MAKE_CMD} ${BOARD_CONFIG})

do-install:
	${MKDIR} ${STAGEDIR}/${INST}
#${INSTALL_DATA} ${WRKSRC}/u-boot.bin ${STAGEDIR}/${INST}
#${INSTALL_DATA} ${DESCR} ${STAGEDIR}/${INST}/README

.include <bsd.port.mk>
