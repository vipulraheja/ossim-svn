###
# $Id$
# GNU Makefile for omarStager.
###


###
# SOAP setup. 
###

# Set sop top if not already set.
SOAP_TOP?=/usr/local/ossim
SOAP_INC=-Iimport -I$(SOAP_TOP)/include
SOAP_LIBS=-L$(SOAP_TOP)/lib -lgsoapssl++ -lgsoap++ -lgsoapssl -lgsoap -lssl -lcrypto
SOAPCPP2=$(SOAP_TOP)/bin/soapcpp2
WSDL2H=$(SOAP_TOP)/bin/wsdl2h
SOAPCPP2=$(SOAP_TOP)/bin/soapcpp2
WSDL2H=$(SOAP_TOP)/bin/wsdl2h

###
# OSSIM setup.
###

# Set ossim home if not already set. Note: This must be a development ossim.
OSSIM_HOME?=/work/drb/ossim
OSSIM_LIBS=-L$(OSSIM_HOME)/lib/ossim -lossim

CPPSRCS=$(wildcard *.cpp)
DEPENDS_FILES=$(wildcard *.d)

include $(OSSIM_HOME)/Makefile.common

INCLUDES=$(SOAP_INC) -I. $(BASE_INCLUDES)

CPPSRCS= \
omarArrayOfFileObject.cpp \
omarArrayOfGeospatialType.cpp \
omarArrayOfRasterEntryObject.cpp \
omarArrayOfSensorType.cpp \
omarFileObject.cpp \
omarGeometryObject.cpp \
omarGeospatialType.cpp \
omarProductType.cpp \
omarRasterDataSetObject.cpp \
omarRasterEntryObject.cpp \
omarSecurityClassificationType.cpp \
omarSensorType.cpp \
omarUnitType.cpp \
omarStagerUtil.cpp

CPPOBJS=$(patsubst %.cpp,%.o,$(CPPSRCS))
OBJS=$(CPPOBJS)


all:		omarstager 

# omarstager:  	omarstager.cpp $(SOAPH) $(SOAPCPP)
omarstager:  	omarStagerWsdl.h soapServer.o soapClient.o soapC.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -o ../omarstager omarstager.cpp soapC.cpp soapClient.cpp $(CPPOBJS) $(LIBS) $(OSSIM_LIBS) $(SOAP_LIBS)


###
# Generate the starting "omarStagerWsdl" from the wsdl which is dynamically
# querried when you type make.
###
omarStagerWsdl.h:
	$(WSDL2H) -t typemap.dat -o omarStagerWsdl.h "http://127.0.0.1:8080/omar-1.1/services/StagerWebService?wsdl"

###
# This generates soapServer.cpp, soapClient.cpp, and  soapC.cpp.
###
soapServer.cpp:
	$(SOAPCPP2) $(SOAP_INC) omarStagerWsdl.h

###
# Soap generated cpp targets.
###
soapServer.o: soapServer.cpp
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -c soapServer.cpp -o soapServer.o

soapClient.o:
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -c soapClient.cpp -o soapClient.o

soapC.o:
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -c soapC.cpp -o soapC.o

depends: $(CPPSRCS:.cpp=.d)

clean:
		rm -f *.o soap* StagerWeb* *~ ../omarstager omar2.nsmap omarStagerWsdl.h

distclean:
		rm -f *.o soap* StagerWeb*


# Pattern rule for .o's from .cpp's:
%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) -c $< -o $@

# Pattern rule for .d dependency file from .cpp files.
%.d: %.cpp
	$(SHELL) -ec '$(CXX) $(CXXFLAGS) $(CDEBUGFLAGS) $(BASE_DEFINES) $(INCLUDES) $< >> $@;'
