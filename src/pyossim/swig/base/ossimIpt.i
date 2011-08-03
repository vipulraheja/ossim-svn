/*-----------------------------------------------------------------------------
Filename        : ossimIpt.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimIpt
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimIpt.h>
%}

/* Handling operators */
%rename(__set__) ossimIpt::operator=;
%rename(__cmp__) ossimIpt::operator==;
%rename(__ne__) ossimIpt::operator!=;
%rename(__add__) ossimIpt::operator+;
%rename(__sub__) ossimIpt::operator-;
%rename(__mul__) ossimIpt::operator*;
%rename(__div__) ossimIpt::operator/;
%rename(__iadd__) ossimIpt::operator+=;
%rename(__isub__) ossimIpt::operator-=;
%rename(__lshift__) operator<<;
%rename(__rshift__) operator>>;

%rename(ossimIpt_print) print;

/* Wrapping class ossimIpt */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimIpt.h"
