# Created by: Simon Marlow <simonmar@microsoft.com>

PORTNAME=	ghc
PORTVERSION=	${GHC_VERSION}
CATEGORIES=	lang haskell
MASTER_SITES=	https://www.haskell.org/ghc/dist/${PORTVERSION}/:source \
		LOCAL/arrowd/:boot \
		https://hackage.haskell.org/package/hscolour-${HSCOLOUR_VERSION}/:docs
DISTFILES=	ghc-${PORTVERSION}-src${EXTRACT_SUFX}:source \
		hscolour-${HSCOLOUR_VERSION}.tar.gz:docs
EXTRACT_ONLY=	${_DISTFILES:C/hscolour.*$//g}

MAINTAINER=	haskell@FreeBSD.org
COMMENT=	Compiler for the functional language Haskell

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386 aarch64 armv6 armv7 powerpc64

USES=			autoreconf compiler:c11 gmake iconv:patch,translit \
			localbase:ldflags ncurses perl5 tar:xz
USE_LOCALE=		en_US.UTF-8
USE_PERL5=		build
GNU_CONFIGURE=		yes
CONFIGURE_ENV=		CC=${CC} LD=${LD} PATH=${SLAVES_PREFIX}/bin:${PATH}
MAKE_ENV=		PATH=${SLAVES_PREFIX}/bin:${PATH}

SUB_FILES=		build.mk
SUB_LIST=		GHC_VERSION=${GHC_VERSION} \
			NCURSESINC="${NCURSESBASE}/include" NCURSESLIB="${NCURSESLIB}" \
			CFLAGS="${CFLAGS}"

OPTIONS_GROUP=		BOOTSTRAP
BOOTSTRAP_DESC=		Bootsrap using installed ghc
OPTIONS_GROUP_BOOTSTRAP=BOOT
OPTIONS_DEFINE=		DYNAMIC GMP PROFILE DOCS
OPTIONS_SUB=		yes

OPTIONS_DEFAULT=	DYNAMIC PROFILE GMP

BOOT_DESC=		Use installed GHC for bootstrapping
DOCS_DESC=		Install HTML documentation
DYNAMIC_DESC=		Add support for dynamic linking
GMP_DESC=		Use GNU Multi-precision Library for big integers support
PROFILE_DESC=		Add support for performance profiling

DOCS_BUILD_DEPENDS=	sphinx-build:textproc/py-sphinx

DYNAMIC_CONFIGURE_WITH=	system-libffi \
			ffi-includes=${LOCALBASE}/include \
			ffi-libraries=${LOCALBASE}/lib
DYNAMIC_LIB_DEPENDS=	libffi.so:devel/libffi
DYNAMIC_SUB_LIST=	WITH_DYNAMIC="YES"
DYNAMIC_SUB_LIST_OFF=	WITH_DYNAMIC="NO"
DYNAMIC_PLIST_SUB=	NODYNAMIC="@comment "
DYNAMIC_PLIST_SUB_OFF=	NODYNAMIC=""

GMP_CONFIGURE_WITH=	gmp-includes=${LOCALBASE}/include \
			gmp-libraries=${LOCALBASE}/lib
GMP_LIB_DEPENDS=	libgmp.so:math/gmp
GMP_SUB_LIST=		INTEGER_LIBRARY="integer-gmp"
GMP_SUB_LIST_OFF=	INTEGER_LIBRARY="integer-simple"
GMP_PLIST_SUB=		GMP="" SIMPLE="@comment "
GMP_PLIST_SUB_OFF=	GMP="@comment " SIMPLE=""

# Append substitutions for build.mk
BOOT_SUB_LIST=		HSC2HS=${LOCALBASE}/bin/hsc2hs
BOOT_SUB_LIST_OFF=	HSC2HS=${BOOT_HSC2HS}

PROFILE_SUB_LIST=	WITH_PROFILE="YES"
PROFILE_SUB_LIST_OFF=	WITH_PROFILE="NO"

GHC_VERSION=		8.10.5
CABAL_VERSION=		3.2.1.0
HSCOLOUR_VERSION=	1.24.4
LLVM_VERSION=		90
# LLVM version that bootstrap compiler uses
BOOT_LLVM_VERSION=	90

PLIST_SUB=		GHC_VERSION=${GHC_VERSION} CABAL_VERSION=${CABAL_VERSION}

PORTDOCS=		*

.include <bsd.port.pre.mk>

# This version of ncurses is needed by bootstrap compiler
.if ${OSVERSION} > 1300078 && empty(PORT_OPTIONS:MBOOT) && ${ARCH} != powerpc64
BUILD_DEPENDS+=	${LOCALBASE}/lib/compat/libncursesw.so.8:misc/compat12x
.endif

.if ${ARCH} == powerpc64 || ${OSVERSION} >= 1400018
CONFIGURE_ARGS+=	--enable-dtrace=0
.endif

.if defined(PPC_ABI) && ${PPC_ABI} == ELFv1
BOOT_GHC_VERSION=      8.6.3
.elif ${ARCH} == aarch64 || ${ARCH:Marmv*}
BOOT_GHC_VERSION=	8.10.4
.else
BOOT_GHC_VERSION=	8.6.5
.endif

NO_CCACHE=	ccache: error: Failed to create directory /nonexistent/.ccache/tmp: Permission denied

DOCSDIR=		${PREFIX}/share/doc/${DISTNAME}
DATADIR=		${PREFIX}/share/ghc-${GHC_VERSION}
EXAMPLESDIR=		${PREFIX}/share/examples/ghc-${GHC_VERSION}
GHC_ARCH=		${ARCH:S/amd64/x86_64/:C/armv.*/arm/}
GHC_LIBDIR=		${STAGEDIR}${PREFIX}/lib/ghc-${GHC_VERSION}
GHC_LIBDIR_REL=		lib/ghc-${GHC_VERSION}

_EXECUTABLES=	${GHC_LIBDIR}/bin/unlit \
		${GHC_LIBDIR}/bin/hpc \
		${GHC_LIBDIR}/bin/ghc-iserv \
		${GHC_LIBDIR}/bin/ghc-pkg \
		${GHC_LIBDIR}/bin/hsc2hs \
		${GHC_LIBDIR}/bin/runghc \
		${GHC_LIBDIR}/bin/ghc \
		${GHC_LIBDIR}/bin/haddock \
		${GHC_LIBDIR}/bin/hp2ps

.if ${PORT_OPTIONS:MPROFILE}
_EXECUTABLES+=	${GHC_LIBDIR}/bin/ghc-iserv-prof
.endif
.if ${PORT_OPTIONS:MDYNAMIC}
_EXECUTABLES+=	${GHC_LIBDIR}/bin/ghc-iserv-dyn
.endif

.if empty(PORT_OPTIONS:MBOOT)
BOOTSTRAPS_SUFFIX?=		${BOOTSTRAPS_SUFFIX_${ARCH}}
BOOTSTRAPS_SUFFIX_powerpc64?=	-${PPC_ABI:tl}
.  if ${OSVERSION} < 1200000 && (${ARCH} == amd64 || ${ARCH} == i386)
ELEVEN_SUFX=		11
.  endif
DISTFILES+=		ghc-${BOOT_GHC_VERSION}-boot-${ARCH}-freebsd${BOOTSTRAPS_SUFFIX}${ELEVEN_SUFX}${EXTRACT_SUFX}:boot
.endif # MBOOT

.if ${ARCH} == aarch64 || ${ARCH:Marmv*}
# ghc-8.10.x on arm requires devel/llvm90
# CONFIGURE_TARGET must to be the same as the llvm triple
CONFIGURE_TARGET=	${ARCH}-unknown-freebsd${"${ARCH:Maarch64}" != "":?:-gnueabihf}
EXTRA_PATCHES+=		${PATCHDIR}/extra-patch-aclocal.m4
BUILD_DEPENDS+=		llc${LLVM_VERSION}:devel/llvm${LLVM_VERSION}
RUN_DEPENDS+=		llc${LLVM_VERSION}:devel/llvm${LLVM_VERSION}
CONFIGURE_ENV+=		LLC=llc${LLVM_VERSION} \
			OPT=opt${LLVM_VERSION} \
			CLANG=clang${LLVM_VERSION} \
			CC=clang${LLVM_VERSION}

# When GHC being compiled and GHC used for bootstrapping support different
# LLVM versions, we have to pull in both. Luckily, this is relatively rare.
.  if ${BOOT_LLVM_VERSION} != ${LLVM_VERSION}
BUILD_DEPENDS+=		llc${BOOT_LLVM_VERSION}:devel/llvm${BOOT_LLVM_VERSION}
# Keep in sync with BOOT_LLVM_VERSION
BINARY_ALIAS+=		llc-9.0=llc90 \
			opt-9.0=opt90
.  endif
.endif

.if ${ARCH} == aarch64 || ${ARCH:Marmv*} || ${ARCH} == powerpc64
.  if ${OSVERSION} < 1202000
IGNORE=	lang/ghc requires at least FreeBSD 12.2-RELEASE
.  endif
.  ifdef QEMU_EMULATING
IGNORE=	qemu-user-static isn't able to build lang/ghc, but it builds fine on a real hardware
.  endif
.endif

.if empty(PORT_OPTIONS:MBOOT)
BOOT_DIR=	${WRKDIR}/ghc-${BOOT_GHC_VERSION}-boot
BOOT_GHC=	${BOOT_DIR}/bin/ghc-${BOOT_GHC_VERSION}
BOOT_GHC-PKG=	${BOOT_DIR}/bin/ghc-pkg-${BOOT_GHC_VERSION}
BOOT_HSC2HS=	${BOOT_DIR}/bin/hsc2hs

SLAVE_ENV=	${SETENV} PATH=${BOOT_DIR}/bin:${PATH}

CONFIGURE_ARGS+=	GHC=${BOOT_GHC}
.else # MBOOT
SLAVE_ENV=		# empty
CONFIGURE_ARGS+=	GHC=${LOCALBASE}/bin/ghc
.endif # MBOOT

SLAVES_PREFIX=		${WRKDIR}/slaves_prefix
SLAVES_WRKDIRPREFIX=	${WRKDIR}/slaves_wrkdirprefix

post-patch:
	@${REINPLACE_CMD} -e 's|%%CC%%|${CC}|; \
		s|%%AR%%|${AR}|; \
		s|%%LD%%|${LD}|' \
		${WRKSRC}/libraries/Cabal/Cabal/Distribution/Simple/Program/Builtin.hs

.if empty(PORT_OPTIONS:MBOOT)
	@${REINPLACE_CMD} -e '/^mandir/d' ${BOOT_DIR}/mk/build.mk
	@${REINPLACE_CMD} -e '/^infodir/d' ${BOOT_DIR}/mk/build.mk
	@${REINPLACE_CMD} -e '/^docdir/d' ${BOOT_DIR}/mk/build.mk
	@${REINPLACE_CMD} -e '/^htmldir/d' ${BOOT_DIR}/mk/build.mk
.endif

.if ${ARCH} == powerpc64 && ${PPC_ABI} == ELFv2
	@${REINPLACE_CMD} -e 's/ELF_V1/ELF_V2/' \
		${WRKSRC}/configure ${WRKSRC}/aclocal.m4
.endif

pre-configure:
	# Copy the subbed build.mk to the proper position
	${CP} ${WRKDIR}/build.mk ${WRKSRC}/mk/build.mk

# If we are using bootstrap compiler, configure and install it into ${BOOT_DIR}
.if empty(PORT_OPTIONS:MBOOT)
	cd ${BOOT_DIR} && ${CONFIGURE_ENV} ${CONFIGURE_CMD} --prefix=${BOOT_DIR}
	cd ${BOOT_DIR} && PACKAGES='' ${MAKE_CMD} install
.else
# otherwise, make sure we have "ghc" in PATH
	if ! ${WHICH} -s ghc ; then \
		echo "No 'ghc' executable is found in your PATH! Turn off BOOT option." ; false ; \
	fi
.endif
# If DOCS are set, install HsColour in-place
.if ${PORT_OPTIONS:MDOCS}
	${MKDIR} ${SLAVES_PREFIX}
	${MKDIR} ${SLAVES_WRKDIRPREFIX}

	cd ${SLAVES_WRKDIRPREFIX} && \
		${TAR} xvf ${DISTDIR}/hscolour-${HSCOLOUR_VERSION}.tar.gz && \
		cd hscolour-${HSCOLOUR_VERSION} && \
		${SLAVE_ENV} ghc --make -o Setup Setup.hs -package Cabal && \
		${SLAVE_ENV} ./Setup configure --ghc --prefix=${SLAVES_PREFIX} --with-gcc=${CC} --with-ld=${LD} && \
		${SLAVE_ENV} ./Setup build && \
		${SLAVE_ENV} ./Setup install
.endif

post-install:
	(for f in ${_EXECUTABLES} $$(${FIND} ${GHC_LIBDIR} -name '*.so*'); do \
		${STRIP_CMD} $$f; done)
	${RM} -r ${STAGEDIR}${DOCSDIR}/html/haddock/.build-html
	${RM} ${STAGEDIR}${PREFIX}/bin/haddock

.PHONY: fixup-plist
fixup-plist:
	${BOOT_DIR}/bin/runhaskell ${PATCHDIR}/fixup-plist.hs ${.CURDIR}/pkg-plist

# Create a bootstrap compiler tar ball: run this in an interactive poudriere jail
# Set all OPTIONS to OFF when generating bootstraps
.PHONY: create-bootstrap
create-bootstrap:
	cd ${WRKSRC} \
		&& ${ECHO} "BIN_DIST_NAME=ghc-${GHC_VERSION}-boot" >> mk/build.mk \
		&& ${ECHO} "BIN_DIST_TAR=ghc-${GHC_VERSION}-boot.tar" >> mk/build.mk \
		&& ${ECHO} "HADDOCK_DOCS=NO" >> mk/build.mk \
		&& ${GMAKE} binary-dist TAR_COMP=xz \
		&& ${MV} ${WRKSRC}/ghc-${GHC_VERSION}-boot-${GHC_ARCH}-portbld-freebsd.tar.xz /tmp/ghc-${GHC_VERSION}-boot-${ARCH}-freebsd.tar.xz

	cd /tmp \
		&& sha256 ghc-${GHC_VERSION}-boot-${ARCH}-freebsd.tar.xz \
		&& ${ECHO} -n "SIZE (ghc-${GHC_VERSION}-boot-${ARCH}-freebsd.tar.xz) = " \
		&& ${STAT} -f %z ghc-${GHC_VERSION}-boot-${ARCH}-freebsd.tar.xz

# Much like create-bootstrap, just different naming and output format
# Set DYNAMIC, GMP and PROFILE to ON, and DOCS to OFF when generating Stack bindist
.PHONY: create-stack-bindist
create-stack-bindist:
	${REINPLACE_CMD} -e '/^mandir/d' \
			-e '/^infodir/d' \
			-e '/^docdir/d' \
			-e '/^htmldir/d' \
		${WRKSRC}/mk/build.mk

	cd ${WRKSRC} \
		&& ${GMAKE} binary-dist TAR_COMP=xz \
		&& ${MV} ${WRKSRC}/ghc-${GHC_VERSION}-${GHC_ARCH}-portbld-freebsd.tar.xz /tmp/

	cd /tmp \
		&& ${ECHO} "${GHC_VERSION}:" \
		&& ${ECHO} "url: \"http://distcache.FreeBSD.org/local-distfiles/arrowd/stack-bindists/ghc-${GHC_VERSION}-${GHC_ARCH}-portbld-freebsd.tar.xz\"" \
		&& ${ECHO} -n "content-length: " \
		&& ${STAT} -f %z ghc-${GHC_VERSION}-${GHC_ARCH}-portbld-freebsd.tar.xz \
		&& ${ECHO} -n "sha1: " \
		&& sha1 -q ghc-${GHC_VERSION}-${GHC_ARCH}-portbld-freebsd.tar.xz \
		&& ${ECHO} -n "sha256: " \
		&& sha256 -q ghc-${GHC_VERSION}-${GHC_ARCH}-portbld-freebsd.tar.xz

.include <bsd.port.post.mk>
