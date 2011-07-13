/*-----------------------------------------------------------------------------
 * Filename        : ossimDatumFactory.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDatumFactory
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimDatumFactoryInterface.h>
#include <ossim/base/ossimDatumFactory.h>
#include <ossim/base/ossimEllipsoidFactory.h>
#include <ossim/base/ossimString.h>

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

/* Handling the templates */
%include "std_vector.i"
%include "std_string.i"
namespace std
{
        %template(vectorossimString) vector<ossimString>;
};


/* Wrapping the class class ossimDatumFactory */
class ossimDatumFactory : public ossimDatumFactoryInterface
{
        public:

                /** virtual destructor */
                virtual ~ossimDatumFactory();

                /**
                 * create method
                 *
                 * Implements pure virtual ossimDatumFactoryInterface::create.
                 *
                 * @return const pointer to a datum.
                 */
                virtual const ossimDatum* create(const ossimString &code)const;
                virtual const ossimDatum* create(const ossimKeywordlist& kwl, const char *prefix=0)const;

                const ossimDatum* create(const ossimDatum* copy) const;

                static ossimDatumFactory* instance();
 
                const ossimDatum* wgs84()const{return theWgs84Datum;}
                const ossimDatum* wgs72()const{return theWgs72Datum;}
                
                std::vector<ossimString> getList()const;
                
                virtual void getList(std::vector<ossimString>& list)const;
                void writeCStructure(const ossimFilename& file);

        protected:
                static ossimDatumFactory*       theInstance;
                const ossimDatum*               theWgs84Datum;
                const ossimDatum*               theWgs72Datum;
                
                std::map<std::string, const ossimDatum*> theDatumTable;


                ossimDatumFactory()
                        :theWgs84Datum(0),
                        theWgs72Datum(0) {}

                void deleteAll();
                void initializeDefaults();
};
