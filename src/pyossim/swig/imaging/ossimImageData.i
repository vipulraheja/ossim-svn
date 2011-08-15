%module pyossim

%{
#include <vector>
#include <iosfwd> /* for ostream */
#include <ossim/imaging/ossimImageData.h>
#include <ossim/base/ossimMultiBandHistogram.h>
%}

#ifndef TYPE_DATA   
#define TYPE_DATA

%rename(ossimImageData_print) print;
%rename(__set__) ossimImageData::operator=;

/* Wrapping the class */
%include "ossim/base/ossimConstants.h"
%include "ossim/imaging/ossimImageData.h"

#endif
