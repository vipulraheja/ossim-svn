%define pref /usr
%define ver 1.1.7
%define ver2 1.1
%define rel 4
%define name gdal
Summary: Gdal
Name: gdal
Version: %{ver}
Release: %{rel}
Copyright: GPL LGPL
Group: Applications/Image
Source: %{name}-%{ver}.tgz
URL: http://www.remotesensing.org/gdal
Distribution: na
Vendor: Remotesensing 
Packager: Garrett Potts <gpotts@imagelinks.com>
BuildRoot: %{_tmppath}/%{name}-buildroot

%description


%package devel
Summary: Geotiff libraries
Group: Development/Libraries
Requires: geotiff = %{ver}

%description devel
Headers for Geotiff

%prep
%setup
rm -r `find . -name CVS -print`

%build
./configure \
    --prefix=%{pref} \
    --with-ogr
make

%install
make \
  version=%{version} \
  prefix=$RPM_BUILD_ROOT%{pref} \
  sysconfdir=$RPM_BUILD_ROOT%{_sysconfdir} \
  docdir=$RPM_BUILD_ROOT%{_defaultdocdir} \
  install

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%preun devel

%changelog

%files
%defattr(-,root,root)
%{_libdir}/lib*.so*

%dir %{_datadir}/gdal
%{_datadir}/gdal/*

%dir %{_bindir}
%{_bindir}/*

%files devel

%defattr(-,root,root)
%dir %{_includedir}
%{_includedir}/*
%dir %{_libdir}
%{_libdir}/*.a

