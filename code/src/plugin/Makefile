ifdef debug
	CONFIG = sh ./config.debug
	MAKE_RTSP=$(MAKE) debug=1
else
	CONFIG = sh ./config.release
	MAKE_RTSP=$(MAKE)
endif

all: build-live555

clean: clean-live555
	@find . -type f -name "*~" -exec rm {} \;

build-live555:
	@cd ./live555 && \
	if [ ! -e Makefile ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) all

clean-live555:
	@cd ./live555 && \
	if [ -e Makefile ]; then \
	  $(MAKE) clean; \
	fi
	@cd ./live555 && \
	find . -type f -name "Makefile" -exec rm {} \;

install:
