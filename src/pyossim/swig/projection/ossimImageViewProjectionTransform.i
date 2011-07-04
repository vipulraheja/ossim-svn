/*-----------------------------------------------------------------------------
 * Filename        : ossimImageViewProjectionTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageViewProjectionTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimImageViewTransform.h>
#include <ossim/projection/ossimImageViewProjectionTransform.h>
#include <ossim/imaging/ossimImageGeometry.h>

%}

class ossimImageViewProjectionTransform : public ossimImageViewTransform
{
        public:
                ossimImageViewProjectionTransform(ossimImageGeometry* imageGeometry=0,
                                ossimImageGeometry* viewGeometry=0);

                ossimImageViewProjectionTransform(const ossimImageViewProjectionTransform& src);

                virtual ossimObject* dup() const { return new ossimImageViewProjectionTransform(*this); }
                virtual ~ossimImageViewProjectionTransform();

                virtual bool isValid() const { return (m_imageGeometry.valid() && m_viewGeometry.valid()); }

                virtual bool isIdentity() const { return (m_imageGeometry == m_viewGeometry); }

                void setViewGeometry(ossimImageGeometry* g) { m_viewGeometry = g; }   

                void setImageGeometry(ossimImageGeometry* g) { m_imageGeometry = g; }  

                virtual void imageToView(const ossimDpt& imagePoint, ossimDpt& viewPoint) const;

                virtual void viewToImage(const ossimDpt& viewPoint, ossimDpt& imagePoint) const;

                virtual std::ostream& print(std::ostream& out) const;

                ossimImageGeometry* getImageGeometry()  { return m_imageGeometry.get(); }
                ossimImageGeometry* getViewGeometry()   { return m_viewGeometry.get(); }
                const ossimImageGeometry* getImageGeometry()const  { return m_imageGeometry.get(); }
                const ossimImageGeometry* getViewGeometry()const   { return m_viewGeometry.get(); }

                virtual bool setView(ossimObject* baseObject);
                virtual       ossimObject* getView()       { return m_viewGeometry.get(); }
                virtual const ossimObject* getView() const { return m_viewGeometry.get(); }

                virtual ossimDpt getInputMetersPerPixel()const;

                virtual ossimDpt getOutputMetersPerPixel() const;

                virtual ossimDrect getImageToViewBounds(const ossimDrect& imageRect)const;

                virtual bool loadState(const ossimKeywordlist& kwl, const char* prefix =0);

                virtual bool saveState(ossimKeywordlist& kwl, const char* prefix = 0)const;

        protected:
                ossimRefPtr<ossimImageGeometry> m_imageGeometry;
                ossimRefPtr<ossimImageGeometry> m_viewGeometry;

                TYPE_DATA
};
