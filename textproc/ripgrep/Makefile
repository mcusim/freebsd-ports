# Created by: Petteri Valkonen <petteri.valkonen@iki.fi>

PORTNAME=	ripgrep
DISTVERSION=	12.1.1
PORTREVISION=	12
CATEGORIES=	textproc

MAINTAINER=	petteri.valkonen@iki.fi
COMMENT=	Command line search tool

LICENSE=	MIT UNLICENSE
LICENSE_COMB=	dual
LICENSE_FILE_MIT=	${WRKSRC}/LICENSE-MIT
LICENSE_FILE_UNLICENSE=	${WRKSRC}/UNLICENSE

BUILD_DEPENDS=	asciidoctor:textproc/rubygem-asciidoctor

USES=		cargo
USE_GITHUB=	yes
GH_ACCOUNT=	BurntSushi

CARGO_CRATES=	aho-corasick-0.7.10 \
		atty-0.2.14 \
		autocfg-1.0.0 \
		base64-0.12.1 \
		bitflags-1.2.1 \
		bstr-0.2.13 \
		bytecount-0.6.0 \
		byteorder-1.3.4 \
		cc-1.0.54 \
		cfg-if-0.1.10 \
		clap-2.33.1 \
		crossbeam-channel-0.4.2 \
		crossbeam-utils-0.7.2 \
		encoding_rs-0.8.23 \
		encoding_rs_io-0.1.7 \
		fnv-1.0.7 \
		fs_extra-1.1.0 \
		glob-0.3.0 \
		hermit-abi-0.1.13 \
		itoa-0.4.5 \
		jemalloc-sys-0.3.2 \
		jemallocator-0.3.2 \
		lazy_static-1.4.0 \
		libc-0.2.71 \
		libm-0.1.4 \
		log-0.4.8 \
		maybe-uninit-2.0.0 \
		memchr-2.3.3 \
		memmap-0.7.0 \
		num_cpus-1.13.0 \
		packed_simd_2-0.3.5 \
		pcre2-0.2.3 \
		pcre2-sys-0.2.2 \
		pkg-config-0.3.17 \
		proc-macro2-1.0.17 \
		quote-1.0.6 \
		regex-1.3.9 \
		regex-automata-0.1.9 \
		regex-syntax-0.6.18 \
		ryu-1.0.4 \
		same-file-1.0.6 \
		serde-1.0.110 \
		serde_derive-1.0.110 \
		serde_json-1.0.53 \
		strsim-0.8.0 \
		syn-1.0.27 \
		termcolor-1.1.0 \
		textwrap-0.11.0 \
		thread_local-1.0.1 \
		unicode-width-0.1.7 \
		unicode-xid-0.2.0 \
		walkdir-2.3.1 \
		winapi-0.3.8 \
		winapi-i686-pc-windows-gnu-0.4.0 \
		winapi-util-0.1.5 \
		winapi-x86_64-pc-windows-gnu-0.4.0

RIPGREP_OUTDIR=	${WRKDIR}/cargo-out
CARGO_ENV=	RIPGREP_OUTDIR=${RIPGREP_OUTDIR}

PLIST_FILES=	bin/rg \
		etc/bash_completion.d/rg.bash \
		man/man1/rg.1.gz \
		share/fish/vendor_completions.d/rg.fish \
		share/zsh/site-functions/_rg

PORTDOCS=	CHANGELOG.md FAQ.md GUIDE.md

OPTIONS_DEFINE=	DOCS PCRE2 SIMD
OPTIONS_DEFAULT=PCRE2

OPTIONS_DEFAULT_aarch64=SIMD
OPTIONS_DEFAULT_amd64=	${OPTIONS_DEFAULT_i386}
OPTIONS_DEFAULT_i386=	${MACHINE_CPU:tu:S/SSE2/SIMD/}

PCRE2_DESC=	${PCRE_DESC} version 2
PCRE2_LIB_DEPENDS=	libpcre2-8.so:devel/pcre2
PCRE2_VARS=	CARGO_FEATURES+=pcre2

# simd crate uses cfg_target_feature which isn't stable yet, so unlock
# unstable features similar to how lang/rust bootstraps. www/firefox
# uses the same hack when building with --enable-rust-simd.
SIMD_MAKE_ENV=	RUSTC_BOOTSTRAP=1
SIMD_VARS=	CARGO_FEATURES+=simd-accel ${SIMD_VARS_${ARCH}}
SIMD_VARS_i386=	RUSTFLAGS+="-C target-feature=+sse2"

post-patch:
	@${REINPLACE_CMD} -e 's|OUT_DIR|RIPGREP_OUTDIR|' ${WRKSRC}/build.rs
	@${RLN} ${CARGO_VENDOR_DIR}/packed_simd_2-* ${CARGO_VENDOR_DIR}/packed_simd
	@${REINPLACE_CMD} 's/packed_simd_2/packed_simd/' ${CARGO_VENDOR_DIR}/packed_simd/Cargo.toml

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/bin/rg
	${INSTALL_MAN} ${RIPGREP_OUTDIR}/rg.1 ${STAGEDIR}${MAN1PREFIX}/man/man1
	@${MKDIR} ${STAGEDIR}${PREFIX}/etc/bash_completion.d/
	${INSTALL_DATA} ${RIPGREP_OUTDIR}/rg.bash \
		${STAGEDIR}${PREFIX}/etc/bash_completion.d/
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/fish/vendor_completions.d/
	${INSTALL_DATA} ${RIPGREP_OUTDIR}/rg.fish \
		${STAGEDIR}${PREFIX}/share/fish/vendor_completions.d/
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/zsh/site-functions/
	${INSTALL_DATA} ${WRKSRC}/complete/_rg \
		${STAGEDIR}${PREFIX}/share/zsh/site-functions/

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${PORTDOCS} ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
