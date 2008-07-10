all:
	cd ./3rdparty && $(MAKE)
	cd ./src && $(MAKE)

clean:
	cd ./3rdparty && $(MAKE) clean
	cd ./src && $(MAKE) clean
	@find . -type f -name "*~" -exec rm {} \;
	@find . -type f -name "*.tmp" -exec rm {} \;
	@find . -type f -name "*.log" -exec rm {} \;
	@rm -rf build/
