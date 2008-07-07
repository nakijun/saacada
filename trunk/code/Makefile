cruise:
	cd ./src && $(MAKE) clean
	cd ./src && $(MAKE)
	cd ./src && $(MAKE) cleandist tardebug clean
	cd ./src && $(MAKE) cruise

clean:
	cd ./src && $(MAKE) clean
	rm -f lib/libs21*.a BuildError*
	find . -type f -name "*~" -exec rm {} \;
	find . -type f -name "*.tmp" -exec rm {} \;

doc:
	cd ./src && $(MAKE) cleandoc doc publishdoc
