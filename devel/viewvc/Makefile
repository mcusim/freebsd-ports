# Created by: will

PORTNAME=	viewvc
DISTVERSION=	1.2.1
PORTREVISION=	1
CATEGORIES=	devel python

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Web-based Version Control Repository Browsing

CONFLICTS_INSTALL=      py[23][6-8]-viewvc-1.3*

LICENSE=	BSD2CLAUSE

USES=		cpe python:2.7
USE_GITHUB=	yes
USE_RC_SUBR=	viewvc

NO_BUILD=		yes
NO_OPTIONS_SORT=	yes
OPTIONS_DEFINE=		WEBSRV APMOD SVN
OPTIONS_DEFAULT=	WEBSRV APACHE SVN

OPTIONS_SINGLE=		WEBSRV APMOD
OPTIONS_SINGLE_WEBSRV=	APACHE LIGHTTPD
OPTIONS_SINGLE_APMOD=	MODWSGI

WEBSRV_DESC=		Enable web server support
APMOD_DESC=		depend on Apache module

MODWSGI_DESC=		Add mod_wsgi to the list of package dependencies

APACHE_USE=		APACHE_RUN=24+
LIGHTTPD_RUN_DEPENDS=	lighttpd:www/lighttpd
MODWSGI_RUN_DEPENDS=	${APACHE_PKGNAMEPREFIX}${PYTHON_PKGNAMEPREFIX}mod_wsgi>=4.4.13:www/mod_wsgi4@${PY_FLAVOR}

SVN_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}subversion-lts>=0:devel/py-subversion@${PY_FLAVOR}

RUN_DEPENDS+=		${PY_PYGMENTS}

.include <bsd.port.options.mk>

SUB_FILES=	pkg-message
SUB_LIST=	PYTHON_CMD=${PYTHON_CMD} \
		ECHO=${ECHO} EGREP=${EGREP} TOUCH=${TOUCH} \
		CHOWN=${CHOWN} RM=${RM:Q}

pre-everything::
.if ${PORT_OPTIONS:MAPMOD} && !${PORT_OPTIONS:MAPACHE}
IGNORE=	apache module needs Apache server, please re-run 'make config' then choose WEBSRV and APACHE
.endif

post-patch:
.for i in cvsgraph.conf mimetypes.conf viewvc.conf
	${MV} ${WRKSRC}/conf/${i}.dist ${WRKSRC}/conf/${i}.sample
	${REINPLACE_CMD} -e '/"${i}"/d' ${WRKSRC}/viewvc-install
.endfor
	${REINPLACE_CMD} -e 's/conf.dist/conf.sample/g' \
		${WRKSRC}/viewvc-install
# to much files, use own shebangfix
	${FIND} ${WRKSRC} -type f | ${GREP} -v -e 'png' -e 'images' \
		| ${XARGS} ${SED} -i '' \
		-e '1s|^\#![[:space:]]*/usr/bin/env python|\#!${PYTHON_CMD}|' \
		-e '1s|^\#![[:space:]]*/usr/bin/python|\#!${PYTHON_CMD}|'

do-install:
	@(cd ${WRKSRC} && ${PYTHON_CMD} viewvc-install --prefix=${PREFIX}/${PORTNAME} --destdir="${STAGEDIR}" --clean-mode=false)

.include <bsd.port.mk>
