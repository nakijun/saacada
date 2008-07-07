CC = g++

LIBPATHS = ../../../../lib
SLIBPATHS = /usr/lib
POCOLIBPATH = ../../../../../3rdparty/poco/lib/Linux/i686
POCOPATH = ../../../../../3rdparty/poco/Foundation/include -I../../../../../3rdparty/poco/XML/include -I../../../../../3rdparty/poco/Net/include
USHAREPATH = ../ushare
USHARESRCPATH = $(USHAREPATH)/src
LIBDLNAPATH = ../libdlna/src -I../ushare/include
LIBUPNPPATH = ../libupnp/upnp/src/inc -I../libupnp/threadutil/inc -I../libupnp/upnp/inc -I../libupnp/ixml/inc

DLNALIBPATH1 = ../libdlna/src/ffmpeg-linux
DLNALIBPATH2 = ../libdlna/src
UPNPLIBPATH1 = /usr/lib
UPNPLIBPATH2 = /usr/lib
UPNPLIBPATH3 = /usr/lib

INCLDS   = -I../../../
INCLDS  += -I.
INCLDS  += -I../../../interface
INCLDS  += -I$(POCOLIBPATH)
INCLDS  += -I$(USHAREPATH)
INCLDS  += -I$(USHARESRCPATH)
INCLDS  += -I$(LIBDLNAPATH)
INCLDS  += -I$(PTHREADPATH)
INCLDS  += -I$(LIBUPNPPATH)

#static libraries
LIBS = $(UPNPLIBPATH3)/libixml.a
LIBS += $(UPNPLIBPATH2)/libupnp.a
LIBS += $(DLNALIBPATH2)/libdlna.a
LIBS += $(UPNPLIBPATH1)/libthreadutil.a
LIBS += $(DLNALIBPATH1)/libavformat.a
LIBS += $(DLNALIBPATH1)/libavcodec.a
LIBS += $(DLNALIBPATH1)/libavutil.a
LIBS += -lz
LIBS += -lbz2
LIBS += -lm
LIBS += $(DLNALIBPATH1)/libavutil.a

#dynamic libraries
#LIBS += -lpthread 
#end

#EXTRALIBS = -lixml -lthreadutil -lpthread -lupnp -ldlna -lavformat -lavcodec -lavutil -lz -lbz2 -lm

OPTFLAGS = -I.. -W -Wall -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -D_REENTRANT -D_GNU_SOURCE -g3 -DHAVE_DEBUG -O3 -DHAVE_LOCALE_H -DHAVE_SETLOCALE -DHAVE_IFADDRS_H -DHAVE_LANGINFO_H -DHAVE_LANGINFO_CODESET -DHAVE_ICONV -pthread -I/usr/include/upnp -I../libdlna/src/ffmpeg-linux -I/usr/include/ffmpeg

LDFLAGS= -L../libdlna/src/ffmpeg-linux

ifdef debug
	CFLAGS   = -g3 -O0 -Wall -DLINUX -D_DEBUG -DDEBUG -DPOCO_STATIC -DNO_USHARE_MAIN -DUPNP_STATIC_LIB -DHAVE_DLNA
	LIBS += $(POCOLIBPATH)/libPocoXMLd.a
	LIBS += $(POCOLIBPATH)/libPocoFoundationd.a
	TARGETS = libs21dlnad.so
else
	CFLAGS   = -O2 -Wall -DLINUX -DPOCO_STATIC -DNO_USHARE_MAIN -DUPNP_STATIC_LIB -DHAVE_DLNA
	LIBS += $(POCOLIBPATH)/libPocoXML.a
	LIBS += $(POCOLIBPATH)/libPocoFoundation.a
	TARGETS = libs21dlna.so
endif

SRCS = $(wildcard *.cpp)

HDRS = $(wildcard *.h)

OBJS = $(SRCS:.cpp=.o)

USHARE_SRCS += $(USHARESRCPATH)/cds.c
USHARE_SRCS += $(USHARESRCPATH)/cms.c
USHARE_SRCS += $(USHARESRCPATH)/msr.c
USHARE_SRCS += $(USHARESRCPATH)/http.c
USHARE_SRCS += $(USHARESRCPATH)/presentation.c
USHARE_SRCS += $(USHARESRCPATH)/metadata.c
USHARE_SRCS += $(USHARESRCPATH)/mime.c
USHARE_SRCS += $(USHARESRCPATH)/services.c
USHARE_SRCS += $(USHARESRCPATH)/buffer.c
USHARE_SRCS += $(USHARESRCPATH)/util_iconv.c
USHARE_SRCS += $(USHARESRCPATH)/content.c
USHARE_SRCS += $(USHARESRCPATH)/cfgparser.c
USHARE_SRCS += $(USHARESRCPATH)/trace.c
USHARE_SRCS += $(USHARESRCPATH)/redblack.c
USHARE_SRCS += $(USHARESRCPATH)/osdep.c
USHARE_SRCS += $(USHARESRCPATH)/ctrl_telnet.c

USHARE_TARGETS = $(USHARE_SRCS:.c=.uo)

USHARE_OBJS += cds.o
USHARE_OBJS += cms.o
USHARE_OBJS += msr.o
USHARE_OBJS += http.o
USHARE_OBJS += presentation.o
USHARE_OBJS += metadata.o
USHARE_OBJS += mime.o
USHARE_OBJS += services.o
USHARE_OBJS += buffer.o
USHARE_OBJS += util_iconv.o
USHARE_OBJS += content.o
USHARE_OBJS += cfgparser.o
USHARE_OBJS += trace.o
USHARE_OBJS += redblack.o
USHARE_OBJS += osdep.o
USHARE_OBJS += ctrl_telnet.o

all: $(TARGETS)

$(TARGETS): $(OBJS) $(USHARE_TARGETS)
	$(CC) -shared -o $@ $(OBJS) $(USHARE_OBJS) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $(INCLDS) -c $<

%.uo: %.c
	$(CC) $(CFLAGS) -x c++ $(OPTFLAGS) $(INCLDS) -c $<

clean:
	rm -f *~ *.o *.so  2>/dev/null

install:
	cp -f *.so /usr/lib
