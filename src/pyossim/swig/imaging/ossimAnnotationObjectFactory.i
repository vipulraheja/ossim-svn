%module pyossim

%{
#include <ossim/base/ossimFactoryBaseTemplate.h>
#include <ossim/imaging/ossimAnnotationObject.h>
#include <ossim/imaging/ossimAnnotationObjectFactory.h>
%}

/* wrapping class */
%include "ossim/base/ossimConstants.h"
%include "ossim/imaging/ossimAnnotationObjectFactory.h" 
