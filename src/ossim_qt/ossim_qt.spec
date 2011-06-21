#---
# $Id: ossim_qt.spec 7205 2005-01-21 19:14:28Z dburken $
# rpm spec file for building an ossim_qt binary rpm.
#
# See note above %file section before trying to build.
#
# This package require an "ossim" package and the qt development 
# libraries to build.
#---

%define pref /usr
%define ver 1.5.6
%define rel 1
%define name ossim_qt

vendor: Intelligence Data Systems, Inc.
name: ossim_qt
version: 1.5.6
release: 1
summary: ossim_qt library and associated applications
copyright: LGPL
group: Applications/Image
source: %{name}-%{ver}.tgz
url: http://www.ossim.org
distribution: na
packager: David Burken <dburken@intelligence-data.com>
buildroot: %{_builddir}/%{name}-%{ver}
requires: qt >= 3.2

%description
Contains  graphical user interface(gui) applications iview, imagelinker and the required ossim_qt library.

%package devel
Summary: OSSIM QT development package.
Group: Development/Libraries
requires: ossim-devel = %{ver}
requires: qt >= 3.2

%description devel
Headers and templates for OSSIM

%prep

%setup

%build
OSSIM_QT_HOME=$RPM_BUILD_ROOT
export OSSIM_QT_HOME
qmake ossim_qt.pro
make

%install
OSSIM_QT_HOME=$RPM_BUILD_ROOT
export OSSIM_QT_HOME
make install

INSTALL_DIR=$OSSIM_QT_HOME%{_prefix}
BIN_DIR=$INSTALL_DIR/bin
LIB_DIR=$INSTALL_DIR/lib

mkdir -p $INSTALL_DIR
mkdir -p $BIN_DIR
mkdir -p $LIB_DIR
mv bin/iview $BIN_DIR
mv bin/imagelinker $BIN_DIR
mv lib/lib* $LIB_DIR

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

#---
# NOTE:
# Since only a few files from the package are actually packaged you must set
# the macro "%_unpackaged_files_terminate_build 0" to work around the
# unpackaged files error.
#
# You can edit this in /usr/lib/rpm/macros or put it in your .rpmmacros file
# which will override the /usr/lib/rpm/macros.
#---
%files
%defattr(-,root,root)
/usr/bin/iview
/usr/bin/imagelinker
/usr/lib/lib*

%files devel
%defattr(-,root,root)
/

%clean
rm -rf $RPM_BUILD_ROOT

%changelog
