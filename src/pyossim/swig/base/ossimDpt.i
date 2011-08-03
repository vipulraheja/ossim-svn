/*-----------------------------------------------------------------------------
Filename        : ossimHistogramRemapper.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimHistogramRemapper 
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimDpt.h>
%}

/* Handling operators */
%rename(__cmp__) ossimDpt::operator==;
%rename(__set__) ossimDpt::operator=;
%rename(__ne__) ossimDpt::operator!=;
%rename(__add__) ossimDpt::operator+;
%rename(__sub__) ossimDpt::operator-;
%rename(__mul__) ossimDpt::operator*;
%rename(__div__) ossimDpt::operator/;
%rename(__iadd__) ossimDpt::operator+=;
%rename(__isub__) ossimDpt::operator-=;

%rename(__lshift__) operator<<;
%rename(__rshift__) operator>>;
%rename(ossimDpt_print) print;


/* Wrapping class ossimDpt */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimDpt.h"
