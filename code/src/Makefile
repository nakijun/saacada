#all: clean debug install
all: dbg install

dist: rel install

rel:
	cd ./plugin && $(MAKE)
	cd ./ushare && $(MAKE)

dbg:
	cd ./plugin && $(MAKE) debug=1
	cd ./ushare && $(MAKE) debug=1

clean:
	cd ./plugin && $(MAKE) clean
	cd ./ushare && $(MAKE) clean

install:
	cd ./plugin && $(MAKE) install
	cd ./ushare && $(MAKE) install
