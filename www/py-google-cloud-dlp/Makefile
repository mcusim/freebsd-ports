PORTNAME=	google-cloud-dlp
PORTVERSION=	3.1.0
CATEGORIES=	www python
MASTER_SITES=	CHEESESHOP
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Cloud Data Loss Prevention (DLP) API API client library

LICENSE=	APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}google-api-core>=1.22.2<2.0.0:www/py-google-api-core@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}proto-plus>=0.4.0:devel/py-proto-plus@${PY_FLAVOR}

USES=		python:3.6+
USE_PYTHON=	autoplist concurrent distutils

NO_ARCH=	yes

OPTIONS_DEFINE=	LIBCST
LIBCST_DESC=	Concrete Syntax Tree (CST) support

LIBCST_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}libcst>=0.2.5:devel/py-libcst@${PY_FLAVOR}

.include <bsd.port.mk>
