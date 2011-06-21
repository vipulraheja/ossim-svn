%define pref /usr
%define ver 1.0.0
%define ver2 1.0
%define rel 1
%define name ossim-geoid
# Preamble
Summary: Geoid grid files for ossim
Name: ossim-geoid
Version: %{ver}
Release: %{rel}
Copyright: Free
Group: Applications/Image
Source: %{name}-%{ver}.tgz
URL: http://www.ossim.org
Distribution: na
Vendor: imagelinks.com
Packager: Garrett Potts <gpotts@remotesensing.org>
BuildRoot: %{_tmppath}/%{name}-%{ver}-buildroot

%description

%prep
%setup

%build

%install
install -d $RPM_BUILD_ROOT%{pref}/share/ossim/geoid_data
install -m 644 *.bin $RPM_BUILD_ROOT%{pref}/share/ossim/geoid_data
install -m 644 *.grd $RPM_BUILD_ROOT%{pref}/share/ossim/geoid_data
install -m 644 *.txt $RPM_BUILD_ROOT%{pref}/share/ossim/geoid_data

%post

%postun

%files
%defattr(-,root,root)
%{pref}/share/ossim/geoid_data
