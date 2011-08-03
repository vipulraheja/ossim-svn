/*-----------------------------------------------------------------------------
 * Filename        : ossimImageElevationHandler.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageElevationHandler
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/elevation/ossimElevCellHandler.h>
#include <ossim/elevation/ossimImageElevationHandler.h>
#include <ossim/base/ossimDrect.h>
#include <ossim/base/ossimIpt.h>
#include <ossim/imaging/ossimImageGeometry.h>
#include <ossim/imaging/ossimImageHandler.h>

%}


/* Wrapping class ossimImageElevationHandler */
class ossimImageElevationHandler : public ossimElevCellHandler
{
public:
   ossimImageElevationHandler();

   virtual double getHeightAboveMSL(const ossimGpt&);
   
   virtual ossimIpt getSizeOfElevCell() const;
      
   /**
    *  METHOD:  getPostValue
    *  Returns the value at a given grid point as a double.
    *  Satisfies pure virtual.
    */
   virtual double getPostValue(const ossimIpt& gridPt) const;

   /** @return True if open, false if not. */
   virtual bool isOpen()const;
   
   /**
    * Opens a stream to the srtm cell.
    *
    * @return Returns true on success, false on error.
    */
   virtual bool open(const ossimFilename& file);

   /** @brief Closes the stream to the file. */
   virtual void close();

   /**
    * @brief pointHasCoverage(gpt)
    *
    * Overrides ossimElevCellHandler::pointHasCoverage
    * @return TRUE if coverage exists over gpt.
    */
   virtual bool pointHasCoverage(const ossimGpt&) const;

protected:
   /**
    * @Brief Protected destructor.
    *
    * This class is derived from ossimReferenced so users should always use
    * ossimRefPtr<ossimImageElevationHandler> to hold instance.
    */
   virtual ~ossimImageElevationHandler();
   
private:

   /** Hidden from use copy constructor */
   ossimImageElevationHandler(const ossimImageElevationHandler&);
   
   /** Hidden from use assignment operator */
   const ossimImageElevationHandler& operator=
      (const ossimImageElevationHandler& rhs);


   /** Pointers to links in chain. */
   ossimRefPtr<ossimImageHandler>      m_ih;
   ossimRefPtr<ossimImageGeometry>     m_geom;

   /** Image space rect stored as drect for inlined pointHasCoverage method. */
   ossimDrect                          m_rect;

   /* Ignoring Macro
   TYPE_DATA */
};
