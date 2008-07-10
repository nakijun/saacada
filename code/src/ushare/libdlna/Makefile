include config.mak

all:
	cd ./src && $(MAKE)

install:
	cd ./src && $(MAKE) install
	cp -f *.pc $(libdir)/pkgconfig

clean:
	cd ./src && $(MAKE) clean
	rm -rf config.mak
	rm -rf libdlna.pc
