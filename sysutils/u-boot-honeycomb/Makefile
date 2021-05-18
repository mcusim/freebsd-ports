# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	u-boot
PORTVERSION=	20.12
CATEGORIES=	sysutils
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/u-boot/snapshot/
PKGNAMESUFFIX?=	-${MODEL}
DISTNAME=	f46a944f715f284aff1d42c009680ffe0be4058f

MAINTAINER=	dsl@mcusim.org
COMMENT=	Cross-build das u-boot for model HoneyComb LX2

LICENSE=	GPLv2

BUILD_DEPENDS+=	makeinfo:print/texinfo \
		gsed:textproc/gsed \
		swig:devel/swig \
		dtc>=1.4.1:sysutils/dtc \
		${PYTHON_PKGNAMEPREFIX}setuptools-pkg>=0:devel/py-setuptools-pkg@${PY_FLAVOR}
BUILD_DEPENDS+=	${COMPILER}:devel/${COMPILER}
LIB_DEPENDS+=	libgmp.so:math/gmp

USES=		bison gmake python:3.7+,build shebangfix
BINARY_ALIAS=	bison=${LOCALBASE}/bin/bison dtc=${LOCALBASE}/bin/dtc sed=gsed python3=${PYTHON_CMD}

SHEBANG_FILES=	tools/binman/binman
SSP_UNSAFE=	yes
UBOOT_DIR=	share/u-boot/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${UBOOT_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	V=1 CROSS_COMPILE=${CROSS_COMPILE} PYTHON=${PYTHON_CMD} ${ARCHFLAGS}

NO_ARCH=	yes

CROSS_COMPILE=	aarch64-none-elf-
ARCHFLAGS=	ARCH=arm
COMPILER?=	${CROSS_COMPILE}gcc

MODEL=		honeycomb
BOARD_CONFIG=	lx2160acex7_tfa_defconfig

do-configure:
	(cd ${WRKSRC}; ${SETENV} ${CONFIGURE_ENV} ${MAKE_CMD} ${BOARD_CONFIG})

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
