/*-----------------------------------------------------------------------------
Filename        : ossimImageHandler.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageHandler 
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageMetaData.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimNBandLutDataObject.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/imaging/ossimFilterResampler.h>
#include <ossim/imaging/ossimImageHandler.h>

#include <vector>

%}

#ifndef TYPE_DATA
#define TYPE_DATA

/* Include the required header files */
%import "ossim/base/ossimConstants.h"

/* Handling the std::exception */
%include "exception.i"
%exception
{
        try
        {
                $action
        }
        catch(const std::exception& e)
        {
                SWIG_exception(SWIG_RuntimeError, e.what());
        }
}

/* Handling the vectors */
%include "std_vector.i"
namespace std
{
        %template(vectorossimIpt) vector<ossimIpt>;
        %template(vectorossimDpt) vector<ossimDpt>;
        %template(vectorossimUInt32) vector<ossim_uint32>;
        %template(vectorossimString) vector<ossimString>;
};


/**
 *  This class defines an abstract Handler which all image handlers(loaders)
 *  should derive from.
 */
%include "ossim/imaging/ossimImageHandler.h"

#endif
