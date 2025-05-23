PORTNAME=	cargo-c
DISTVERSION=	0.8.2
DISTVERSIONSUFFIX=	+cargo-0.54
CATEGORIES=	devel
MASTER_SITES=	CRATESIO
# XXX Teach USES=cargo to have proper default
DISTFILES=	${CARGO_DIST_SUBDIR}/${DISTNAME}${CARGO_CRATE_EXT}

MAINTAINER=	jbeich@FreeBSD.org
COMMENT=	Cargo C-ABI helpers

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libgit2.so:devel/libgit2 \
		libcurl.so:ftp/curl \
		libssh2.so:security/libssh2

USES=		cargo ssl
PLIST_FILES=	bin/cargo-capi \
		bin/cargo-cbuild \
		bin/cargo-cinstall \
		bin/cargo-ctest \
		${NULL}

CARGO_CRATES=	adler-1.0.2 \
		aho-corasick-0.7.18 \
		ansi_term-0.11.0 \
		anyhow-1.0.41 \
		atty-0.2.14 \
		autocfg-1.0.1 \
		bitflags-1.2.1 \
		bitmaps-2.1.0 \
		bstr-0.2.16 \
		bytesize-1.0.1 \
		cargo-0.54.0 \
		cargo-platform-0.1.1 \
		cargo-util-0.1.0 \
		cbindgen-0.19.0 \
		cc-1.0.68 \
		cfg-if-1.0.0 \
		clap-2.33.3 \
		commoncrypto-0.2.0 \
		commoncrypto-sys-0.2.0 \
		core-foundation-0.9.1 \
		core-foundation-sys-0.8.2 \
		crates-io-0.33.0 \
		crc32fast-1.2.1 \
		crossbeam-utils-0.8.5 \
		crypto-hash-0.3.4 \
		curl-0.4.38 \
		curl-sys-0.4.44+curl-7.77.0 \
		env_logger-0.8.4 \
		filetime-0.2.14 \
		flate2-1.0.20 \
		fnv-1.0.7 \
		foreign-types-0.3.2 \
		foreign-types-shared-0.1.1 \
		form_urlencoded-1.0.1 \
		fwdansi-1.1.0 \
		getrandom-0.2.3 \
		git2-0.13.20 \
		git2-curl-0.14.1 \
		glob-0.3.0 \
		globset-0.4.7 \
		hashbrown-0.9.1 \
		heck-0.3.3 \
		hermit-abi-0.1.18 \
		hex-0.3.2 \
		hex-0.4.3 \
		home-0.5.3 \
		humantime-2.1.0 \
		idna-0.2.3 \
		ignore-0.4.18 \
		im-rc-15.0.0 \
		indexmap-1.6.2 \
		itoa-0.4.7 \
		jobserver-0.1.22 \
		lazy_static-1.4.0 \
		lazycell-1.3.0 \
		libc-0.2.97 \
		libgit2-sys-0.12.21+1.1.0 \
		libnghttp2-sys-0.1.6+1.43.0 \
		libssh2-sys-0.2.21 \
		libz-sys-1.1.3 \
		log-0.4.14 \
		matches-0.1.8 \
		memchr-2.4.0 \
		miniz_oxide-0.4.4 \
		miow-0.3.7 \
		num_cpus-1.13.0 \
		once_cell-1.8.0 \
		opener-0.4.1 \
		openssl-0.10.34 \
		openssl-probe-0.1.4 \
		openssl-src-111.15.0+1.1.1k \
		openssl-sys-0.9.63 \
		percent-encoding-2.1.0 \
		pkg-config-0.3.19 \
		ppv-lite86-0.2.10 \
		proc-macro-error-1.0.4 \
		proc-macro-error-attr-1.0.4 \
		proc-macro2-1.0.27 \
		quote-1.0.9 \
		rand-0.8.4 \
		rand_chacha-0.3.1 \
		rand_core-0.5.1 \
		rand_core-0.6.3 \
		rand_hc-0.3.1 \
		rand_xoshiro-0.4.0 \
		redox_syscall-0.2.9 \
		regex-1.5.4 \
		regex-syntax-0.6.25 \
		remove_dir_all-0.5.3 \
		rustc-workspace-hack-1.0.0 \
		rustfix-0.5.1 \
		ryu-1.0.5 \
		same-file-1.0.6 \
		schannel-0.1.19 \
		semver-0.10.0 \
		semver-parser-0.7.0 \
		serde-1.0.126 \
		serde_derive-1.0.126 \
		serde_ignored-0.1.2 \
		serde_json-1.0.64 \
		shell-escape-0.1.5 \
		sized-chunks-0.6.5 \
		socket2-0.4.0 \
		strip-ansi-escapes-0.1.0 \
		strsim-0.8.0 \
		structopt-0.3.21 \
		structopt-derive-0.4.14 \
		syn-1.0.73 \
		tar-0.4.35 \
		tempfile-3.2.0 \
		termcolor-1.1.2 \
		textwrap-0.11.0 \
		thread_local-1.1.3 \
		tinyvec-1.2.0 \
		tinyvec_macros-0.1.0 \
		toml-0.5.8 \
		typenum-1.13.0 \
		unicode-bidi-0.3.5 \
		unicode-normalization-0.1.19 \
		unicode-segmentation-1.7.1 \
		unicode-width-0.1.8 \
		unicode-xid-0.2.2 \
		url-2.2.2 \
		utf8parse-0.1.1 \
		vcpkg-0.2.14 \
		vec_map-0.8.2 \
		version_check-0.9.3 \
		vte-0.3.3 \
		walkdir-2.3.2 \
		wasi-0.10.2+wasi-snapshot-preview1 \
		winapi-0.3.9 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-util-0.1.5 \
		winapi-x86_64-pc-windows-gnu-0.4.0

post-patch:
	@${REINPLACE_CMD} -e 's,libdir.join("pkgconfig,prefix.join("libdata/pkgconfig,' \
		${WRKSRC}/src/install.rs

.include <bsd.port.mk>
