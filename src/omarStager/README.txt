$Id$

File:  README.txt for OSSIM Mapping Archive (OMAR) stager.

This is a database stager for omar.  To build you need:

1) ossim core library
2) omar with database up and running
3) gsoap

To build:

1) cd to the "src" directory.
2) Edit the Makefile SOAP_TOP variable.
3) type "gmake"
4) Should generate a "omarstager" application in this directory.

Notes:
Because this will dynamically query the wsdl you must have an instance of OMAR up and running. Example url for wsdl:
http://127.0.0.1:8080/omar/services/StagerWebService?wsdl


