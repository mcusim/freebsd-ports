PORTNAME=	colmap
DISTVERSION=	3.6
PORTREVISION=	3
CATEGORIES=	graphics

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Structure from motion and multi-view stereo

LICENSE=	BSD2CLAUSE BSD3CLAUSE CC-BY-3.0 GPLv3+ MIT SIFTGPU
LICENSE_COMB=	multi
LICENSE_NAME_SIFTGPU=	SiftGPU non-commercial license
LICENSE_FILE_BSD2CLAUSE=${WRKSRC}/lib/VLFeat/LICENSE
LICENSE_FILE_BSD3CLAUSE=${WRKSRC}/COPYING.txt # also FLANN
LICENSE_FILE_CC-BY-3.0=	${WRKSRC}/src/ui/media/LICENSE
LICENSE_FILE_GPLv3+ =	${WRKSRC}/lib/PBA/LICENSE # also Graclus, LSD
LICENSE_FILE_MIT=	${WRKSRC}/lib/PoissonRecon/LICENSE
LICENSE_FILE_SIFTGPU=	${WRKSRC}/lib/SiftGPU/LICENSE
LICENSE_PERMS_SIFTGPU=	dist-mirror pkg-mirror auto-accept

LIB_DEPENDS=	libboost_filesystem.so:devel/boost-libs \
		libglog.so:devel/glog \
		libfreeimage.so:graphics/freeimage \
		libceres.so:math/ceres-solver

USES=		cmake compiler:${OPENMP}c++11-lib eigen:3 gl localbase qt:5 \
		sqlite
USE_GITHUB=	yes
USE_GL=		gl glew
USE_QT=		qmake_build buildtools_build core gui opengl_build widgets
EXCLUDE=	SQLite
EXTRACT_AFTER_ARGS=	${EXCLUDE:S,^,--exclude lib/,}
CMAKE_OFF=	BOOST_STATIC CUDA_ENABLED
LDFLAGS+=	-Wl,--as-needed # gflags, glu, xi, xmu
TEST_TARGET=	test

OPTIONS_DEFINE=		CGAL DOCS OPENMP SIMD TEST
OPTIONS_DEFAULT=	CGAL OPENMP SIMD

CGAL_DESC=		Graph-cut on Delaunay triangulation based meshing algorithm
CGAL_BUILD_DEPENDS=	cgal>0:math/cgal
CGAL_CMAKE_BOOL=	CGAL_ENABLED

DOCS_BUILD_DEPENDS=	gmake:devel/gmake \
			sphinx-build:textproc/py-sphinx \
			${NONEXISTENT}:textproc/py-sphinx_rtd_theme
DOCS_PORTDOCS=		*

OPENMP_USES=		compiler:openmp
OPENMP_CMAKE_BOOL=	OPENMP_ENABLED
.if !exists(/usr/include/omp.h)
# XXX ports/199603: LLVM openmp in base doesn't support armv6, armv7 yet
OPENMP_VARS=		OPENMP=gcc-
.endif

SIMD_CMAKE_BOOL=	SIMD_ENABLED

TEST_CMAKE_BOOL=	TESTS_ENABLED

post-patch:
# XXX math/flann has -DUSE_OPENMP=OFF and lacks tunning:
# https://github.com/colmap/colmap/commit/4b594eb85c13
# https://github.com/colmap/colmap/commit/1e9f1f3324cd
	@${REINPLACE_CMD} -e '/SQLite/d' \
		${WRKSRC}/lib/CMakeLists.txt
	@${REINPLACE_CMD} -e 's,SQLite/,,' \
		${WRKSRC}/src/base/database.h \
		${WRKSRC}/src/util/sqlite3_utils.h
.if !defined(DISPLAY) # QApplication
	@${REINPLACE_CMD} -e '/feature_matching_test/d' \
		-e '/feature_extraction_test/d' \
		${WRKSRC}/src/base/CMakeLists.txt
	@${REINPLACE_CMD} -e '/opengl_utils_test/d' \
		${WRKSRC}/src/util/CMakeLists.txt
.endif

post-build-DOCS-on:
	@${SETENV} ${MAKE_ENV} ${GMAKE} ${_MAKE_JOBS} html -C${WRKSRC}/doc

pre-install-TEST-on: do-test

post-install:
# XXX Clean up garbage after install(DIRECTORY)
	@${FIND} ${STAGEDIR}${PREFIX}/include -type d -empty -delete

post-install-DOCS-on:
	(cd ${WRKSRC}/doc/_build/html && ${COPYTREE_SHARE} \
		"${PORTDOCS}" ${STAGEDIR}${DOCSDIR})

.include <bsd.port.mk>
