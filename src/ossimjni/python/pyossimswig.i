/* ----------------------------------------------------------------------------
// File: pyossim.i
// License: See top level LICENSE.txt file
// Author: Vipul Raheja
// Description: SWIG Module to build ossim-python bindings
//--------------------------------------------------------------------------- */

/* Start pyOSSIM Wrappers */
%module pyOssimWrappers
%{
#include <ossimjni/Constants.h>
#include <ossimjni/Info.h>
#include <ossimjni/Init.h>
#include <ossimjni/SingleImageChain.h>

#include <exception>
%}


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

/* This tells SWIG to treat char ** as a special case */
%typemap(in) char ** 
{
        /* Check if input is a list */
        if (PyList_Check($input)) 
        {
                int size = PyList_Size($input);
                int i = 0;
                
                /* Allocate memory */
                $1 = (char **) malloc((size+1)*sizeof(char *));
                
                for (i = 0; i < size; i++) 
                {
                        PyObject *o = PyList_GetItem($input,i);
                        
                        if (PyString_Check(o))
                        {
                                $1[i] = PyString_AsString(PyList_GetItem($input,i));
                        }

                        else 
                        {
                                PyErr_SetString(PyExc_TypeError,"List must contain strings");
                                free($1);
                                return NULL;
                        }
                }
                $1[i] = 0;
        } 
        
        else 
        {
                PyErr_SetString(PyExc_TypeError,"not a list");
                return NULL;
        }
}

/* To return char** from a C function as Python List */
%typemap(out) char**
{
        int i;
        int len = 0;

        while ($1[len])
        {
                len++;
        }

        $result = PyList_New(len);
        
        for (i = 0; i < len; i++) 
        {
                PyList_SetItem($result, i, PyString_FromString($1[i]));
        }
}


/* Include library header files */
%include <ossimjni/Constants.h>
%include <ossimjni/Info.h>
%include <ossimjni/Init.h>
%include <ossimjni/SingleImageChain.h>

%include "typemaps.i"


/* Typemaps to convert values from Python to C++ */
%typemap(in) ossimjni_int8
{
        $1 = PyString_AsString($input);
}

%typemap(in) ossimjni_int32
{
        $1 = PyInt_AsLong($input);
}

%typemap(in) ossimjni_int64
{
        $1 = PyLong_AsLongLong($input);
}

%typemap(in) ossimjni_uint64
{
        $1 = PyLong_AsUnsignedLongLong
}

%typemap(in) ossimjni_float64
{
        $1 = PyFloat_AsDouble($input);
}


/* Typemaps to convert from C++ to Python */
%typemap(out) ossimjni_int32
{
        $result = PyInt_FromLong((long) $1);
}

%typemap(out) ossimjni_int64
{
        $result = PyLong_FromLongLong($1);
}

%typemap(out) ossimjni_uint64
{
        $result = PyLong_FromUnsignedLongLong($1);
}

%typemap(out) ossimjni_float64
{
        $result = PyFloat_FromDouble($1);
}


/* Applying the typemaps to other basic primitives */
%apply ossimjni_int8 { ossimjni_sint8, ossimjni_uint8 };
%apply ossimjni_int32 { ossimjni_int16, ossimjni_uint16, ossimjni_uint16, ossimjni_uint32, ossimjni_sint32 };
%apply ossimjni_int64 { ossimjni_sint64 };
%apply ossimjni_float64 { ossimjni_float32 };
