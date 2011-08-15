%module pyossim

%{
#include <vector>

#include <ossim/base/ossimReferenced.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimRgbImage.h>
%}       

/* Wrapping the class */
%include "ossim/base/ossimConstants.h"
%include "ossim/imaging/ossimRgbImage.h"
