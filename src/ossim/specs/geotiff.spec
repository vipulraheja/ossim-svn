%define pref /usr
%define ver 1.1.5
%define ver2 1.1
%define rel 1
%define name geotiff
Summary: Geotiff
Name: geotiff
Version: %{ver}
Release: %{rel}
Copyright: GPL LGPL
Group: Applications/Image
Source: %{name}-%{ver}.tgz
URL: http://www.remotesensing.org/geotiff/geotiff.html
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
cd libgeotiff
./configure \
    --prefix=%{pref} \
    --with-libtiff=/usr
make

%install
cd libgeotiff
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
#%doc %{_docdir}/%{name}-%{version}/
#%config %{_sysconfdir}/%{name}
%{_libdir}/lib*.so*

%dir %{_bindir}
%{_bindir}/*

%files devel
%defattr(-,root,root)
%dir %{_includedir}
%{_includedir}/*
%dir %{_libdir}
%{_libdir}/*.a

%dir %{_datadir}/epsg_csv
%{_datadir}/epsg_csv/*

