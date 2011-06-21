//*******************************************************************
//
// License:  See top LICENSE.txt file.
//
// Author: Garrett Potts
//
//*************************************************************************
// $Id: ossimQtViewDialogController.cpp 17821 2010-08-03 13:46:38Z dburken $
#include <list>
#include <sstream>
#include <qcombobox.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qradiobutton.h>
#include "ossimQtViewDialogController.h"
#include "ossimQtViewDialog.h"
#include <ossim/base/ossimObject.h>
#include <ossim/projection/ossimEquDistCylProjection.h>
#include <ossim/projection/ossimMapProjectionFactory.h>
#include <ossim/projection/ossimEpsgProjectionFactory.h>
#include <ossim/projection/ossimProjectionFactoryRegistry.h>
#include <ossim/base/ossimDatumFactory.h>
#include <ossim/base/ossimString.h>
#include <ossim/base/ossimDatum.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimKeywordNames.h>


ossimQtViewDialogController::ossimQtViewDialogController(ossimQtViewDialog* dialog)
: theViewDialog(dialog),
theViewObject(NULL)
{
   theViewDialog->connect(theViewDialog, SIGNAL(destroyed()), this, SLOT(dialogDestroyed()));
   init();
}

ossimQtViewDialogController::~ossimQtViewDialogController()
{
   theViewObject = NULL;
   if(theViewDialog)
   {
      theViewDialog->disconnect(theViewDialog, SIGNAL(destroyed()), this, SLOT(dialogDestroyed()));
   }
}

void ossimQtViewDialogController::dialogDestroyed()
{
   theViewDialog = NULL;
}

void ossimQtViewDialogController::init()
{
   setDatumList();
   setProjectionList();
   
   if(!theViewObject)
   {
      setDefaultView();
   }
}


void ossimQtViewDialogController::setDatumList()
{
   if(!theViewDialog) return;
   
   QStrList datumList;
   std::vector<ossimString> tempOssimDatumList = ossimDatumFactory::instance()->getList();
   std::vector<ossimString>::iterator listIter = tempOssimDatumList.begin();
   
   
   while(listIter != tempOssimDatumList.end())
   {
      const ossimDatum* datum = ossimDatumFactory::instance()->create(*listIter);
      if(datum)
      {
         datumList.append((datum->code() + ": " + datum->name()).c_str());
      }
      ++listIter;
   }
   theViewDialog->theDatumComboBox->clear();
   theViewDialog->theDatumComboBox->insertStrList(datumList);   
   
}

void ossimQtViewDialogController::setProjectionList()
{
   if(!theViewDialog) return;
   
   if ( isIdentityMode() )
   {
      // Disable all fields.
      theViewDialog->theDatumComboBox->setDisabled(true);
      theViewDialog->theProjectionComboBox->setDisabled(true);
      theViewDialog->theGsdInput->setDisabled(true);
      theViewDialog->theOriginInput->setDisabled(true);
      theViewDialog->theZoneInput->setDisabled(true);
      theViewDialog->theHemisphereComboBox->setDisabled(true);
      theViewDialog->theStandardParallelInput->setDisabled(true);
      theViewDialog->theScaleFactorInput->setDisabled(true);   
   }
   else
   {
      // Enable fields identity mode would have disabled.
      theViewDialog->theDatumComboBox->setDisabled(false);
      theViewDialog->theProjectionComboBox->setDisabled(false);
      
      QStrList projList;
      if(theViewDialog->theMapRadioButton->isOn())
      {
         std::vector<ossimString> tempOssimList;
         ossimMapProjectionFactory::instance()->getTypeNameList(tempOssimList);
         std::vector<ossimString>::iterator listIter = tempOssimList.begin();
         
         while(listIter != tempOssimList.end())
         {
            projList.append((*listIter).c_str());
            ++listIter;
         }
      }
      else if(theViewDialog->theStatePlaneRadioButton->isOn())
      {
         std::vector<ossimString> tempOssimList;
         ossimEpsgProjectionFactory::instance()->getTypeNameList(tempOssimList);
         std::vector<ossimString>::iterator listIter = tempOssimList.begin();
         while(listIter != tempOssimList.end())
         {
            projList.append((*listIter).c_str());
            ++listIter;
         }
         showStatePlaneInputs();   
      }
      theViewDialog->theProjectionComboBox->clear();
      theViewDialog->theProjectionComboBox->insertStrList(projList);
      
      if(theViewObject.valid()&&theViewDialog->theMapRadioButton->isOn())
      {
         theViewDialog->theProjectionComboBox->setCurrentText(theViewObject->getClassName().c_str());
         if(theViewObject.valid())
         {
            showProjectionInputs(theViewObject->getClassName().c_str());
         }
      }
   }
}

