$Id: README.txt 9649 2006-10-05 18:31:22Z gpotts $

README file for "Open Source Software Image Map (OSSIM) QT" library and 
applications.

Web site:  http://www.ossim.org/

Build instructions:

For most unix type platforms via command line:
1) Requirements:
   - ossim core library
   - qt development library 3.3 or 3.4.

2) Environment variables:
   - OSSIM_DEV_HOME (This should be the directory where thing are under.) 
   - QTDIR

tcsh/csh users (replace "software" with your path):
setenv QTDIR /usr/lib/qt-3.3
setenv OSSIM_DEV_HOME /software

bash/sh users:
set QTDIR=/usr/lib/qt-3.3
set OSSIM_DEV_HOME=/software
export QTDIR OSSIM_DEV_HOME OSSIM_HOME OSSIM_QT_HOME

3) To build:
cd /software/ossim_qt
qmake ossim_qt.pro
make
make install

You should now have two applications "iview" and "imagelinker" in the 
ossim_qt/bin directory.


