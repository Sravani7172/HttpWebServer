PKG_NAME=libmyhttpwebserver
PKG_VERSION=1.5.7
UBAC_PKG_DEPENDS=libubacjsonparser-1.2.8,libubacsslinterface-1.2.7,libubachttpclient-1.5.2,libubacipc-1.4.4,libubacutils-1.2.5,libubaclogger-1.5.0,libubacyaml-1.2.1
DEB_PKG_DEPENDS=
DEB_18_04_PKG_DEPENDS=
RPM_PKG_DEPENDS=

OBJ_NAME = $(PKG_NAME).so.$(PKG_VERSION)
install_include_dir = /usr/local/include/sbu2webapp/

LIBS = -l:libubacjsonparser.so.1.2.8 -l:libubacsslinterface.so.1.2.7 -l:libubachttpclient.so.1.5.2 -l:libubacipc.so.1.4.4 -l:libubacutils.so.1.2.5 -l:libubaclogger.so.1.5.0 -l:libubacyaml.so.1.2.1

CPP = g++
CPPFLAGS = -g --shared -Wall -fstack-protector-all -Wstack-protector -fno-defer-pop -Wformat -Wformat-security -fexceptions -finline-functions -fPIC -O2                                               
SRC = src/*
BIN = bin

INCLUDE = -I ./include/
OBJ = $(BIN)/$(OBJ_NAME)

all:
	$(CPP) $(SRC) $(INCLUDE) $(CPPFLAGS) $(LIBS) -o $(OBJ)

install-bin:
	cp $(OBJ) /usr/local/lib/
	ldconfig /usr/local/lib

install-dev:
	test -d $(install_include_dir) ||  mkdir $(install_include_dir)
	cp include/* $(install_include_dir)/

install: install-bin install-dev

clean:
	rm -f $(BIN)/*

