/*-----------------------------------------------------------------------------
 * Filename        : ossimDataObject.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDataObject
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimDataObject.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimDpt3d.h>

%}

/* OPERATORS */
/* Handling operators */
%rename(__cmp__) ossimDataObject::operator==;
%rename(__set__) ossimDataObject::operator=;
%rename(__ne__) ossimDataObject::operator!=;
%rename(ossimDataObject_print) print;

/* Wrapping class ossimDataObject */
class ossimDataObject : public ossimObject
{
        public:
                ossimDataObject(ossimSource* source=0,
                                ossimDataObjectStatus status=OSSIM_STATUS_UNKNOWN);

                ossimDataObject(const ossimDataObject& rhs);
                virtual ~ossimDataObject();

                virtual ossim_uint32 getHashId()const=0;

                /**
                 * Sets the owner of this Data object.
                 */
                virtual void setOwner(ossimSource* aSource);

                virtual ossimSource* getOwner();

                virtual const ossimSource* getOwner() const;

                /**
                 * Full list found in ossimConstants.h
                 *
                 * OSSIM_STATUS_UNKNOWN
                 * OSSIM_NULL            Null data.  The buffers are never allocated
                 * OSSIM_EMPTY           Allocated data but its empty.  Most of the
                 *                       time this will be the default for an initialized
                 *                       data object.
                 * OSSIM_PARTIAL         Says that some of the object is empty and is only
                 *                       partially full
                 * OSSIM_FULL            This data is completey full
                 */
                virtual void  setDataObjectStatus(ossimDataObjectStatus status) const;

                /**
                 * @return Returns enumerated status:
                 * OSSIM_STATUS_UNKNOWN = 0
                 * OSSIM_NULL           = 1
                 * OSSIM_EMPTY          = 2
                 * OSSIM_PARTIAL        = 3
                 * OSSIM_FULL           = 4
                 */
                virtual ossimDataObjectStatus getDataObjectStatus() const;

                /**
                 * @return Returns the status as a string, like "OSSIM_NULL".
                 */
                virtual ossimString getDataObjectStatusString() const;

                virtual ossim_uint32 getObjectSizeInBytes()const;

                virtual ossim_uint32 getDataSizeInBytes()const=0;

                /**
                 * This is to be overriden in the derived classes so they can check
                 * If their data is null.
                 */
                virtual bool isInitialize() const;

                /**
                 * Will allow derived classes to initialize their buffers.  This class
                 * does nothing with this and reset any internal attributes.
                 */
                virtual void initialize()=0;

                virtual void assign(const ossimDataObject* rhs);

                virtual bool isEqualTo(const ossimDataObject& rhs,
                                bool deepTest=false)const=0;

                virtual const ossimDataObject* operator =(const ossimDataObject* rhs);

                virtual const ossimDataObject& operator=(const ossimDataObject& rhs);

                virtual bool operator==(const ossimDataObject& rhs) const;
                virtual bool operator!=(const ossimDataObject& rhs) const;

                virtual std::ostream& print(std::ostream& out) const;

        protected:
                ossimSource*                      theOwner;
                mutable ossimDataObjectStatus     theDataObjectStatus;

                /* Ignoring Macro 
                TYPE_DATA */
};
