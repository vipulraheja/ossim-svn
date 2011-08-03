/*-----------------------------------------------------------------------------
 * Filename        : ossimImageElevationDatabase.i
 * Author          : Vipul Raheja
 * License         : See top level LICENSE.txt file.
 * Description     : Contains SWIG-Python of class ossimImageElevationDatabase
 * -----------------------------------------------------------------------------*/

%module pyossim

%{

#include <ossim/elevation/ossimElevationDatabase.h>
#include <ossim/elevation/ossimImageElevationDatabase.h>

#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimGrect.h>
#include <ossim/base/ossimRefPtr.h>
#include <ossim/base/ossimRtti.h>

#include <map>

%}

/* Handling operators */
%rename(__set__) ossimImageElevationDatabase::operator=;

/* Wrapping class ossimImageElevationDatabase */
class ossimImageElevationDatabase : public ossimElevationCellDatabase
{
        public:

                /** default constructor */
                ossimImageElevationDatabase();

                virtual bool open(const ossimString& connectionString);
                virtual void close();

                void mapRegion(const ossimGrect& region);

                virtual double getHeightAboveMSL(const ossimGpt& gpt);
                virtual double getHeightAboveEllipsoid(const ossimGpt&);

                virtual bool pointHasCoverage(const ossimGpt& gpt) const;

                virtual double getAccuracyLE90(const ossimGpt& gpt) const;
                virtual double getAccuracyCE90(const ossimGpt& gpt) const;

                virtual bool loadState(const ossimKeywordlist& kwl, const char* prefix=0);
                virtual bool saveState(ossimKeywordlist& kwl, const char* prefix)const;

                void getBoundingRect(ossimGrect& rect) const;

                bool processFile(const ossimFilename& file, bool& recurseFlag);

        protected:
                ~ossimImageElevationDatabase();

                virtual ossimRefPtr<ossimElevCellHandler> createCell(const ossimGpt& gpt);

                // virtual ossim_uint64 createId(const ossimGpt& pt) const;

                virtual ossimRefPtr<ossimElevCellHandler> getOrCreateCellHandler(const ossimGpt& gpt);

                virtual void remove(ossim_uint64 id);

        private:

                // Private container to hold bounding rect and image handler.
                struct ossimImageElevationFileEntry
                {
                        /** @brief default constructor */
                        ossimImageElevationFileEntry();

                        /** @brief Constructor that takes a file name. */
                        ossimImageElevationFileEntry(const ossimFilename& file);

                        /** file name */
                        ossimFilename m_file;

                        /** Bounding rectangle in decimal degrees. */
                        ossimGrect m_rect;

                        /** True if in ossimElevationCellDatabase::m_cacheMap. */
                        bool m_loadedFlag;
                };  

                /**
                 * @brief Initializes m_entryMap with all loadable files from
                 * m_connectionString.
                 */
                void loadFileMap();

                ossimImageElevationDatabase(const ossimImageElevationDatabase& copy_this);

                const ossimImageElevationDatabase& operator=(const ossimImageElevationDatabase& rhs);

                std::map<ossim_uint64, ossimImageElevationFileEntry> m_entryMap;
                ossim_uint64 m_lastMapKey;
                ossim_uint64 m_lastAccessedId;

                /* Ignoring Macro 
                TYPE_DATA */
};
