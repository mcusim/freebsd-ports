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
		git:devel/git \
		bash:shells/bash \
		gcc${GCC_DEFAULT}:lang/gcc${GCC_DEFAULT} \
		${PREFIX}/share/u-boot/u-boot-lx2160acex7/u-boot.bin:sysutils/u-boot-lx2160acex7 \
		${PREFIX}/share/rcw/rcw-lx2160acex7/lx2160acex7.bin:sysutils/rcw-lx2160acex7

USES=		gmake shebangfix
BINARY_ALIAS=	gcc=gcc${GCC_DEFAULT}

SHEBANG_GLOB=	*.sh *.mk
SSP_UNSAFE=	yes
ATF_DIR=	share/atf/${PORTNAME}${PKGNAMESUFFIX}
INST=		${PREFIX}/${ATF_DIR}
DESCR?=		${.CURDIR}/pkg-descr

MAKE_ENV+=	BL33=${PREFIX}/share/u-boot/u-boot-lx2160acex7/u-boot.bin
MAKE_ARGS+=	V=1 CROSS_COMPILE=${CROSS_COMPILE} ${ARCHFLAGS} \
		PLAT=${PLAT} all fip pbl \
		RCW=${PREFIX}/share/rcw/rcw-lx2160acex7/lx2160acex7.bin \
		TRUSTED_BOARD_BOOT=0 GENERATE_COT=0 BOOT_MODE=auto SECURE_BOOT=false

NO_ARCH=	yes

CROSS_COMPILE=	aarch64-none-elf-
ARCHFLAGS=	ARCH="aarch64"
COMPILER?=	${CROSS_COMPILE}gcc

PLAT=		lx2160acex7

# NXP's Layerscape SDK version
LSDK_VERSION?=	20.12
LSDK_COMMIT?=	9225ad51f026975fa6b86db800f43c55db11fa4d
LSDK_SITES?=	https://source.codeaurora.org/external/qoriq/qoriq-components/atf/snapshot/
NXP_DDR_BINARY_SITE?=https://github.com/NXP/ddr-phy-binary.git

PLIST_FILES+=	${ATF_DIR}/bl2.bin \
		${ATF_DIR}/bl2_auto.pbl \
		${ATF_DIR}/bl31.bin \
		${ATF_DIR}/fip.bin \
		${ATF_DIR}/fip_ddr_all.bin \
		${ATF_DIR}/README

post-patch:
	${FIND} ${WRKSRC} -name "*.orig" -delete

do-configure:
	(cd ${WRKSRC}/tools/fiptool; git clone ${NXP_DDR_BINARY_SITE})
	(cd ${WRKSRC}/tools/fiptool; ${SETENV} ${CONFIGURE_ENV} ${MAKE_CMD})
	(cd ${WRKSRC}/tools/fiptool; ./fiptool create \
		--ddr-immem-udimm-1d ddr-phy-binary/lx2160a/ddr4_pmu_train_imem.bin \
		--ddr-immem-udimm-2d ddr-phy-binary/lx2160a/ddr4_2d_pmu_train_imem.bin \
		--ddr-dmmem-udimm-1d ddr-phy-binary/lx2160a/ddr4_pmu_train_dmem.bin \
		--ddr-dmmem-udimm-2d ddr-phy-binary/lx2160a/ddr4_2d_pmu_train_dmem.bin \
		--ddr-immem-rdimm-1d ddr-phy-binary/lx2160a/ddr4_rdimm_pmu_train_imem.bin \
		--ddr-immem-rdimm-2d ddr-phy-binary/lx2160a/ddr4_rdimm2d_pmu_train_imem.bin \
		--ddr-dmmem-rdimm-1d ddr-phy-binary/lx2160a/ddr4_rdimm_pmu_train_dmem.bin \
		--ddr-dmmem-rdimm-2d ddr-phy-binary/lx2160a/ddr4_rdimm2d_pmu_train_dmem.bin \
		fip_ddr_all.bin)

do-install:
	${MKDIR} ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/build/${PLAT}/release/bl2.bin ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/build/${PLAT}/release/bl2_auto.pbl ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/build/${PLAT}/release/bl31.bin ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/build/${PLAT}/release/fip.bin ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${WRKSRC}/tools/fiptool/fip_ddr_all.bin ${STAGEDIR}/${INST}
	${INSTALL_DATA} ${DESCR} ${STAGEDIR}/${INST}/README

.include <bsd.port.mk>
