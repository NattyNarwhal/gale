%define	name	gale
%define	version	1.1happy
%define	release	3

Summary:	Gale
Name:		%{name}
Version:	%{version}
Release:	%{release}
License:	GPLv2+
Group:		Applications/Networking
URL:		http://www.gale.org/
Vendor:		Calvin Buckley <calvin@cmpct.info>
Source0:	%{name}-%{version}.tar.gz

Distribution:	Gale Distribution
Packager:	Calvin Buckley <calvin@cmpct.info>

Requires:	gale-base

# ...at least on Red Hat/Fedora
BuildRequires:	gc-devel
BuildRequires:	adns-devel
BuildRequires:	tcl-devel
BuildRequires:	glib2-devel
BuildRequires:	readline-devel
BuildRequires:	openssl-devel

%package base
Summary:	Gale Shared Components
Group:		Development/Libraries

%package server
Summary:	Gale Server
Group:		Development/Libraries
Requires:	gale-base

%package devel
Summary:	Gale Development Headers
Group:		Development/Libraries
Requires:	gale-base

%package -n liboop
License:	LGPLv2.1+
Summary:	Low-level event loop management library for POSIX
Group:		Development/Libraries

%package -n liboop-devel
License:	LGPLv2.1+
Summary:	Low-level event loop management library for POSIX - development headers
Group:		Development/Libraries

%description
Gale is instant messaging software distributed under the terms of the GPL.
It offers secure, reliable, scalable and usable instant messaging services.
This is the client package for command-line access to the Gale network.

%description base
Gale is instant messaging software distributed under the terms of the GPL.
This is the base package required by both server and clients.

%description server
Gale is a freeware instant messaging and presence software for Unix.
This is the server package needed to operate a Gale domain.

%description devel
Gale is a freeware instant messaging and presence software for Unix.
This is the development package needed to build programs with the Gale API.

%description -n liboop
Liboop is a low-level event loop management library for POSIX-based operating
systems. It supports the development of modular, multiplexed applications which
may respond to events from several sources. It replaces the "select() loop" and
allows the registration of event handlers for file and network I/O, timers and
signals. Since processes use these mechanisms for almost all external
communication, liboop can be used as the basis for almost any application. 

%description -n liboop-devel
Liboop is a low-level event loop management library for POSIX-based operating
systems. It supports the development of modular, multiplexed applications which
may respond to events from several sources. It replaces the "select() loop" and
allows the registration of event handlers for file and network I/O, timers and
signals. Since processes use these mechanisms for almost all external
communication, liboop can be used as the basis for almost any application. 

This is the development package needed to build programs with the Gale API.

%prep
%setup -q

%build

%configure --disable-static
%make_build

%install

%make_install
rm $RPM_BUILD_ROOT/%{_libdir}/*.la
rm $RPM_BUILD_ROOT/%{_sysconfdir}/gale/COPYING
touch $RPM_BUILD_ROOT/%{_sysconfdir}/gale/conf

%files
%defattr(-,root,root)
%{_bindir}/gkgen
%{_bindir}/gkinfo
%{_bindir}/gksign
%{_bindir}/gsend
%{_bindir}/gsub
%{_sbindir}/gksign

%files base
%license COPYING
%config(noreplace) %{_sysconfdir}/gale/conf
%dir %{_sysconfdir}/gale/auth
# Is a ROOT key supposed to exist?
%config(noreplace) %{_sysconfdir}/gale/auth/trusted/ROOT
%{_libdir}/libgale*.so.*
%{_bindir}/gale-config
%{_bindir}/gale-install

%files devel
%{_includedir}/gale
%{_libdir}/libgale*.so

%files server
%{_bindir}/galed
%{_bindir}/gdomain

%files -n liboop
%{_libdir}/liboop*.so.*

%files -n liboop-devel
%{_libdir}/liboop*.so
%{_libdir}/pkgconfig/*.pc
%{_includedir}/oop*.h

# Previous version ran gale-install directly, but it seems unwise to run
# interactive commands when you don't know the scenario they're in. I think it
# would be better to run gale-install yourself.
