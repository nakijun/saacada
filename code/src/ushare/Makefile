ifdef debug
	CONFIG = sh ./configure.debug
	MAKE_DLNA=$(MAKE) debug=1
else
	CONFIG = sh ./configure.release
	MAKE_DLNA=$(MAKE)
endif

all: build-libupnp build-libdlna build-ushare build-s21dlna

clean: clean-libupnp clean-libdlna clean-ushare clean-s21dlna
	@find . -type f -name "*~" -exec rm {} \;

install:
	@cd ./s21dlna && \
	$(MAKE) install;

build-libupnp:
	@cd ./libupnp && \
	if [ ! -e Makefile ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-libupnp:
	@cd ./libupnp && \
	$(MAKE) clean; \

build-libdlna:
	@cd ./libdlna && \
	if [ ! -e config.mak ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-libdlna:
	@cd ./libdlna && \
	$(MAKE) clean; \

build-ushare:
	@cd ./ushare && \
	if [ ! -e config.mak ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-ushare:
	@cd ./ushare && \
	$(MAKE) clean; \

build-s21dlna:
	@cd ./s21dlna && \
	$(MAKE_DLNA)

clean-s21dlna:
	@cd ./s21dlna && \
	$(MAKE) clean

