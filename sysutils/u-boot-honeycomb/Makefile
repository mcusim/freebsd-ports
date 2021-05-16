# Created by: Dmitry Salychev <dsl@mcusim.org>
# $FreeBSD$

PORTNAME=	u-boot
PORTVERSION=	20.12
CATEGORIES=	sysutils
PKGNAMESUFFIX?=	-${MODEL}
MASTER_SITES=	https://source.codeaurora.org/external/qoriq/qoriq-components/u-boot/snapshot/
DISTNAME=	f46a944f715f284aff1d42c009680ffe0be4058f

MODEL=		honeycomb
BOARD_CONFIG=	lx2160acex7_tfa_defconfig
FAMILY=		aarch64

MAINTAINER=	dsl@mcusim.org
COMMENT=	Cross-build das u-boot for model HoneyComb LX2

LICENSE=	GPLv2

BUILD_DEPENDS+=	libgmp.so:math/gmp
		makeinfo:print/texinfo \
		gsed:textproc/gsed \
		swig:devel/swig \
		dtc>=1.4.1:sysutils/dtc \
		mkimage:sysutils/u-boot-tools \
		${PYTHON_PKGNAMEPREFIX}setuptools-pkg>=0:devel/py-setuptools-pkg@${PY_FLAVOR}
BUILD_DEPENDS+=	${COMPILER}:devel/${COMPILER}

USES=		bison gmake python:3.7+,build shebangfix
BINARY_ALIAS=	bison=${LOCALBASE}/bin/bison dtc=${LOCALBASE}/bin/dtc sed=gsed python3=${PYTHON_CMD}

SHEBANG_FILES=	tools/binman/binman arch/arm/mach-rockchip/make_fit_atf.py
SSP_UNSAFE=	yes
UBOOT_DIR=	share/u-boot/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${UBOOT_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ARGS+=	V=1 CROSS_COMPILE=${CROSS_COMPILE} PYTHON=${PYTHON_CMD} ${ARCHFLAGS}

NO_ARCH=	yes

UBOOT_ARCH=	aarch64
CROSS_COMPILE=	aarch64-none-elf-
ARCHFLAGS=	ARCH=arm

COMPILER?=${CROSS_COMPILE}gcc

do-configure:
	(cd ${WRKSRC}; ${SETENV} ${CONFIGURE_ENV} ${MAKE_CMD} ${BOARD_CONFIG})

do-install:
	${MKDIR} ${STAGEDIR}/${INST}

.include <bsd.port.mk>
