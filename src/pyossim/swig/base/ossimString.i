/*-----------------------------------------------------------------------------
 * Filename        : ossimString.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimString
 * -----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/base/ossimString.h>
%}

/* OPERATOR () left */

/* Handling ossimHistogramRemapper assignment operator */
%rename(__set__) ossimString::operator=;
%rename(__iadd__) ossimString::operator+=;
%rename(__ne__) ossimString::operator!=;
%rename(__getitem__) ossimString::operator[];
%rename(__eq__) operator==;
%rename(__add__) operator+;
%rename(__rshift__) operator>>;
%rename(__lshift__) operator<<;

/* Wrapping the class ossimString */
%include "ossim/base/ossimConstants.h"
%include "ossim/base/ossimString.h"
