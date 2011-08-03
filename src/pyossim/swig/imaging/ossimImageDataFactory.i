/*-----------------------------------------------------------------------------
Filename        : ossimImageDataFactory.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageDataFactory
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimSource.h>
#include <OpenThreads/Mutex>

#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimImageDataFactory.h>

%}

#ifndef OSSIM_DLL
#define OSSIM_DLL

/* Handling ossimImageDataFactory assignment operator */
%rename(__set__) ossimImageDataFactory::operator=; 

%include "ossim/imaging/ossimImageDataFactory.h"

#endif
