# Created by: Alex Dupre <ale@FreeBSD.org>

PORTNAME=	solidity
PORTVERSION=	0.8.5
CATEGORIES=	lang
MASTER_SITES=	https://github.com/ethereum/solidity/releases/download/v${PORTVERSION}/
DISTNAME=	${PORTNAME}_${PORTVERSION}

MAINTAINER=	ale@FreeBSD.org
COMMENT=	Solidity Contract-Oriented Programming Language

LICENSE=	GPLv3

NOT_FOR_ARCHS=		powerpc powerpc64 powerpcspe sparc64
NOT_FOR_ARCHS_REASON=	solidity currently does not support big endian systems

BUILD_DEPENDS=	boost-libs>=0:devel/boost-libs \
		range-v3>=0:devel/range-v3
LIB_DEPENDS=	libjsoncpp.so:devel/jsoncpp

USES=		cmake compiler:c++14-lang

OPTIONS_DEFINE=	Z3 CVC4
OPTIONS_DEFAULT=Z3 CVC4
Z3_DESC=	SMT Checker via Z3
CVC4_DESC=	SMT Checker via CVC4
Z3_LIB_DEPENDS=		libz3.so:math/z3
CVC4_LIB_DEPENDS=	libcvc4.so:math/cvc4 libgmp.so:math/gmp
Z3_CMAKE_OFF=	USE_Z3
CVC4_CMAKE_OFF=	USE_CVC4

CMAKE_ARGS+=	-DUSE_LD_GOLD=OFF -DTESTS=OFF \
		-DRANGE_V3_INCLUDE_DIR="${LOCALBASE}/include" \
		-DJSONCPP_INCLUDE_DIR:STRING="${LOCALBASE}/include/jsoncpp" \
		-DJSONCPP_LIB_DIR:STRING="${LOCALBASE}/lib"

PLIST_FILES=	bin/solc \
		bin/solidity-upgrade \
		bin/yul-phaser

pre-patch:
		@${CP} ${FILESDIR}/jsoncpp.cmake ${WRKSRC}/cmake/
		@${REINPLACE_CMD} '/EthCcache/d' ${WRKSRC}/CMakeLists.txt

.include <bsd.port.mk>
