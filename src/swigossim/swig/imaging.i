%module jossim
%{
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimSource.h>
#include <ossim/base/ossimString.h>
#include <ossim/imaging/ossimImageChain.h>
#include <ossim/imaging/ossimImageData.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageSource.h>
#include <ossim/imaging/ossimImageHandlerRegistry.h>
#include <ossim/imaging/ossimImageSourceFactoryRegistry.h>
#include <ossim/imaging/ossimImageHandler.h>
#include <ossim/imaging/ossimImageRenderer.h>
%}

%include "various.i"

%import "base.i"

%pragma(java) jniclassimports=%{
import jossim.base.ossimConnectableObject;
import jossim.base.ossimFilename;
import jossim.base.ossimIrect;
import jossim.base.ossimKeywordlist;
import jossim.base.ossimString;
%}

%typemap(javabody) SWIGTYPE %{
  protected long swigCPtr;
  protected boolean swigCMemOwn;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}

%typemap(javabody_derived) SWIGTYPE %{

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
	  super(cPtr,cMemoryOwn);
  }
%}

%include "arrays_java.i"

%typemap ( javaimports ) ossimImageData
%{
import jossim.base.ossimInterleaveType;	
import jossim.base.ossimIrect;	
%}

class ossimImageData
{
public:
   virtual ossim_uint32 getHeight()const;
   virtual ossim_uint32 getWidth()const;
   virtual ossim_uint32 getNumberOfBands() const;
//   virtual ossimString getScalarTypeAsString()const;
//   virtual ossimScalarType getScalarTypeFromString(const ossimString& s)const;
//   virtual ossim_uint8* getUcharBuf(ossim_uint32 band);
   
   

protected:
	ossimImageData();
};
//%extend ossimImageData {
//public:
//	virtual void unloadTile(char* BYTE, const ossimIrect& dest_rect, ossimInterleaveType il_type) const
//	{
//		self->unloadTile( (void*)BYTE, dest_rect, il_type );		
//	}                           
//}

%typemap ( javaimports ) ImagingUtil
%{
import jossim.base.ossimInterleaveType;
import jossim.base.ossimIrect;
%}

%inline 
%{
class ImagingUtil
{
public:
	static void unloadTile( const ossimRefPtr<ossimImageData>& tile, const ossimIrect& dest_rect, ossimInterleaveType il_type, char* BYTE)
	{
		tile->unloadTile( (void*)BYTE, dest_rect, il_type );		
	}
	
	static void unloadBand( const ossimRefPtr<ossimImageData>& tile, const ossimIrect& dest_rect, ossim_uint32 bandNum, char* BYTE)
	{
		tile->unloadBand( (void*)BYTE, dest_rect, bandNum );
	}
	
protected:
	ImagingUtil();
};	      
%}

%template( ossimImageDataRefPtr ) ossimRefPtr<ossimImageData>;

%typemap ( javaimports ) ossimImageSource
%{
import jossim.base.ossimScalarType;	
import jossim.base.ossimSource;
import jossim.base.ossimIrect;
import jossim.base.ossimStringVector;
import jossim.base.ossimKeywordlist;
%}
		

	
class ossimImageSource : public ossimSource
{
public:
   virtual ossim_uint32 getNumberOfOutputBands() const;
//   virtual ossim_uint32 getNumberOfDecimationLevels() const;
   virtual ossimScalarType getOutputScalarType() const;
   virtual ossimRefPtr<ossimImageData> getTile(const ossimIrect& rect,
                                   ossim_uint32 resLevel=0);
   virtual ossim_uint32 getTileWidth()const;
   virtual ossim_uint32 getTileHeight()const;
   virtual ossimIrect getBoundingRect(ossim_uint32 resLevel=0) const;
   
   virtual bool getImageGeometry(ossimKeywordlist& kwl,
                                 const char* prefix=0);
   
// 	virtual ossimRefPtr<ossimProperty> getProperty( const ossimString& name ) const;
// 	virtual void setProperty( ossimRefPtr<ossimProperty> property );
//	virtual void getPropertyNames( std::vector<ossimString>& propertyNames ) const;   
	
protected:
	ossimImageSource();
};	

%typemap ( javaimports ) ossimImageChain
%{
import jossim.base.ossimConnectableObject;	
%}
	
class ossimImageChain : public ossimImageSource
{
public:
	ossimImageChain();	
	bool addLast( ossimConnectableObject* obj );
	
protected:
	
};

%typemap(javabody) SWIGTYPE %{
  protected long swigCPtr;
  protected boolean swigCMemOwn;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}

%typemap(javabody_derived) SWIGTYPE %{

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
	  super(cPtr,cMemoryOwn);
  }
%}

%typemap ( javaimports ) ossimImageHandler
%{
import jossim.imaging.ossimImageSource;	
%}
	
class ossimImageHandler : public ossimImageSource
{
public:
//	virtual ossim_uint32 getImageTileWidth() const = 0;
//	virtual ossim_uint32 getImageTileHeight() const = 0;	
//	virtual ossim_uint32 getNumberOfInputBands();
//	virtual ossim_uint32 getNumberOfLines(ossim_uint32 reduced_res_level = 0) const = 0;
//	virtual ossim_uint32 getNumberOfSamples(ossim_uint32 reduced_res_level = 0) const = 0;
	virtual bool isOpen()const=0;
	
	virtual ossim_uint32 	getNumberOfEntries () const;
	virtual ossim_uint32 getNumberOfReducedResSets() const;
	virtual bool setCurrentEntry (ossim_uint32 entryIdx);
	
	virtual void close() = 0;
	
protected:
	ossimImageHandler();
};

%typemap(javabody) SWIGTYPE %{
  protected long swigCPtr;
  protected boolean swigCMemOwn;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}

%typemap(javabody_derived) SWIGTYPE %{

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
	 super(cPtr,cMemoryOwn);
  }
%}

%typemap(javaimports) ossimImageHandlerRegistry
%{
import jossim.base.ossimFilename;	
import jossim.base.ossimObjectFactory;
import jossim.imaging.ossimImageHandler;	
%}	
class ossimImageHandlerRegistry : public ossimObjectFactory
{
public:
	static ossimImageHandlerRegistry* instance();
   	ossimImageHandler* open(const ossimFilename& fileName)const;

protected:
	ossimImageHandlerRegistry();
};


%typemap(javaimports) ossimImageSourceFactoryRegistry
%{
import jossim.base.ossimString;	
import jossim.base.ossimObjectFactory;
import jossim.imaging.ossimImageSource;	
%}	

class ossimImageSourceFactoryRegistry : public ossimObjectFactory
{
public:
	static ossimImageSourceFactoryRegistry* instance();
	virtual ossimImageSource* createImageSource( const ossimString& className ) const;
	
protected:
	ossimImageSourceFactoryRegistry();	
};

%include "various.i"

%typemap(javabody) SWIGTYPE %{
  protected long swigCPtr;
  protected boolean swigCMemOwn;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}



