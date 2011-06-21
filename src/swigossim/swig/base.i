%module jossim
%{
#include <ossim/base/ossimConnectableObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimGpt.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimIrect.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimObjectFactory.h>
#include <ossim/base/ossimProperty.h>
#include <ossim/base/ossimPropertyInterface.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimSource.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimRefPtr.h>
#include <vector>
#include <string>
%}


template<class T> class ossimRefPtr
{
public:
	T* operator->();
	bool valid() const;
	T* get();	
};

%include "std_vector.i"

%include <ossim/base/ossimConstants.h>	

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


class ossimObject
{
 public:

 protected:
   ossimObject();
};


%typemap ( javaimports ) ossimPropertyInterface
%{
import jossim.base.ossimString;	
import jossim.base.ossimStringVector;	
import jossim.base.ossimPropertyRefPtr;	
import jossim.base.ossimPropertyRefPtrVector;	
%}	
class ossimPropertyInterface
{
public:
   virtual void setProperty(const ossimString& name,
                            const ossimString& value);
                            
	virtual void setProperty(ossimRefPtr<ossimProperty> property);
	virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
	virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;
	void getPropertyList(std::vector<ossimRefPtr<ossimProperty> >& propertyList)const;
	void setProperties(std::vector<ossimRefPtr<ossimProperty> >& propertyList);
   
protected:
     ossimPropertyInterface();
};

%typemap ( javaimports ) ossimConnectableObject
%{
import jossim.base.ossimString;	
import jossim.base.ossimStringVector;	
import jossim.base.ossimPropertyRefPtr;	
import jossim.base.ossimPropertyRefPtrVector;	
%}	
class ossimConnectableObject : public ossimPropertyInterface
{
protected:
   ossimConnectableObject();
   
public:
	virtual ossim_int32 connectMyInputTo(ossimConnectableObject* inputObject,
                                        bool makeOutputConnection=true,
                                        bool createEventFlag=true);	     
                                                                    
	virtual void setProperty(ossimRefPtr<ossimProperty> property);
	virtual ossimRefPtr<ossimProperty> getProperty(const ossimString& name)const;
	virtual void getPropertyNames(std::vector<ossimString>& propertyNames)const;
	void getPropertyList(std::vector<ossimRefPtr<ossimProperty> >& propertyList)const;
	void setProperties(std::vector<ossimRefPtr<ossimProperty> >& propertyList);                                        
};

class ossimSource : public ossimConnectableObject
{
public:
	virtual void initialize();
	
protected:
    ossimSource();
};

%include "std_vector.i"
%include "std_string.i"

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

class ossimString
{
public:
	ossimString();
    ossimString(const char*);
};
%extend ossimString {
public:	
	std::string toString()
	{
		return self->c_str();
	}
};

namespace std
{
	%template(ossimStringVector) vector<ossimString>; 
}


class ossimFilename : public ossimString
{
public:
	ossimFilename(const char* src);	
};

%typemap ( javaimports ) ossimIrect
%{
import jossim.base.ossimCoordSysOrientMode;
import jossim.base.ossimIpt;	
%}
	
	
class ossimIpt
{
public:
	ossimIpt(ossim_int32 anX, ossim_int32 aY);
	ossim_int32 x;
	ossim_int32 y;
};
		
class ossimIrect
{
public:
   ossimIrect(ossim_int32 ul_corner_x,
              ossim_int32 ul_corner_y,
              ossim_int32 lr_corner_x,
              ossim_int32 lr_corner_y,
              ossimCoordSysOrientMode mode=OSSIM_LEFT_HANDED);
              
	ossimIpt ul() const;
	ossimIpt ur() const; 
	ossimIpt lr() const; 
	ossimIpt ll() const; 

	ossim_uint32 width() const;
	ossim_uint32 height() const;
	
	 
};


class ossimKeywordlist
{
public:
  ossimKeywordlist(char delimiter = DEFAULT_DELIMITER);

  ossimKeywordlist(const char*     file,
               char            delimiter = DEFAULT_DELIMITER,
               bool            ignoreBinaryChars = false);

   ossimKeywordlist(const ossimFilename& fileName,
               char            delimiter = DEFAULT_DELIMITER,
               bool            ignoreBinaryChars = false);


   /*!
    *  Reads file and adds keywords to the KeywordMap.
    *  Returns true if file was parsed, false on error.
    */
   bool addFile(const char* file);

   /*!
    *  Reads file and adds keywords to the KeywordMap.
    *  Returns true if file was parsed, false on error.
    */
   bool addFile(const ossimFilename& file);

  // Methods to add keywords to list.
   void add(const char*   key,
            const char*   value,
            bool          overwrite = true);

   void add(const char*   prefix,
            const char*   key,
            const char*   value,
            bool          overwrite = true);



   const char* find(const char* key) const;
   const char* find(const char* prefix,
                    const char* key) const;

   void remove(const char * key);
   void remove(const char* prefix, const char * key);
   
   void clear();
   
  /**
    * Methods to dump the ossimKeywordlist to a file on disk.
    * @return true on success, false on error.
    */
   bool write(const char* file) const;   	
};

%extend ossimKeywordlist {
public:	
	std::string toString()
	{
		return self->toString();
	}
};

class ossimGpt
{
public:
   /*!
    * Constructor.  The values are assumed to be in DEGREES.
    */
   ossimGpt(double lat, double lon);
            
   /*!
    * Will convert the radian measure to degrees.
    */
   double latd() const;
            
   /*!
    * Will convert the radian measure to degrees.
    */
   double lond() const;
};   

class ossimDpt
{
public:
	ossimDpt(double anX, double aY);
	ossimDpt(const ossimIpt& pt);
	double x;
	double y;
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

%typemap( javaimports ) ossimObjectFactory
%{
import jossim.base.ossimObject;	
import jossim.base.ossimString;
import jossim.base.ossimStringVector;
import jossim.base.ossimKeywordlist;	
%}	
class ossimObjectFactory : public ossimObject
{
public:
 
   /*!
    * Creates an object given a type name.
    */
   virtual ossimObject* createObject(const ossimString& typeName)const=0;

   /*!
    * Creates and object given a keyword list.
    */
   virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                     const char* prefix=0)const=0;

   /*!
    * This should return the type name of all objects in all factories.
    * This is the name used to construct the objects dynamially and this
    * name must be unique.
    */
   virtual void getTypeNameList(std::vector<ossimString>& typeList)const=0;

protected:
	ossimObjectFactory();
};

%include "various.i"
%include "std_vector.i"
%include "std_string.i"

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

%typemap ( javaimports ) ossimProperty
%{
import jossim.base.ossimString;	
%}

class ossimProperty
{
public:
//	const ossimString& getName() const;	
//	virtual ossimString valueToString() const;
//	virtual bool setValue( const ossimString& value );

protected:
	ossimProperty();
};		

%template( ossimPropertyRefPtr ) ossimRefPtr<ossimProperty>;

%typemap ( javaimports ) PropertyUtil
%{
import jossim.base.ossimString;	
%}
%inline 
%{
class PropertyUtil
{
public:
	static const std::string& getName( const ossimRefPtr<ossimProperty>& property ) 
	{
		return property->getName();
	}
	static const std::string& getValue( const ossimRefPtr<ossimProperty>& property ) 
	{
		return property->valueToString();
	}
	static bool setValue( ossimRefPtr<ossimProperty>& property, const std::string& value )
	{
		return property->setValue( value );
	}
	
protected:
	PropertyUtil();
};	      
%}

namespace std
{
	%template(ossimPropertyRefPtrVector) vector<ossimRefPtr<ossimProperty> >; 
}
