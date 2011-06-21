# $Id: ospr.spec 423 2001-06-28 15:12:09Z gpotts $
# $crtd: by Kenneth Melero on 062501 $

%define withgrass no

# Preamble
Summary: Open Source Prototype Tools (OSPR)
Name: ospr
Version: 0.1.0
Release: 1
Copyright: GPL LGPL
Group: Applications/Image
Source: ftp://ftp.remotesensing.org/pub/ossim/%{name}-%{version}.tgz
URL: http://www.remotesensing.org/ossim/
Distribution: na
Vendor: imagelinks.com
Packager: Kenneth Melero <kmelero@remotesensing.org>
BuildRoot: %{_tmppath}/%{name}-%{version}

%description
OSPR is based on the OSSIM (Open Source Software Image Map) library.  Pronounced "awesome", the OSSIM project leverages existing open source algorithms, tools, and packages to construct an integrated library for remote sensing, image-processing, and Geographical Information Sciences (GIS) analysis.

%prep
%setup
rm -r `find . -name CVS -print`

%build
./configure \
    --prefix=%{_prefix} \
    --with-grass=%{withgrass} \
    --without-python
make

%install
make \
  version=%{version} \
  prefix=$RPM_BUILD_ROOT%{_prefix} \
  sysconfdir=$RPM_BUILD_ROOT%{_sysconfdir} \
  docdir=$RPM_BUILD_ROOT%{_defaultdocdir} \
  install

%changelog
* Mon Jun 06 2001  Kenneth Melero <kmelero@remotesensing.org>
-Initial packaging.
-Contains icp, mosaic

%files
%defattr(-,root,root)
%{_bindir}/icp
%{_bindir}/mosaic
%{_bindir}/img2rr
