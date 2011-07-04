/*-----------------------------------------------------------------------------
 * Filename        : ossimImageViewAffineTransform.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageViewAffineTransform 
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/projection/ossimImageViewTransform.h>
#include <ossim/projection/ossimImageViewAffineTransform.h>
#include <ossim/matrix/newmat.h>

%}

class ossimImageViewAffineTransform: public ossimImageViewTransform
{
        public:
                ossimImageViewAffineTransform(double rotateDegrees = 0,
                                double scaleXValue = 1,
                                double scaleYValue = 1,
                                double translateXValue = 0,
                                double translateYValue = 0,
                                double pivotXValue = 0,
                                double pivotYValue = 0);
                virtual ~ossimImageViewAffineTransform();

                ossimImageViewAffineTransform(const ossimImageViewAffineTransform& src)
                        :ossimImageViewTransform(src),
                        m_transform(src.m_transform),
                        m_inverseTransform(src.m_inverseTransform),
                        m_rotation(src.m_rotation),
                        m_scale(src.m_scale),
                        m_translate(src.m_translate),
                        m_pivot(src.m_pivot)
        {
        }
                virtual ossimObject* dup()const
                {
                        return new ossimImageViewAffineTransform(*this);
                }

                virtual void imageToView(const ossimDpt& imagePoint,
                                ossimDpt&       viewPoint)const;
                virtual void viewToImage(const ossimDpt& viewPoint,
                                ossimDpt&       imagePoint)const;
                void setMatrix(NEWMAT::Matrix& matrix);
                const NEWMAT::Matrix& getMatrix()const;

                virtual bool isIdentity()const
                {
                        return ((m_transform[0][0] == 1.0)&&
                                        (m_transform[0][1] == 0.0)&&
                                        (m_transform[0][2] == 0.0)&&
                                        (m_transform[1][0] == 0.0)&&
                                        (m_transform[1][1] == 1.0)&&
                                        (m_transform[1][2] == 0.0)&&
                                        (m_transform[2][0] == 0.0)&&
                                        (m_transform[2][1] == 0.0)&&
                                        (m_transform[2][2] == 1.0));
                }

                virtual bool isValid()const;
                virtual bool setView(ossimObject* obj);
                virtual ossimObject* getView();
                virtual const ossimObject* getView()const;

                virtual ossimDpt getInputMetersPerPixel()const;
                virtual ossimDpt getOutputMetersPerPixel()const;

                virtual void translate(double deltaX, double deltaY);
                virtual void translateX(double deltaX);
                virtual void translateY(double deltaY);

                virtual void pivot(double originX, double originY);
                virtual void pivotX(double originX);
                virtual void pivotY(double originY);

                virtual void scale(double x, double y);
                virtual void scaleX(double x);
                virtual void scaleY(double y);

                virtual void rotate(double degrees);

                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix =0);
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix =0)const;

        protected:
                void buildCompositeTransform();

                NEWMAT::Matrix m_transform;
                NEWMAT::Matrix m_inverseTransform;
                ossim_float64 m_rotation;
                ossimDpt      m_scale;
                ossimDpt      m_translate;
                ossimDpt      m_pivot;

                TYPE_DATA
};
