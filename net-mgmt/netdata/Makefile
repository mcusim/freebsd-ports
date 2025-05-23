# Created by: Mahdi Mokhtari <mokhi64@gmail.com>

PORTNAME=	netdata
DISTVERSIONPREFIX=	v
DISTVERSION=	1.31.0
CATEGORIES=	net-mgmt
MASTER_SITES=	https://github.com/${PORTNAME}/${PORTNAME}/releases/download/v${DISTVERSION}/ \
		https://github.com/forkbomb9/netdata/commit/:dashboard
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} fd15080f65fde1c484a06cbc5a13a2853639a960.patch:dashboard
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

# Backport commit to fix interrupt graph
PATCH_SITES=	https://github.com/netdata/netdata/commit/
PATCHFILES=	4b130034f223a5034c241b8a3e905d8f8031747d.patch:-p1

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Scalable distributed realtime performance and health monitoring

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

# Used to patch the custom dashboard
PATCH_DEPENDS=	gpatch:devel/patch
LIB_DEPENDS=	libjson-c.so:devel/json-c \
		libuuid.so:misc/e2fsprogs-libuuid \
		libuv.so:devel/libuv
RUN_DEPENDS=	bash:shells/bash \
		curl:ftp/curl \
		${PYTHON_PKGNAMEPREFIX}yaml>0:devel/py-yaml@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}urllib3>0:net/py-urllib3@${PY_FLAVOR}

USES=		autoreconf cpe gmake pathfix pkgconfig:both python shebangfix \
		ssl
SHEBANG_GLOB=	*

USE_RC_SUBR=	${PORTNAME}

INSTALL_TARGET=	install-strip
CPPFLAGS+=	-D_WANT_VMMETER

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--disable-unit-tests

SUB_FILES=	${PORTNAME}.conf.sample
SUB_LIST=	NETDATA_CACHE=${NETDATA_CACHE} \
		NETDATA_LOG=${NETDATA_LOG} \
		NETDATA_PERST=${NETDATA_PERST}

USERS=		netdata
GROUPS=		netdata

PLIST_SUB=	NETDATA_CACHE=${NETDATA_CACHE} \
		NETDATA_LOG=${NETDATA_LOG} \
		NETDATA_PERST=${NETDATA_PERST}

OPTIONS_DEFINE=		CLOUD CUPS DBENGINE FREEIPMI GOPLUGIN LTO
OPTIONS_DEFAULT=	DBENGINE
OPTIONS_DEFAULT_FreeBSD_12=	LTO
OPTIONS_DEFAULT_FreeBSD_13=	LTO
OPTIONS_DEFAULT_FreeBSD_14=	LTO
OPTIONS_DEFAULT+=	${OPTIONS_DEFAULT_${OPSYS}_${OSREL:R}}
OPTIONS_SUB=		YES

CLOUD_DESC=		Enable cloud functionality
CUPS_DESC=		Enable support for cups
DBENGINE_DESC=		Enable support for database engine
FREEIPMI_DESC=		Enable support for freeipmi
GOPLUGIN_DESC=		Enable the go collector plugin

CLOUD_CONFIGURE_ON=		--with-aclk-ng
CLOUD_CONFIGURE_OFF=		--disable-cloud
CUPS_LIB_DEPENDS=		libcups.so:print/cups
CUPS_CONFIGURE_ENABLE=		plugin-cups
DBENGINE_LIB_DEPENDS=		libJudy.so:devel/judy \
				liblz4.so:archivers/liblz4
DBENGINE_CONFIGURE_ENABLE=	dbengine
FREEIPMI_LIB_DEPENDS=		libfreeipmi.so:sysutils/freeipmi
FREEIPMI_CONFIGURE_ENABLE=	plugin-freeipmi
GOPLUGIN_RUN_DEPENDS=		${LOCALBASE}/libexec/netdata/plugins.d/god.plugin:net-mgmt/netdata-go
LTO_USES=			compiler:c11
LTO_CONFIGURE_ENABLE=		lto

.include <bsd.port.options.mk>
.if ${PORT_OPTIONS:MLTO} && ${OPSYS}_${OSREL:R} == FreeBSD_11
BROKEN=		Link-Time Optimization breaks compilation on FreeBSD 11
.endif

.if ${PORT_OPTIONS:MLTO} && ${ARCH} == powerpc64
USE_GCC=	yes
.endif

NETDATA_CACHE=	/var/cache/${PORTNAME}
NETDATA_LOG=	/var/log/${PORTNAME}
NETDATA_PERST=	/var/db/${PORTNAME}

.if ! ${PORT_OPTIONS:MCLOUD}
post-patch:
	cd ${WRKSRC} && gpatch -p1 < ${_DISTDIR}/fd15080f65fde1c484a06cbc5a13a2853639a960.patch
	@${REINPLACE_CMD} -e 's|%%DISTVERSION%%|${DISTVERSION}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_CACHE%%|${NETDATA_CACHE}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_LOG%%|${NETDATA_LOG}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_PERST%%|${NETDATA_PERST}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%ETCDIR%%|${ETCDIR}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%PYTHON%%|${PYTHON_CMD}|g' \
	    ${PATCH_WRKSRC}/collectors/python.d.plugin/python.d.plugin.in
.else
post-patch:
	@${REINPLACE_CMD} -e 's|%%DISTVERSION%%|${DISTVERSION}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_CACHE%%|${NETDATA_CACHE}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_LOG%%|${NETDATA_LOG}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%NETDATA_PERST%%|${NETDATA_PERST}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%ETCDIR%%|${ETCDIR}|g' \
	    ${PATCH_WRKSRC}/configure.ac
	@${REINPLACE_CMD} -e 's|%%PYTHON%%|${PYTHON_CMD}|g' \
	    ${PATCH_WRKSRC}/collectors/python.d.plugin/python.d.plugin.in
.endif

post-install:
	${MKDIR} ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKDIR}/netdata.conf.sample ${STAGEDIR}${ETCDIR}/netdata.conf.sample
	${TOUCH} ${STAGEDIR}${ETCDIR}/.opt-out-from-anonymous-statistics
	${MKDIR} ${STAGEDIR}${NETDATA_CACHE}
	${MKDIR} ${STAGEDIR}${NETDATA_LOG}
	${MKDIR} ${STAGEDIR}${NETDATA_PERST}
	(for fi in 	${STAGEDIR}${LOCALBASE}/lib/${PORTNAME}/conf.d/*.conf \
			${STAGEDIR}${LOCALBASE}/lib/${PORTNAME}/conf.d/*/*.conf \
			${STAGEDIR}${LOCALBASE}/lib/${PORTNAME}/conf.d/*/*.txt ; do \
		${MV} $$fi $$fi".sample"; \
	done)

.include <bsd.port.mk>
