# Created by: Julien Laffaye <jlaffaye@FreeBSD.org>

PORTNAME=	pelican
PORTVERSION=	4.6.0
CATEGORIES=	www textproc python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	andreas@bilke.org
COMMENT=	Static site generator written in Python

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}docutils>=0.15:textproc/py-docutils@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}Jinja2>=2.7:devel/py-Jinja2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}feedgenerator>=1.9:www/py-feedgenerator@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pytz>0:devel/py-pytz@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}blinker>0:devel/py-blinker@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}unidecode>0:converters/py-unidecode@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}six>=1.4:devel/py-six@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}dateutil>0:devel/py-dateutil@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}mock>0:devel/py-mock@${PY_FLAVOR}

USES=		python:3.6+ shebangfix
USE_GITHUB=	yes
USE_PYTHON=	autoplist concurrent distutils

SHEBANG_FILES=	pelican/tools/templates/publishconf.py.jinja2 \
		pelican/tools/templates/pelicanconf.py.jinja2 \
		pelican/tools/*.py
NO_ARCH=	yes

GH_ACCOUNT=	getpelican

OPTIONS_DEFINE=		MARKDOWN SYNTAX
OPTIONS_DEFAULT=	MARKDOWN SYNTAX

MARKDOWN_DESC=		Markdown markup language format support
MARKDOWN_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}markdown>=3.1.1:textproc/py-markdown@${PY_FLAVOR}

SYNTAX_DESC=		Syntax Highlighting (via pygments)
SYNTAX_RUN_DEPENDS=	${PY_PYGMENTS}

do-test:
	@cd ${WRKSRC} && ${PYTHON_CMD} ${PYDISTUTILS_SETUP} test

.include <bsd.port.mk>
