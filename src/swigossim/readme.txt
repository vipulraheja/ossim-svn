COMPILING:

copy the local.properties.template to local.properties and modify for your system.

now type
ant <return>
should have a successful bild




RUNNING:

Before running note that if you are on the MAC 
you have linked to frameworks not in the standard location such as /Library/Frameworks or ~/Library/Frameworks, then you must set the
DYLD_FRAMEWORK_PATH to point to that location.  For example:  let's say that ossim home is located in /my/path/ossim and you linked to an ossim.framework located in the xcode Deploy build location, 
then:

export DYLD_FRAMEWORK_PATH=/my/path/ossim/xcode/ossim/build/Deploy

before you run any of the sample applications.  For desciption of the env variable can be found if you do a :
man 1 dyld


There are a couple of ways to run the example apps under bin/apps:


1.  In the base dir of the project:

     To run ImageViewerFrame:

java -cp bin/ apps.ImageViewerFrame /Library/WebServer/Documents/ajaxmaps/earth.tif

2.  Or if you want to package it up so you can run outside the project dir, use ant: 

    run 'ant dist' to package

    then just include jar on classpath and wrappers on library path:

java -cp dist/jossim.jar -Djava.library.path=dist/ apps.ImageViewerFrame <image file> 
