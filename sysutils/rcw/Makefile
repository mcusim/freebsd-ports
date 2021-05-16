# Created by: Dmitry Salychev <dsl@mcusim.org>
# $FreeBSD$

PORTNAME=	rcw
PORTVERSION=	20.12
CATEGORIES=	sysutils
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/rcw/snapshot/
DISTNAME=	bd6675518e6cb22f731c53407cc0631aa240f49f

MAINTAINER=	dsl@mcusim.org
COMMENT=	Hardware boot-time parameters for the QorIQ targets

LICENSE=	BSD3CLAUSE

BUILD_DEPENDS+=	gcc:lang/gcc \
		as:devel/binutils

USES=		gmake python:3.7+,build shebangfix
BINARY_ALIAS=	python3=${PYTHON_CMD}

DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	RCW_VERSION=${PORTVERSION}

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
	${MKDIR} ${WRKSRC}/lx2160acex7/RCW
	echo "#include <configs/lx2160a_defaults.rcwi>" > ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_2000_700_3200.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD1_8.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD2_5.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD3_2.rcwi>" >> ${WRKSRC}/lx2160acex7/RCW/template.rcw

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
