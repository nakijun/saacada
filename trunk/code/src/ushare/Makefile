ifdef debug
	CONFIG = sh ./configure.debug
	MAKE_DLNA=$(MAKE) debug=1
else
	CONFIG = sh ./configure.release
	MAKE_DLNA=$(MAKE)
endif

all: build-libupnp build-libdlna build-ushare

clean: clean-libupnp clean-libdlna clean-ushare

install:

build-libupnp:
	@cd ./libupnp && \
	if [ ! -e Makefile ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-libupnp:
	@cd ./libupnp && \
	if [ -e Makefile ]; then \
	  $(MAKE) distclean; \
	fi

build-libdlna:
	@cd ./libdlna && \
	if [ ! -e config.mak ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-libdlna:
	@cd ./libdlna && \
	if [ -e config.mak ]; then \
	  $(MAKE) clean; \
	fi

build-ushare:
	@cd ./ushare && \
	if [ ! -e config.mak ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-ushare:
	@cd ./ushare && \
	if [ -e config.mak ]; then \
	  $(MAKE) distclean; \
	fi

build-s21dlna:
	@cd ./s21dlna && \
	$(MAKE_DLNA)

clean-s21dlna:
	@cd ./s21dlna && \
	$(MAKE) clean
