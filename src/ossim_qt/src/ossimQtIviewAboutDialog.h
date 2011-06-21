//----------------------------------------------------------------------------
// Copyright (C) 2004 David Burken, all rights reserved.
//
// License:  LGPL
// 
// See LICENSE.txt file in the top level directory for more details.
//
// Author:  David Burken
//
// Description: ImageLinker about dialog.
//
// $Id: ossimQtIviewAboutDialog.h 6890 2004-10-14 19:47:18Z dburken $
//----------------------------------------------------------------------------
#ifndef ossimQtIviewAboutDialog_HEADER
#define ossimQtIviewAboutDialog_HEADER

#include <ossimQtAboutDialogBase.h>

class ossimQtIviewAboutDialog : public ossimQtAboutDialogBase
{

public:

   /** public constructor */
   ossimQtIviewAboutDialog(
      QWidget* parent = 0,
      const char* name = "ossimQtIviewAboutDialog",
      bool modal = false,
      WFlags f = 0 );

   /** virtual destructor */
   virtual ~ossimQtIviewAboutDialog();

private:
   /** Hide from use copy constructor. */
   ossimQtIviewAboutDialog(const ossimQtIviewAboutDialog& obj);

   /** Hide from use assignment operator. */
   const ossimQtIviewAboutDialog& operator=(const ossimQtIviewAboutDialog& rhs);

};

#endif /* End of "#ifndef ossimQtIviewAboutDialog_HEADER" */