void ossimQtViewDialogController::currentProjectionChanged(const QString& str)
{
   if(theViewDialog&&theViewDialog->theMapRadioButton->isOn())
   {
      showProjectionInputs(str.ascii());
   }
   else
   {
      
   }
}


void ossimQtViewDialogController::apply()
{
   if ( isIdentityMode() )
   {
      emit setIdentityMode(true);
   }
   else
   {
      emit setIdentityMode(false);
      transferFromDialog();
      emit applyView(theViewObject.get());
      transferToDialog();
   }
}

void ossimQtViewDialogController::propagate()
{
   transferFromDialog();
   
   emit propagateView();
}

void ossimQtViewDialogController::close()
{
   if(theViewDialog)
   {
      theViewDialog->close(true);
   }
}

void ossimQtViewDialogController::setView(const ossimObject* view)
{
   theViewObject = 0;
   
   if(view)
   {
      theViewObject = view->dup();
   }
   
   transferToDialog();
}

void ossimQtViewDialogController::transformationTypeChanged()
{
   setProjectionList();
}


void ossimQtViewDialogController::setDefaultView()
{
   ossimEquDistCylProjection proj;
   setView(&proj);
}

void ossimQtViewDialogController::hideIdentityButton(bool flag)
{
   if (theViewDialog)
   {
      if (theViewDialog->theIdentityButton)
      {
         if (flag)
         {
            theViewDialog->theIdentityButton->hide();
         }
         else
         {
            theViewDialog->theIdentityButton->show();
         }
      }
   }
}

void ossimQtViewDialogController::setIdentityButtonChecked(bool flag)
{
   if (theViewDialog)
   {
      if (theViewDialog->theIdentityButton)
      {
         theViewDialog->theIdentityButton->setChecked(flag);
         setProjectionList();
      }
   }
}

void ossimQtViewDialogController::transferFromDialog()
{
   ossimKeywordlist kwl;
   
   kwl.add(ossimKeywordNames::TYPE_KW,
           ossimString(theViewDialog->theProjectionComboBox->currentText().ascii()),
           true);
   
   QString currentText = theViewDialog->theDatumComboBox->currentText().ascii();
   
   ossimString code = currentText.ascii();
   
   std::vector<ossimString> arrayList = code.explode(":");
   kwl.add(ossimKeywordNames::DATUM_KW,
           arrayList[0],
           true);
   
   kwl.add(ossimKeywordNames::METERS_PER_PIXEL_X_KW,
           ossimString(theViewDialog->theGsdInput->text().ascii()).toDouble(),
           true);
   kwl.add(ossimKeywordNames::METERS_PER_PIXEL_Y_KW,
           ossimString(theViewDialog->theGsdInput->text().ascii()).toDouble(),
           true);
   
   ossimString origin = theViewDialog->theOriginInput->text().ascii();
   if(origin != "")
   {
      istringstream istr(origin.c_str());
      double lat=0.0, lon=0.0;
      istr>>lat >>lon;
      
      kwl.add(ossimKeywordNames::ORIGIN_LATITUDE_KW,
              lat,
              true);
      
      kwl.add(ossimKeywordNames::CENTRAL_MERIDIAN_KW,
              lon,
              true);
   }
   
   kwl.add(ossimKeywordNames::ZONE_KW,
           ossimString(theViewDialog->theZoneInput->text().ascii()).toInt32(),
           true);
   
   ossimString hem = theViewDialog->theHemisphereComboBox->currentText().ascii();
   if(hem == "North")
   {
      hem = "N";
   }
   else 
   {
      hem = "S";
   }
   
   kwl.add(ossimKeywordNames::HEMISPHERE_KW,
           hem,
           true);
   
   
   // Don't pass an empty scale factor to projection loadState.
   ossimString scaleFactor =
   theViewDialog->theScaleFactorInput->text().ascii();
   if (scaleFactor.toDouble() > 0.0)
   {
      kwl.add(ossimKeywordNames::SCALE_FACTOR_KW,
              scaleFactor,
              true);
   }
   
   // Check for standard parallels.
   std::string parallels =
   theViewDialog->theStandardParallelInput->text().ascii();
   if (parallels.size())
   {
      std::istringstream is(parallels.c_str());
      if (is)
      {
         ossimString p1;
         ossimString p2;
         is >> p1;
         is >> p2;
         p1 = p1.trim();
         p2 = p2.trim();
         if (p1.size() && p2.size())
         {
            ossim_float64 d1 = p1.toFloat64();
            ossim_float64 d2 = p2.toFloat64();
            if (p1 > p2) // swap.
            {
               ossim_float64 d3 = d1;
               d1 = d2;
               d2 = d3;
            }
            // pseudo range check.
            if ( (d1 > -90.0) && (d1 < 90.0) &&
                (d2 > -90.0) && (d2 < 90.0) )
            {
               kwl.add(ossimKeywordNames::STD_PARALLEL_1_KW, d1, true);
               kwl.add(ossimKeywordNames::STD_PARALLEL_2_KW, d2, true);
            }
         }
      }
   } // End of standard parallels...
   
   ossimProjection* proj = ossimProjectionFactoryRegistry::instance()->createProjection(kwl);
   if(proj)
   {
       theViewObject = proj;
   }
}

