/*-----------------------------------------------------------------------------
Filename        : ossimImageDataFactory.i
Author          : Vipul Raheja
License         : See top level LICENSE.txt file.
Description     : Contains SWIG-Python of class ossimImageDataFactory
-----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimImageDataFactory.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimSource.h>
#include <OpenThreads/Mutex>

%}

/* Handling ossimImageDataFactory assignment operator */
%rename(__set__) ossimImageDataFactory::operator=; 

/*!
 * This factory should be called by all image source producers to allocate
 * an image tile.
 */
class ossimImageDataFactory
{
        public:
                virtual ~ossimImageDataFactory();
                static ossimImageDataFactory* instance();

                virtual ossimRefPtr<ossimImageData> create(ossimSource* owner,
                                ossimScalarType scalar,
                                ossim_uint32 bands = 1)const;

                virtual ossimRefPtr<ossimImageData> create(ossimSource* owner,
                                ossimScalarType scalar,
                                ossim_uint32 bands,
                                ossim_uint32 width,
                                ossim_uint32 height)const;

                virtual ossimRefPtr<ossimImageData> create(
                                ossimSource* owner,
                                ossim_uint32 bands,
                                ossimImageSource* inputSource)const;


                virtual ossimRefPtr<ossimImageData> create(
                                ossimSource* owner,
                                ossimImageSource* inputSource)const;

        protected:
                ossimImageDataFactory();                                // hide
                ossimImageDataFactory(const ossimImageDataFactory&) {}  //hide
                void operator= (ossimImageDataFactory&) {}              // hide

                static ossimImageDataFactory* theInstance;
                static OpenThreads::Mutex theInstanceMutex;
};
