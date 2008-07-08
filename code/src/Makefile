#all: clean debug install
all: debug install

dist: rel install

rel:
	cd ./plugin && $(MAKE)
	cd ./ushare && $(MAKE)

debug:
	cd ./plugin && $(MAKE) debug=1
	cd ./ushare && $(MAKE) debug=1

clean:
	cd ./plugin && $(MAKE) clean
	cd ./ushare && $(MAKE) clean
	find . -type f -name "*~" -exec rm {} \;

doc:
	doxygen Doxyfile

cleandoc:
	rm -rf ../html/

publishdoc:
	rm -rf /var/www/html/mrs
	mv ../html /var/www/html/mrs

install:
	cd ./plugin && $(MAKE) install
	cd ./ushare && $(MAKE) install
	ls -l -t /usr/sbin/s21*

