# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	mc-utils
PORTVERSION=	${LSDK_VERSION}
CATEGORIES=	sysutils
MASTER_SITES=	${LSDK_SITES}
PKGNAMESUFFIX?=	-${PLAT}
DISTNAME=	${LSDK_COMMIT}

MAINTAINER=	dsl@mcusim.org
COMMENT=	Management Complex utilities for platform ${PLAT}

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+= git:devel/git

USES=		gmake

SSP_UNSAFE=	yes
MCUTILS_DIR=	share/mc-utils/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${MCUTILS_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	-C config/

PLAT=		lx2160acex7

# NXP's Layerscape SDK version
LSDK_VERSION?=	20.12
LSDK_COMMIT?=	8e0b863693fc2ccbc62a62c79b4e3db6da88c16e
LSDK_SITES?=	https://source.codeaurora.org/external/qoriq/qoriq-components/mc-utils/snapshot/
MC_BINARY_SITE?=https://github.com/NXP/qoriq-mc-binary.git

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
	(cd ${WRKSRC}; git clone ${MC_BINARY_SITE})

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
