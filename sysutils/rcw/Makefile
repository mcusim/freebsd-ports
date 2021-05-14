# Created by: Dmitry Salychev <dsl@mcusim.org>
# $FreeBSD$

PORTNAME=	qoriq-rcw
PORTVERSION=	20.12
CATEGORIES=	sysutils
RCW_COMMIT=	bd6675518e6cb22f731c53407cc0631aa240f49f
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/rcw/snapshot
DISTNAME=	${RCW_COMMIT}

MAINTAINER=	dsl@mcusim.org
COMMENT=	Reset Configuration Word - hardware boot-time parameters for the QorIQ targets.

LICENSE=	BSD3CLAUSE

DESCR?=		${.CURDIR}/pkg-descr

do-configure:
	${MKDIR} -p ${WRKSCR}/lx2160acex7/RCW
	echo "#include <configs/lx2160a_defaults.rcwi>" > ${WRKSCR}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_3200.rcwi>" >> ${WRKSCR}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD1_8.rcwi>" >> ${WRKSCR}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD2_5.rcwi>" >> ${WRKSCR}/lx2160acex7/RCW/template.rcw
	echo "#include <configs/lx2160a_SD3_2.rcwi>" >> ${WRKSCR}/lx2160acex7/RCW/template.rcw

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