void ossimQtViewDialogController::transferToDialog()
{
   ossimMapProjection* proj = PTR_CAST(ossimMapProjection, theViewObject.get());
   if(proj)
   { 
      ossimKeywordlist kwl;
      theViewObject->saveState(kwl);
      
      ossimGpt origin = proj->origin();
      ossimDpt meters = proj->getMetersPerPixel();
      ossimString originString = ossimString::toString(origin.latd()) + " " + ossimString::toString(origin.lond());
      ossimString metersString = ossimString::toString(meters.x) + " " + ossimString::toString(meters.y);
      theViewDialog->theOriginInput->setText(originString.c_str());
      theViewDialog->theGsdInput->setText(metersString.c_str());
      
      const char* value = kwl.find(ossimKeywordNames::ZONE_KW);
      if(value)
      {
         theViewDialog->theZoneInput->setText(value);
      }
      else
      {
         theViewDialog->theZoneInput->setText("");
      }
      
      if((value=kwl.find(ossimKeywordNames::HEMISPHERE_KW))!=NULL)
      {	    
         ossimString temp = value;
         temp = temp.upcase();
         if(temp.contains("N"))
         {
            theViewDialog->theHemisphereComboBox->setCurrentText("North");
         }
         else
         {
            theViewDialog->theHemisphereComboBox->setCurrentText("South");
         }
      }
      
      if((value = kwl.find(ossimKeywordNames::STD_PARALLEL_1_KW))!=NULL)
      {
         ossimString parallels = value;
         parallels += " ";
         parallels += ossimString( kwl.find(ossimKeywordNames::STD_PARALLEL_2_KW));
         theViewDialog->theStandardParallelInput->setText(parallels.c_str());
      }
      if((value=kwl.find(ossimKeywordNames::SCALE_FACTOR_KW))!=NULL)
      {
         theViewDialog->theScaleFactorInput->setText(value);
      }
      theViewDialog->theProjectionComboBox->setCurrentText(theViewObject->getClassName().c_str());
      theViewDialog->theDatumComboBox->setCurrentText((proj->getDatum()->code() + ": " + proj->getDatum()->name()).c_str());
   }
   
}

void ossimQtViewDialogController::showStatePlaneInputs()
{
   theViewDialog->theGsdInput->setDisabled(false);
   theViewDialog->theOriginInput->setDisabled(true);
   theViewDialog->theZoneInput->setDisabled(true);
   theViewDialog->theHemisphereComboBox->setDisabled(true);
   theViewDialog->theStandardParallelInput->setDisabled(true);
   theViewDialog->theScaleFactorInput->setDisabled(true);   
}

void ossimQtViewDialogController::showProjectionInputs(const QString& proj)
{
   ossimRefPtr<ossimProjection> tempProj = ossimProjectionFactoryRegistry::instance()->createProjection(ossimString(proj.ascii()));
   if(tempProj.valid())
   {
      ossimKeywordlist kwl;
      ossimKeywordlist kwlCurrent;
      
      tempProj->saveState(kwl);
      
      theViewDialog->theGsdInput->setDisabled(false);
      theViewDialog->theOriginInput->setDisabled(false);
      
      if(kwl.find(ossimKeywordNames::ZONE_KW))
      {
         theViewDialog->theZoneInput->setDisabled(false);
      }
      else
      {
         theViewDialog->theZoneInput->setDisabled(true);
      }
      
      if(kwl.find(ossimKeywordNames::HEMISPHERE_KW))
      {
         theViewDialog->theHemisphereComboBox->setDisabled(false);
      }
      else
      {
         theViewDialog->theHemisphereComboBox->setDisabled(true);
      }
      
      if(kwl.find(ossimKeywordNames::STD_PARALLEL_1_KW))
      {
         theViewDialog->theStandardParallelInput->setDisabled(false);
      }
      else
      {
         theViewDialog->theStandardParallelInput->setDisabled(true);
      }
      
      if(kwl.find(ossimKeywordNames::SCALE_FACTOR_KW))
      {
         theViewDialog->theScaleFactorInput->setDisabled(false);
      }
      else
      {
         theViewDialog->theScaleFactorInput->setDisabled(true);
      }
   }
   
}

bool ossimQtViewDialogController::isIdentityMode() const
{
   bool result = false;
   {
      if (theViewDialog)
      {
         if (theViewDialog->theIdentityButton)
         {
            result = theViewDialog->theIdentityButton->isOn();
         }
      }
   }
   return result;
}
