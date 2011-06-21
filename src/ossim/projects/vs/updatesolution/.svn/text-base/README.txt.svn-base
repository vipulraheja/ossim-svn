------------------UpdateSolution---------------------------
Written By: David A. Horner - (http://dave.thehorners.com)
License: LGPL
-----------------------------------------------------------
This is a program I wrote to create solution and project
files for the OSSIM tree.  I did this because I didn't want to
have to copy files by hand...and there are a lot of apps in the
OSSIM tree.

This program allows the developer to maintain a set of template
files which are populated with source code from the OSSIM tree.
This means you can quickly change the include and code generation
parameters specific to your build machine without having to
manually change each and every project file.

(It also means you can quickly re-generate the projects when files
are added or removed from the OSSIM tree)

At this time the software overwrites the contents of existing solution
and project files.  Be careful, changes made to solution/project files
will be lost.

NOTE:
It is important that updatesolution.exe be run from:
makefiles\vs2005\updatesolution\updatesolution\bin\Release or
makefiles\vs2005\updatesolution\updatesolution\bin\Debug
As it relies on this location to find all the OSSIM source.


What is a project template file?
--------------------------------
A template file is simply a .vcproj file with all the <File>
entries erased from the <Files> section.  Sample templates can
be found in the templates folder of updatesolution.

To make a new template, open the existing solution/project files
get it to compile with your specific include/lib information. Save it,
then strip out all the files in the <Files> section.

Make sure to leave the <Files> entry so that updatesolution
knows where to stuff the files it finds.