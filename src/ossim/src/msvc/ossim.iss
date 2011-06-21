[Setup]
AppName=imagelinker
AppVerName=1.5.101
DefaultDirName={pf}\ossim
DefaultGroupName=ossim
[Files]
Source: C:\drb\ossim\bin\ossim.dll; DestDir: {app}; Flags: sharedfile replacesameversion
Source: C:\drb\inno_setup\ossim\qt-mtnc321.dll; DestDir: {app}; Flags: sharedfile
Source: C:\drb\inno_setup\ossim\msvcr71.dll; DestDir: {app}; Flags: sharedfile
Source: C:\drb\inno_setup\ossim\msvcp71.dll; DestDir: {app}; Flags: sharedfile
Source: C:\drb\ossim\bin\create_histo.exe; DestDir: {app}
Source: C:\drb\ossim\bin\igen.exe; DestDir: {app}
Source: C:\drb\ossim\bin\image_info.exe; DestDir: {app}
Source: C:\drb\ossim\bin\icp.exe; DestDir: {app}
Source: C:\drb\ossim\bin\imagelinker.exe; DestDir: {app}
Source: C:\drb\ossim\bin\img2rr.exe; DestDir: {app}
[Icons]
Name: {group}\{cm:UninstallProgram, imagelinker}; Filename: {uninstallexe}
Name: {group}\imagelinker; Filename: {app}\imagelinker.exe
[_ISTool]
UseAbsolutePaths=true
