#include <cstdlib> /* for exit */
#include <iostream>
#include <qapplication.h>
#include <ossimQtMainWindow.h>
#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimApplicationUsage.h>
#include <ossim/init/ossimInit.h>
#ifdef OSSIMQT_USE_WINDOWS_STYLE
#include <qwindowsstyle.h>
#endif
#include <ossim/base/ossimEnvironmentUtility.h>
#include <ossim/base/ossimFilename.h>
#include <ossim/base/ossimEnvironmentUtility.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimDirectory.h>
#include <ossim/base/ossimGeoidEgm96.h>
#include <ossim/base/ossimGeoidManager.h>
#include <ossim/elevation/ossimElevManager.h>

extern void qInitImages_ossim_qt();
extern void qCleanupImages_ossim_qt();

void addMacDefaults(const ossimFilename executablePath)
{
   // test for a bundle
   //
   ossimFilename contentsFolder = executablePath.dirCat("..");
	
   // Check for embedded geoid grid nder the resource folder Resources/egm96.grd
   ossimFilename resourceFolder = contentsFolder.dirCat("Resources");
   ossimFilename geoid1996File = resourceFolder.dirCat("egm96.grd");
   if(geoid1996File.exists())
   {
      ossimRefPtr<ossimGeoid> geoid96 = new ossimGeoidEgm96;
      if(geoid96->open(geoid1996File, OSSIM_BIG_ENDIAN))
      {
         ossimGeoidManager::instance()->addGeoid(geoid96.get());
      }
   }
   // Check for embedded plugins and reference images
   ossimFilename resources = contentsFolder.dirCat("Resources");
   ossimFilename ossimPluginsBundle = contentsFolder.dirCat("plugins");
   if(ossimPluginsBundle.exists())
   {
      ossimInit::instance()->loadPlugins(ossimPluginsBundle);
   }
	
   ossimFilename elevation = resourceFolder.dirCat("elevation");
   if(elevation.exists())
   {
      ossimElevManager::instance()->loadElevationPath(elevation);
   }
}

void addDefaults(int argc, char *argv[])
{
   ossimFilename currentPath = ossimFilename(argv[0]).path();
	if(currentPath.dirCat("..").dirCat("Resources").exists())
	{
		addMacDefaults(currentPath);
	}
}

int main(int argc, char *argv[])
{
   ossimArgumentParser argumentParser(&argc, argv);
   ossimInit::instance()->addOptions(argumentParser);

	addDefaults(argc, argv);
	
   ossimInit::instance()->initialize(argumentParser);
   argumentParser.getApplicationUsage()->addCommandLineOption("-h or --help","Display this information");
   argumentParser.getApplicationUsage()->setApplicationName(argumentParser.getApplicationName());
   argumentParser.getApplicationUsage()->setDescription(argumentParser.getApplicationName()+" GUI application for the ossim core library");
   argumentParser.getApplicationUsage()->setCommandLineUsage(argumentParser.getApplicationName()+" [options]");
  
   if (argumentParser.read("-h") || argumentParser.read("--help"))
   {
      argumentParser.getApplicationUsage()->write(std::cout);
      exit(0);
   }
   argumentParser.reportRemainingOptionsAsUnrecognized();

   // this was put here since static builds on windows don't load.
   // this entrance is a singleton so if called more than once its ok.
   // this load the images uses for icons and about windows.
   //
   qInitImages_ossim_qt();
   
   QApplication app(argc, argv);
#ifdef OSSIMQT_USE_WINDOWS_STYLE
   QWindowsStyle *style = new QWindowsStyle();
   app.setStyle(style);
#endif
   ossimQtMainWindow*  mainWindow = new ossimQtMainWindow(NULL, "ossimQtMainWindow");

   app.setMainWidget(mainWindow);
   mainWindow->show();
   int result = app.exec();
   ossimInit::instance()->finalize();
   
   qCleanupImages_ossim_qt();
   
   return result;
}
