/*-----------------------------------------------------------------------------
 * Filename        : ossim2dTo2dShiftTransformi
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossim2dTo2dShiftTransform
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/base/ossim2dTo2dTransform.h>
#include <ossim/base/ossim2dTo2dShiftTransform.h>

%}

/* Handling operators */
%rename(__set__) ossim2dTo2dShiftTransform::operator=;
%rename(ossim2dTo2dShiftTransform_print) print;

/* Wrapping class ossim2dTo2dShiftTransform */
class ossim2dTo2dShiftTransform : public ossim2dTo2dTransform
{
        public:
                ossim2dTo2dShiftTransform(const ossimDpt& shift = ossimDpt(0.0,0.0))
                        :ossim2dTo2dTransform(),
                        m_shift(shift) {}
                ossim2dTo2dShiftTransform(const ossim2dTo2dShiftTransform& src)
                        :ossim2dTo2dTransform(src),
                        m_shift(src.m_shift) {}

                /**
                 * Duplication method that duplicates this object
                 */
                virtual ossimObject* dup()const{return new ossim2dTo2dShiftTransform(*this);}

                /**
                 * operator = allows one to copy the contents of the class through a common = 
                 * operator.  The = is passed to the derived class.
                 */
                const ossim2dTo2dShiftTransform& operator =(const ossim2dTo2dShiftTransform& src)
                {
                        if(this == &src) return *this;

                        ossim2dTo2dTransform::operator =(*this); // call base classes equal operator
                        m_shift = src.m_shift;

                        return *this;
                }

                virtual void forward(const ossimDpt& input,
                                ossimDpt& output) const
                {
                        output = input + m_shift;
                }                
                virtual void forward(ossimDpt&  modify_this) const
                {
                        modify_this.x += m_shift.x;
                        modify_this.y += m_shift.y;
                }


                virtual void inverse(const ossimDpt& input,
                                ossimDpt& output) const
                {
                        output = input - m_shift;
                }
                virtual void inverse(ossimDpt&  modify_this) const
                {
                        modify_this.x -= m_shift.x;
                        modify_this.y -= m_shift.y;
                }

                
                virtual bool saveState(ossimKeywordlist& kwl,
                                const char* prefix = 0)const;
                virtual bool loadState(const ossimKeywordlist& kwl,
                                const char* prefix = 0);

                /**
                 * Print the contents of the class and pass to the derived class.
                 */
                virtual std::ostream& print(std::ostream& out) const
                {
                        ossim2dTo2dTransform::print(out);

                        out << "shift: " << m_shift;

                        return out;
                }

        protected:
                virtual ~ossim2dTo2dShiftTransform(){}

                ossimDpt m_shift;

                /* Ignoring Macro
                TYPE_DATA; */
};
