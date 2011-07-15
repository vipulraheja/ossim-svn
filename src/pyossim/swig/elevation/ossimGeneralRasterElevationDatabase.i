/*-----------------------------------------------------------------------------
 * Filename        : ossimGeneralRasterElevationDatabase.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimDataObject
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/elevation/ossimElevationDatabase.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/elevation/ossimGeneralRasterElevHandler.h>
#include <ossim/elevation/ossimGeneralRasterElevationDatabase.h>
#include <OpenThreads/Mutex>

%}

/* Wrapping class ossimGeneralRasterElevationDatabase */
class ossimGeneralRasterElevationDatabase : public ossimElevationCellDatabase
{
        public:
                ossimGeneralRasterElevationDatabase()
                        :ossimElevationCellDatabase()
                {
                }
                ossimGeneralRasterElevationDatabase(const ossimGeneralRasterElevationDatabase& rhs)
                        :ossimElevationCellDatabase(rhs)
                {
                }
                virtual ~ossimGeneralRasterElevationDatabase()
                {
                        if(m_cellHandler.valid())
                        {
                                m_cellHandler->close();
                        }
                        m_cellHandler = 0;
                }
                ossimObject* dup()const
                {
                        return new ossimGeneralRasterElevationDatabase(*this);
                }
                virtual bool open(const ossimString& connectionString);
                virtual bool pointHasCoverage(const ossimGpt& gpt) const;
                
                virtual double getAccuracyLE90(const ossimGpt& /* gpt */) const
                {
                        std::cout << "ossimGeneralElevationDatabase::getAccuracyLE90 \n";
                        return 0.0;
                }
                virtual double getAccuracyCE90(const ossimGpt& /* gpt */) const
                {
                        std::cout << "ossimGeneralElevationDatabase::getAccuracyCE90 \n";
                        return 0.0;
                }
                
                virtual double getHeightAboveMSL(const ossimGpt&);
                virtual double getHeightAboveEllipsoid(const ossimGpt& gpt);
                
                virtual bool loadState(const ossimKeywordlist& kwl, const char* prefix = 0);
                virtual bool saveState(ossimKeywordlist& kwl, const char* prefix = 0)const;
                
                virtual ossim_uint64 createId(const ossimGpt& /* pt */)const
                {
                        return 0;
                }

        protected:
                ossimRefPtr<ossimGeneralRasterElevHandler> m_cellHandler;
                
                bool openGeneralRasterDirectory(const ossimFilename& dir);
                
                void createRelativePath(ossimFilename& file, const ossimGpt& gpt)const;
                
                void createFullPath(ossimFilename& file, const ossimGpt& gpt)const
                {
                        ossimFilename relativeFile;
                        createRelativePath(relativeFile, gpt);
                        file = ossimFilename(m_connectionString).dirCat(relativeFile);
                }
                ossimRefPtr<ossimElevCellHandler> createHandler(const ossimGpt& /* gpt */);
                virtual ossimRefPtr<ossimElevCellHandler> createCell(const ossimGpt& /* gpt */);

                /* Ignoring Macro
                   TYPE_DATA */
};
