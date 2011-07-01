/*-----------------------------------------------------------------------------
Filename        : init.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimInit which handles 
all aspects of initialization for OSSIM applications.
-----------------------------------------------------------------------------*/

%module pyossim

%{
#include <ossim/init/ossimInit.h>
%}

%include "typemaps.i"

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

/* Wrapping class ossimInit */
class ossimInit
{
        public:
                ~ossimInit();

                static ossimInit* instance();

                void initialize(int& argc, char** argv);

                void finalize();

                void usage();

        protected:
                ossiminit();
};

/* Methods left out 
public:
   void addOptions(ossimArgumentParser& parser);
   void initialize(ossimArgumentParser& parser);
   bool getElevEnabledFlag() const;
   void setElevEnabledFlag(bool flag);
   void setPluginLoaderEnabledFlag(bool flag);
   void loadPlugins(const ossimFilename& plugin, const char* options=0);

   void initializePlugins();
   void initializeDefaultFactories();
   void initializeElevation();

   void initializeLogFile();

   ossimString version() const;

   ossimFilename appName()const;

protected:
   ossimInit(const ossimInit& obj);
   void operator=(const ossimInit& rhs) const;
   void parseOptions(ossimArgumentParser& parser);
   void parseNotifyOption(ossimArgumentParser& parser);
   void removeOption(int&   argc, 
   char** argv,
   int    argToRemove);

   static ossimInit*  theInstance;
   bool               theInitializedFlag; 
   ossimFilename      theAppName;
   ossimPreferences*  thePreferences;
   bool               theElevEnabledFlag;
   bool               thePluginLoaderEnabledFlag;
*/
