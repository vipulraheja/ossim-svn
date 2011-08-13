%module pyossimtest

%{

#include <pyossimtest/Constants.h>
#include <pyossimtest/Info.h>
#include <pyossimtest/Init.h>
#include <pyossimtest/SingleImageChain.h>

#include <exception>

%}

/* Handling exception */
%include <exception.i>
%exception
{
        try
        {
                $action
        }
        catch (const std::exception& e)
        {
                SWIG_exception(SWIG_RuntimeError, e.what());
        }
}


/* Including classes */
%include <pyossimtest/Constants.h>
%include <pyossimtest/Info.h>
%include <pyossimtest/Init.h>
%include <pyossimtest/SingleImageChain.h>
