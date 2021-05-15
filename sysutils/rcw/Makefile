# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	qoriq-rcw
PORTVERSION=	20.12
CATEGORIES=	sysutils
RCW_COMMIT=	bd6675518e6cb22f731c53407cc0631aa240f49f
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/rcw/snapshot/
DISTNAME=	${RCW_COMMIT}

MAINTAINER=	dsl@mcusim.org
COMMENT=	Reset Configuration Word - hardware boot-time parameters for the QorIQ targets.

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+=	${COMPILER}:lang/${COMPILER}

USES=		gmake python:3.7+,build shebangfix
BINARY_ALIAS=	python3=${PYTHON_CMD}

DESCR?=		${.CURDIR}/pkg-descr

COMPILER?=gcc

do-configure:
	${MKDIR} ${WRKSRC}/lx2160acex7/RCW
	echo "#include <configs/lx2160a_defaults.rcwi>" > ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_3200.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD1_8.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD2_5.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD3_2.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
