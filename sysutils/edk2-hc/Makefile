# Created by: Dmitry Salychev <dsl@mcusim.org>

PORTNAME=	edk2
PORTVERSION=	g20210313
CATEGORIES=	sysutils

MAINTAINER=	dsl@mcusim.org
COMMENT=	EDK2 Firmware for SolidRun HoneyComb LX2

LICENSE=	BSD3CLAUSE

ONLY_FOR_ARCHS=		aarch64 amd64
ONLY_FOR_ARCHS_REASON=	This port only provides firmware for aarch64 and amd64 machine

PKGNAMESUFFIX?=	-hc

USES=		gmake python:3.7+,build
USE_GCC=	yes:build

BUILD_DEPENDS+=	dtc>=1.4.1:sysutils/dtc \
		bash:shells/bash

# SolidRun uses their own forks of platforms and non-osi repositories. These
# tags are used in their "lx2160a_uefi" repository.
PLATFORM_TAG=	42aea3c3
NONOSI_TAG=	93839d3e

USE_GITHUB=	yes
GH_ACCOUNT=	SolidRun
GH_TAGNAME=	f55a316f
GH_TUPLE=	SolidRun:edk2-platforms:${PLATFORM_TAG}:platforms \
		SolidRun:edk2-non-osi:${NONOSI_TAG}:nonosi \
		openssl:openssl:OpenSSL_1_1_1g:openssl/CryptoPkg/Library/OpensslLib/openssl \
		ucb-bar:berkeley-softfloat-3:master:softfloat/ArmPkg/Library/ArmSoftFloatLib/berkeley-softfloat-3 \
		kkos:oniguruma:v6.9.4_mark1:oniguruma/MdeModulePkg/Universal/RegularExpressionDxe/oniguruma \
		google:brotli:v1.0.7-17-g666c328:brotli/MdeModulePkg/Library/BrotliCustomDecompressLib/brotli \

BINARY_ALIAS=	make=${LOCALBASE}/bin/gmake \
		dtc=${LOCALBASE}/bin/dtc \
		gcc=${LOCALBASE}/bin/gcc${GCC_DEFAULT} \
		gcc-ar=${LOCALBASE}/bin/gcc-ar${GCC_DEFAULT} \
		g++=${LOCALBASE}/bin/g++${GCC_DEFAULT} \
		python3=${PYTHON_CMD} python=${PYTHON_CMD}

# Board configuration
PLAT=		lx2160acex7
PLAT_ARCH=	AARCH64
PLAT_ARGS=	-D X64EMU_ENABLE=TRUE -D CAPSULE_ENABLE=FALSE
PLAT_TARGET=	RELEASE
PLATFILE=	Platform/SolidRun/LX2160aCex7/LX2160aCex7.dsc
PLAT_RESULT=	LX2160aCex7/${PLAT_TARGET}_GCC5/FV/LX2160ACEX7_EFI.fd
PLAT_FILENAME=	LX2160ACEX7_EFI.fd

PLIST_FILES=	${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME}

# Emulate source edk2/edksetup.sh
MAKE_ENV+=	WORKSPACE=${WRKDIR} \
		PACKAGES_PATH=${WRKDIR}/edk2-${GH_TAGNAME}:${WRKDIR}/edk2-platforms-${PLATFORM_TAG}:${WRKDIR}/edk2-non-osi-${NONOSI_TAG} \
		CONF_PATH=${WRKDIR}/edk2-${GH_TAGNAME}/Conf \
		EDK_TOOLS_PATH=${WRKDIR}/edk2-${GH_TAGNAME}/BaseTools \
		PATH=${WRKDIR}/edk2-${GH_TAGNAME}/BaseTools/BinWrappers/PosixLike:${PATH} \
		PYTHON_COMMAND=python3 \
		PYTHONHASHSEED=1

.if ${PLAT_ARCH} == AARCH64
BUILD_DEPENDS+=	aarch64-none-elf-gcc:devel/aarch64-none-elf-gcc
MAKE_ENV+=	GCC5_AARCH64_PREFIX=aarch64-none-elf-
.endif

.if ${PLAT_ARCH} == X64
BUILD_DEPENDS+=	nasm:devel/nasm
.endif

# We can't have two submodule with the same origin in GH_TUPLE
post-extract:
	(cd ${WRKDIR}/edk2-${GH_TAGNAME}/MdeModulePkg/Library/BrotliCustomDecompressLib/brotli && tar cf - * | tar xf - -C ../../../../BaseTools/Source/C/BrotliCompress/brotli)

do-build:
	# This is normaly done during source edksetup.sh
	(cp ${WRKDIR}/edk2-${GH_TAGNAME}/BaseTools/Conf/build_rule.template ${WRKDIR}/edk2-${GH_TAGNAME}/Conf/build_rule.txt)
	(cp ${WRKDIR}/edk2-${GH_TAGNAME}/BaseTools/Conf/tools_def.template ${WRKDIR}/edk2-${GH_TAGNAME}/Conf/tools_def.txt)
	(cp ${WRKDIR}/edk2-${GH_TAGNAME}/BaseTools/Conf/target.template ${WRKDIR}/edk2-${GH_TAGNAME}/Conf/target.txt)
	# Build the basetools
	(cd ${WRKDIR} && ${SETENV} ${MAKE_ENV} ${MAKE_CMD} -C edk2-${GH_TAGNAME}/BaseTools ${_MAKE_JOBS})
	# Build EDK2
	(cd ${WRKDIR}/edk2-${GH_TAGNAME} && ${SETENV} ${MAKE_ENV} BaseTools/BinWrappers/PosixLike/build -a ${PLAT_ARCH} -p ${PLATFILE} -n ${MAKE_JOBS_NUMBER} -t GCC5 -b ${PLAT_TARGET} ${PLAT_ARGS})

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/
	# ${INSTALL_DATA} ${WRKDIR}/Build/${PLAT_RESULT} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME}

.include <bsd.port.mk>
