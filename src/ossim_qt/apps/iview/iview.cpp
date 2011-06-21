//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: Raster Import Tool (IVIEW) application main.
//
// $Id: iview.cpp 13138 2008-07-06 17:39:39Z dburken $
//----------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include <qapplication.h>
#include <ossimQtSingleImageWindow.h>
#include <ossim/base/ossimArgumentParser.h>
#include <ossim/base/ossimApplicationUsage.h>
#include <ossim/init/ossimInit.h>
#ifdef OSSIMQT_USE_WINDOWS_STYLE
#include <qwindowsstyle.h>
#endif


using namespace std;

extern void qInitImages_ossim_qt();
extern void qCleanupImages_ossim_qt();

int main(int argc, char *argv[])
{
   ossimArgumentParser argumentParser(&argc, argv);
   ossimInit::instance()->addOptions(argumentParser);
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

   //---
   // This was put here since static builds on windows don't load.
   // this entrance is a singleton so if called more than once its ok.
   // This load the images uses for icons and about windows.
   //---
   qInitImages_ossim_qt();
  
   QApplication app(argc, argv);
#ifdef OSSIMQT_USE_WINDOWS_STYLE
   QWindowsStyle *style = new QWindowsStyle();
   app.setStyle(style);
#endif

   ossimQtSingleImageWindow* mainWindow
      = new ossimQtSingleImageWindow(NULL, "mainWindow");

   app.setMainWidget(mainWindow);
   
   mainWindow->show();

   int result = app.exec();

   ossimInit::instance()->finalize();
   
   qCleanupImages_ossim_qt();

   return result;
}
