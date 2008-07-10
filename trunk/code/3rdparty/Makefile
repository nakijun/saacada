CURRENT_DIR=`pwd`

ifdef debug
	CONFIG = CFLAGS="-g3 -O0" CXXFLAGS="-g3 -O0" sh ./configure --prefix=$(CURRENT_DIR)/../../build
	MAKE_DLNA=$(MAKE) debug=1
else
	CONFIG = CFLAGS="-O3" CXXFLAGS="-O3" sh ./configure --prefix=$(CURRENT_DIR)/../../build
	MAKE_DLNA=$(MAKE)
endif

all: build-ffmpeg

clean: clean-ffmpeg
	@find . -type f -name "*~" -exec rm {} \;

install:

build-ffmpeg:
	@cd ./ffmpeg && \
	if [ ! -e config.mak ]; then \
	  $(CONFIG); \
	fi &&\
	$(MAKE) && $(MAKE) install

clean-ffmpeg:
	if [ -e config.mak ]; then \
	  $(MAKE) clean distclean; \
	fi
