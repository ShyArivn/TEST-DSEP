CC=gcc
CXX=g++
ARC=ar

ARFLAGS = -rcu
CXXFLAGS = -g2 -D__STDC_FORMAT_MACROS -Wall -Wno-sign-compare
MAKE=make

LIBPATH = 
LIBPATH = ./

LIBOBJECT = libnet.a
 
OBJECTS = netacpiocom.o netbuffer.o	netconnection.o netconnectsocket.o \
	netepollevent.o netevent.o nethttpstream.o netiocom.o netiostream.o \
	netpacket.o netserver.o netserversocket.o netsocket.o netstream.o \
	nettcpconnection.o nettcpiocom.o nettcpserver.o nettimeout.o \
	log.o netdoublebuffer.o

INCHEADERS = 

INCLUDEDIR = -I../ -I../include 
CXXFLAGS += $(INCLUDEDIR)

all:$(OBJECTS)
	$(ARC) $(ARFLAGS) $(LIBPATH)$(LIBOBJECT) $(OBJECTS)

netacpiocom.o:netlib.h netacpiocom.cpp
	$(CXX) $(CXXFLAGS) -c netacpiocom.cpp
netbuffer.o:netlib.h netbuffer.cpp
	$(CXX) $(CXXFLAGS) -c netbuffer.cpp
netconnection.o:netlib.h netconnection.cpp
	$(CXX) $(CXXFLAGS) -c netconnection.cpp
netconnectsocket.o:netlib.h netconnectsocket.cpp
	$(CXX) $(CXXFLAGS) -c netconnectsocket.cpp
netepollevent.o:netlib.h netepollevent.cpp
	$(CXX) $(CXXFLAGS) -c netepollevent.cpp
nettcpiocom.o:netlib.h nettcpiocom.cpp
	$(CXX) $(CXXFLAGS) -c nettcpiocom.cpp
netevent.o:netlib.h netevent.cpp
	$(CXX) $(CXXFLAGS) -c netevent.cpp
nethttpserver.o:netlib.h nethttpserver.cpp
	$(CXX) $(CXXFLAGS) -c nethttpserver.cpp
nethttpstream.o:netlib.h nethttpstream.cpp
	$(CXX) $(CXXFLAGS) -c nethttpstream.cpp
netiostream.o:netlib.h netiostream.cpp
	$(CXX) $(CXXFLAGS) -c netiostream.cpp
netpacket.o:netlib.h netpacket.cpp
	$(CXX) $(CXXFLAGS) -c netpacket.cpp
netserver.o:netlib.h netserver.cpp
	$(CXX) $(CXXFLAGS) -c netserver.cpp
netstream.o:netlib.h netstream.cpp
	$(CXX) $(CXXFLAGS) -c netstream.cpp
nettcpconnection.o:netlib.h nettcpconnection.cpp
	$(CXX) $(CXXFLAGS) -c nettcpconnection.cpp
nettcpserver.o:netlib.h nettcpserver.cpp
	$(CXX) $(CXXFLAGS) -c nettcpserver.cpp
netiocom.o:netlib.h netiocom.cpp
	$(CXX) $(CXXFLAGS) -c netiocom.cpp
netserversocket.o:netlib.h netserversocket.cpp
	$(CXX) $(CXXFLAGS) -c netserversocket.cpp
log.o:log.h log.cpp
	$(CXX) $(CXXFLAGS) -c log.cpp
netdoublebuffer.o:netlib.h netdoublebuffer.cpp
	$(CXX) $(CXXFLAGS) -c netdoublebuffer.cpp
clean:
	rm -rf *.o




