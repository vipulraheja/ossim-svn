//*******************************************************************
// Copyright (C) 2003 ImageLinks Inc. 
//
// OSSIM is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software 
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// Author:  David Burken <dburken@imagelinks.com>
// 
// Description:
// 
// Class definition for ossimQtHistogramWidget.
// 
// Derived from QWidget.
// 
// A QT Widget for displaying histograms.
//
//*************************************************************************
// $Id: ossimQtHistogramWidget.cpp 12805 2008-05-07 19:41:34Z gpotts $

#include <qpainter.h>
#include "ossimQtHistogramWidget.h"
#include <ossim/imaging/ossimHistogramRemapper.h>
#include <ossim/base/ossimHistogram.h>

const int WIDTH  = 258;
const int HEIGHT = 130;


ossimQtHistogramWidget::ossimQtHistogramWidget(QWidget* parent,
                                               const char* name,
                                               WFlags f)
   :
      QWidget(parent, name, f), // base class.
      theRemapper(NULL)
{
   setMinimumWidth(WIDTH);
   setMinimumHeight(HEIGHT);
   setMaximumWidth(WIDTH);
   setMaximumHeight(HEIGHT);
   setBackgroundColor(Qt::white);
   // paintHistogram(0);
}

ossimQtHistogramWidget::~ossimQtHistogramWidget()
{
}

void ossimQtHistogramWidget::paintHistogram(ossim_uint32 zero_based_band)
{
   if (!theRemapper)
   {
      return;
   }

//   const int W = WIDTH  - 2;  
   const int H = HEIGHT - 2;

   QPainter p;
   QPen p1(Qt::black, 1);
   QPixmap pm(WIDTH, HEIGHT);
   pm.fill(Qt::white);
   p.begin(&pm);

   ossimRefPtr<ossimHistogram> h = theRemapper->getHistogram(zero_based_band);
   if (h.valid())
   {
      float min = floor(h->GetMinVal());
      float max = ceil(h->GetMaxVal());
      float maxBins = h->GetRes();
      ossimRefPtr<ossimHistogram> scaledHisto = new ossimHistogram(WIDTH, min, max);
      ossim_uint32 binIdx = 0;
      float delta = (max-min)/maxBins;
      float* sumCounts = scaledHisto->GetCounts();
      ossim_int32 sumIndex = 0;
      float value = 0.0;
      memset(sumCounts, '\0', sizeof(float)*WIDTH);
      
      for(binIdx = 0; binIdx < maxBins;++binIdx)
      {
         value = min+delta*binIdx;
         sumIndex = scaledHisto->GetIndex(value);
         if(sumIndex >= 0)
         {
            sumCounts[sumIndex] += h->GetCount(value);
         }
      }
      float sumMaxCount   = scaledHisto->GetMaxCount();
      int height = 0;
      if(sumMaxCount > 0.0)
      {
         for (int col = 1; col < WIDTH; ++col)
         {
            height = ossim::round<int>((sumCounts[col-1]/sumMaxCount)*H);
            
            p.drawLine(col, H, col, H-height);
         }
      }
   }

   // Now paint the clip lines.
   // int lowClip  = static_cast<int>(floor(theRemapper->getLowClipPoint()));
   // int highClip = static_cast<int>(ceil(theRemapper->getHighClipPoint()));
   

   p.end();
   setBackgroundPixmap(pm);
   update();
}

void ossimQtHistogramWidget::paintHistogram()
{
   // This paints an average of all bands it more than one.
   if (!theRemapper)
   {
      return;
   }
//   const int W = WIDTH  - 2;  
   const int H = HEIGHT - 2;

   QPainter p;
   QPen p1(Qt::black, 1);
   QPixmap pm(WIDTH, HEIGHT);
   pm.fill(Qt::white);
   p.begin(&pm);

   ossim_uint32 band = 0;
   const ossim_uint32 BANDS = theRemapper->getNumberOfOutputBands();
   std::vector<ossimRefPtr<ossimHistogram> > h;
   h.resize(BANDS);

   if(!h.size()) return;
   
   for(band = 0; band < BANDS; ++ band)
   {
      h[band] = theRemapper->getHistogram(band);
      if(!h[band].valid()) return;
   }
   
   float min = 99999.0;
   float max = -99999.0;
   float max_count = 0.0;
   ossim_uint32 maxBins   = 0;   
   for (band = 0; band < BANDS; ++band)
   {
      float hmin       = floor(h[band]->GetMinVal());
      float hmax       = ceil(h[band]->GetMaxVal());
      float hmax_count = h[band]->GetMaxCount();
      ossim_uint32 res = h[band]->GetRes();
      
      maxBins = res > maxBins?res:maxBins;
      min = hmin < min ? hmin : min;
      max = hmax > max ? hmax : max;
      // max_count = hmax_count > max_count ? hmax_count : max_count;
      max_count += hmax_count;
   }
   ossimRefPtr<ossimHistogram> scaledHisto = new ossimHistogram(WIDTH, min, max);
   ossim_uint32 binIdx = 0;
   float delta = (max-min)/maxBins;
   float* sumCounts = scaledHisto->GetCounts();
   ossim_int32 sumIndex = 0;
   float value = 0.0;
   memset(sumCounts, '\0', sizeof(float)*WIDTH);

   for(binIdx = 0; binIdx < maxBins;++binIdx)
   {
      value = min+delta*binIdx;
      sumIndex = scaledHisto->GetIndex(value);
      if(sumIndex >= 0)
      {
         for(band = 0; band < BANDS; ++band)
         {
            sumCounts[sumIndex] += h[band]->GetCount(value);
         }
      }
   }
   float sumMaxCount   = scaledHisto->GetMaxCount();
   int height = 0;
   if(sumMaxCount > 0.0)
   {
      for (int col = 1; col < WIDTH; ++col)
      {
         height = ossim::round<int>((sumCounts[col-1]/sumMaxCount)*H);
         
         p.drawLine(col, H, col, H-height);
      }
   }
   
   
   p.end();
   setBackgroundPixmap(pm);
   update();
}

void
ossimQtHistogramWidget::setHistogramRemapper(ossimHistogramRemapper* remapper)
{
   theRemapper = remapper;
}

double getMaxBinCount()
{
   return 0.0;
}

// private copy constructor.
ossimQtHistogramWidget::ossimQtHistogramWidget(const ossimQtHistogramWidget& /* rhs */)
   :
      QWidget(NULL, NULL, 0),
      theRemapper(NULL)
{}

// private operator=
ossimQtHistogramWidget& ossimQtHistogramWidget::operator=(const ossimQtHistogramWidget& /* rhs */)
{
   return *this;
}
