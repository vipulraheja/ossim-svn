%module jossim
%{
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
%}

%import "base.i"

%pragma(java) jniclassimports=%{
import jossim.base.ossimDpt;
import jossim.base.ossimGpt;
import jossim.base.ossimKeywordlist;
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

%typemap ( javaimports ) ossimProjection
%{
import jossim.base.ossimObject;	
import jossim.base.ossimGpt;	
import jossim.base.ossimDpt;	
%}	
class ossimProjection	 : public ossimObject
{
public:	
   /*!
    * METHOD: worldToLineSample()
    * Performs the forward projection from ground point to line, sample.
    */
   virtual void worldToLineSample(const ossimGpt& worldPoint,
                                  ossimDpt&       lineSampPt) const = 0;

   /*!
    * METHOD: lineSampleToWorld()
    * Performs the inverse projection from line, sample to ground (world):
    */
   virtual void lineSampleToWorld(const ossimDpt& lineSampPt,
                                  ossimGpt&       worldPt) const = 0;	
                                  
protected:
  ossimProjection();                                  
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


%typemap ( javaimports ) ossimProjectionFactoryRegistry 
%{
import jossim.base.ossimKeywordlist;	
import jossim.base.ossimObjectFactory;	
import jossim.projection.ossimProjection;	
%}	
class ossimProjectionFactoryRegistry : public ossimObjectFactory
{
public:
	static ossimProjectionFactoryRegistry* instance();
	
  virtual ossimProjection* createProjection(const ossimKeywordlist& kwl,
                                     const char* prefix=0)const;
		
protected:
	ossimProjectionFactoryRegistry();
};
