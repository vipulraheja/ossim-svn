/*-----------------------------------------------------------------------------
 * Filename        : ossimImageData.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageData 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <vector>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimObject.h>
#include <ossim/base/ossimDpt.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/base/ossimRtti.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/projection/ossimProjection.h>
#include <ossim/base/ossim2dTo2dTransform.h>

#include <ossim/include/ossimImageGeometry.h>

%}

class ossimImageGeometry : public ossimObject
{
        public:
                ossimImageGeometry();
                virtual ~ossimImageGeometry();

                ossimImageGeometry(const ossimImageGeometry& copy_this);

                ossimImageGeometry(ossim2dTo2dTransform* transform, ossimProjection* projection);

                void rnToRn(const ossimDpt& inRnPt, ossim_uint32 inResolutionLevel,
                                ossim_uint32 outResolutionLevel,ossimDpt& outRnPt) const;

                void rnToFull(const ossimDpt& rnPt, ossim_uint32 resolutionLevel, ossimDpt& fullPt) const;

                void fullToRn(const ossimDpt& fullPt, ossim_uint32 resolutionLevel, ossimDpt& rnPt) const;

                void rnToWorld(const ossimDpt& rnPt, ossim_uint32 resolutionLevel, ossimGpt& wpt) const;

                void worldToRn(const ossimGpt& wpt, ossim_uint32 resolutionLevel, ossimDpt& rnPt) const;

                bool localToWorld(const ossimDpt& local_pt, ossimGpt& world_pt) const;

                bool worldToLocal(const ossimGpt& world_pt, ossimDpt& local_pt) const;

                void setTransform(ossim2dTo2dTransform* transform);

                void setProjection(ossimProjection* projection);

                const ossim2dTo2dTransform* getTransform() const { return m_transform.get(); }
                ossim2dTo2dTransform*       getTransform()       { return m_transform.get(); }

                const ossimProjection* getProjection() const { return m_projection.get(); }
                ossimProjection*       getProjection()       { return m_projection.get(); }

                bool hasProjection() const { return m_projection.valid(); }

                bool hasTransform() const { return m_transform.valid(); }

                bool isAffectedByElevation() const;

                const ossimDpt& getMetersPerPixel() const;

                bool getCornerGpts(ossimGpt& ul, ossimGpt& ur, ossimGpt& lr, ossimGpt& ll) const;

                std::ostream& print(std::ostream& out) const;

                bool operator==(const ossimImageGeometry& compare_this) const;

                const ossimImageGeometry& operator=(const ossimImageGeometry& copy_this);

                ossimDpt decimationFactor(ossim_uint32 r_index) const;

                void decimationFactor(ossim_uint32 r_index, ossimDpt& result) const;

                void decimationFactors(std::vector<ossimDpt>& decimations) const;

                void setDiscreteDecimation(const std::vector<ossimDpt>& decimation_list) 
                {
                        m_decimationFactors = decimation_list;
                }

                ossim_uint32 getNumberOfDecimations()const
                {
                        return (ossim_uint32)m_decimationFactors.size();
                }
                
                void setImageSize(const ossimIpt& size)
                {
                        m_imageSize = size;
                }
                
                const ossimIpt& getImageSize()const
                {
                        return m_imageSize;
                }
                
                virtual ossimObject* dup() const { return new ossimImageGeometry(*this); }

                virtual bool loadState(const ossimKeywordlist& kwl, const char* prefix=0);

                virtual bool saveState(ossimKeywordlist& kwl, const char* prefix=0) const;

                void setTargetRrds(ossim_uint32 rrds);

                ossim_uint32 getTargetRrds() const;

                void computeGsd()const;


        protected:
                void undecimatePoint(const ossimDpt& rnPt,
                                ossim_uint32 resolutionLevel,
                                ossimDpt& outPt) const;

                void decimatePoint(const ossimDpt& inPt,
                                ossim_uint32 resolutionLevel,
                                ossimDpt& rnPt) const;

                ossimRefPtr<ossim2dTo2dTransform> m_transform;          //!< Maintains local_image-to-full_image transformation 
                ossimRefPtr<ossimProjection>      m_projection;         //!< Maintains full_image-to-world_space transformation
                mutable ossimDpt                  m_gsd;                //!< meters per pixel
                std::vector<ossimDpt>             m_decimationFactors;  //!< List of decimation factors for R-levels
                ossimIpt                          m_imageSize;          // Image width and height

                /** @brief Target rrds for localToWorld and worldToLocal methods. */
                ossim_uint32                      m_targetRrds; 

                TYPE_DATA
};
