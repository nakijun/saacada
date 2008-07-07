#all: clean debug install
all: debug install

dist: rel install rpm

mrs-rel:
	cd ./dongle && $(MAKE)
	cd ./util && $(MAKE)
	cd ./network && $(MAKE)
	cd ./network/s21msglistener && $(MAKE)
	cd ./network/s21msgparser && $(MAKE)
	cd ./app/relayagent && $(MAKE)

mrs-debug:
	cd ./dongle && $(MAKE) debug=1
	cd ./util && $(MAKE) debug=1
	cd ./network && $(MAKE) debug=1
	cd ./network/s21msglistener && $(MAKE) debug=1
	cd ./network/s21msgparser && $(MAKE) debug=1
	cd ./app/relayagent && $(MAKE) debug=1

mrs-clean:
	cd ./dongle && $(MAKE) clean
	cd ./util && $(MAKE) clean
	cd ./network && $(MAKE) clean
	cd ./network/s21msglistener && $(MAKE) clean
	cd ./network/s21msgparser && $(MAKE) clean
	cd ./app/relayagent && $(MAKE) clean cleanrpm
	find . -type f -name "*~" -exec rm {} \;

rel:
	cd ./dongle && $(MAKE)
	cd ./util && $(MAKE)
	cd ./network && $(MAKE)
	cd ./network/s21msglistener && $(MAKE)
	cd ./network/s21msgparser && $(MAKE)
	cd ./app/relayagent && $(MAKE)
	cd ./app/s21ext && $(MAKE)
	cd ./plugin/s21rtsp && $(MAKE)
	cd ./plugin/s21soap && $(MAKE)
	cd ./plugin/s21dlna && $(MAKE)

debug:
	cd ./dongle && $(MAKE) debug=1
	cd ./util && $(MAKE) debug=1
	cd ./network && $(MAKE) debug=1
	cd ./network/s21msglistener && $(MAKE) debug=1
	cd ./network/s21msgparser && $(MAKE) debug=1
	cd ./app/relayagent && $(MAKE) debug=1
	cd ./app/s21ext && $(MAKE) debug=1
	cd ./plugin/s21rtsp && $(MAKE) debug=1
	cd ./plugin/s21soap && $(MAKE) debug=1
	cd ./plugin/s21dlna && $(MAKE) debug=1

clean:
	cd ./dongle && $(MAKE) clean
	cd ./util && $(MAKE) clean
	cd ./network && $(MAKE) clean
	cd ./network/s21msglistener && $(MAKE) clean
	cd ./network/s21msgparser && $(MAKE) clean
	cd ./app/relayagent && $(MAKE) clean cleanrpm
	cd ./app/s21ext && $(MAKE) clean
	cd ./plugin/s21rtsp && $(MAKE) clean
	cd ./plugin/s21soap && $(MAKE) clean
	cd ./plugin/s21dlna && $(MAKE) clean
	find . -type f -name "*~" -exec rm {} \;

doc:
	doxygen Doxyfile

cleandoc:
	rm -rf ../html/

publishdoc:
	rm -rf /var/www/html/mrs
	mv ../html /var/www/html/mrs

rpm:
	cd ./app/relayagent && $(MAKE) rpm

mrs-install:
	cd ./app/relayagent && $(MAKE) install
	ls -l -t /usr/sbin/s21*

install:
	cd ./app/relayagent && $(MAKE) install
	cd ./app/s21ext && $(MAKE) install
	cd ./plugin/s21rtsp && $(MAKE) install
	cd ./plugin/s21soap && $(MAKE) install
	cd ./plugin/s21dlna && $(MAKE) install
	ls -l -t /usr/sbin/s21*

cleandist:
	rm -f /usr/src/redhat/RPMS/i386/s21*

tardebug:
	cd ./app/relayagent/application && tar -cjf /usr/src/redhat/RPMS/i386/s21mrsd-debug.tar.bz2 s21mrsd

cruise: dist
	cd ./app/relayagent/application && tar -cjf /usr/src/redhat/RPMS/i386/s21mrsd-nostrip.tar.bz2 s21mrsd
