/*-----------------------------------------------------------------------------
Filename        : ossimInit.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimInit which handles 
                  all aspects of initialization for OSSIM applications.
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/init/ossimInit.h>
#include <ossim/base/ossimFilename.h>        
#include <ossim/base/ossimConstants.h>

%}

%include "typemaps.i"

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


/* Handling Init Assignment operator */
%rename(__setattr__) ossimInit::operator=;


/* Include the header file containing the declarations to be wrapped */
%import "ossim/base/ossimConstants.h"

%include "ossim/init/ossimInit.h"
