/*-----------------------------------------------------------------------------
Filename        : ossimImageWriterFactory.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageWriterFactory
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageWriterFactoryBase.h>
#include <ossim/imaging/ossimImageWriterFactory.h>

%}        

/* Wrapping the class ossimImageWriterFactory */
%include "ossim/imaging/ossimImageWriterFactory.h"

