#!/bin/tcsh
set MOC=moc
set UIC=uic
if (! -d .ui ) then
    mkdir .ui
endif
if (! -d .moc ) then
    mkdir .moc
endif

set UI_FILES=`find ./src -name "*.ui"`
foreach f ( $UI_FILES )
set basename=`basename -s .ui $f`
set pathname=`dirname $f`
echo "uic $f -o .ui/$basename.h"
uic $f -o ".ui/$basename.h"
echo "uic $f -i .ui/$basename.h -o .ui/$basename.cpp"
uic $f -i .ui/$basename.h -o .ui/$basename.cpp
echo $MOC .ui/$basename.h -o ".moc/moc_$basename.cpp"
$MOC .ui/$basename.h -o ".moc/moc_$basename.cpp"
end

set MOC_FILES=`find ./src -name "*.h"`
foreach f ( $MOC_FILES )
set grepresult=`grep Q_OBJECT $f`
if ("$grepresult" != "") then
    set basename=`basename -s .h $f`
    set pathname=`dirname $f`
    echo $MOC $f -o ".moc/moc_$basename.cpp"
    $MOC $f -o ".moc/moc_$basename.cpp"
endif

end

echo "Embedding images..."

set IMAGES="images/filenew images/fileopen images/filesave images/print images/undo images/redo images/editcut images/editcopy images/editpaste images/searchfind images/display images/datastore images/fingerup images/dataextract images/alignbottom images/alignleft images/alignright images/aligntop images/tilecascade images/connection images/resetproperty images/ImageLinkerSplash images/Splash.png images/iviewsplash"

echo "uic -embed $1 $IMAGES -o .ui/qmake_image_collection.cpp"

uic -embed $1 $IMAGES -o .ui/qmake_image_collection.cpp


