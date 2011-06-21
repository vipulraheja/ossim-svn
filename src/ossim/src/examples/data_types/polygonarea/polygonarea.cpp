// $Id: polygonarea.cpp 8902 2006-03-20 21:16:32Z dburken $


#include <vector>
#include <iostream>
using namespace std;

#include "base/data_types/ossimPolyArea2d.h"
#include "base/data_types/ossimDpt.h"
#include "base/data_types/ossimKeywordlist.h"

int main()
{
   ossimKeywordlist kwl;
   vector<ossimDpt> v(4);
   
   v[0] = ossimDpt(0,0);
   v[1] = ossimDpt(1000,0);
   v[2] = ossimDpt(1000,1000);
   v[3] = ossimDpt(0,1000);

   vector<ossimDpt> v2(4);

   v2[0] = ossimDpt(100,100);
   v2[1] = ossimDpt(900,100);
   v2[2] = ossimDpt(900,900);
   v2[3] = ossimDpt(100,900);
   
   ossimPolyArea2d poly1(v);
   
   ossimPolyArea2d poly2(v2);

   cout << "poly2" << endl;
   cout << poly2 << endl;
   
   cout << "poly1" << endl;
   cout << poly1 << endl;

   
   ossimDrect rect;
   poly1.getBoundingRect(rect);
   cout <<"Bounding rect:" << endl;
   cout << rect << endl;

   ossimPolyArea2d poly3 = (poly1 - poly2);
   
   poly3.saveState(kwl);
   cout << kwl << endl;

   ossimPolyArea2d poly4;

   poly4.loadState(kwl);
   cout << "poly4: " << endl;
   cout << poly4 << endl;

   cout << "pointwithin 200, 200: " << poly4.isPointWithin(200, 200) << endl;
   cout << "pointwithin 50, 50:   " << poly4.isPointWithin(50, 50) << endl;

   cout << poly4 << endl;

   ossimPolyArea2d poly5 = poly1;

   cout << "poly1-poly2" << endl;
   cout << (poly1-poly2) << endl;
   poly5 -= poly2;
   cout << "poly5-=poly2 should be the same as poly1-poly2" << endl;
   cout << poly5 << endl;
   
   cout << "poly1+poly2" << endl;
   cout << (poly1+poly2) << endl;

   poly5 = poly1;
   poly5 += poly2;
   cout << "poly5+=poly2 should be the same as poly1+poly2" << endl;
   cout << poly5 << endl;
   
   cout << "poly1^poly2" << endl;
   cout << (poly1^poly2) << endl;
   poly5 = poly1;
   poly5 ^= poly2;
   cout << "poly5^=poly2 should be the same as poly1^poly2" << endl;
   cout << poly5 << endl;
   
   cout << "poly1&poly2" << endl;
   cout << (poly1&poly2) << endl;
   poly5 = poly1;
   poly5 &= poly2;
   cout << "poly5&=poly2 should be the same as poly1&poly2" << endl;
   cout << poly5 << endl;
   
   cout << "point within " << poly1.isPointWithin(10,1) <<endl;


   //---
   // This test put us in an infinite loop bugzilla #1117.  (drb 20060320)
   //---
   cout << "Starting infinite loop test bugzilla #1117..." << endl;
   ossimPolyArea2d poly6( ossimDpt(3065, -25684),
                          ossimDpt(3575, -25686),
                          ossimDpt(3576, -25175),
                          ossimDpt(3066, -25174) );
   cout << "poly6:  " << poly6 << endl;
   ossimPolyArea2d poly7( ossimDpt(3513, -25238),
                          ossimDpt(3576, -25238),
                          ossimDpt(3576, -25175),
                          ossimDpt(3513, -25175));
   cout << "poly7:  " << poly7 << endl;
   ossimPolyArea2d poly8 = poly6 & poly7;
   cout << "poly8:  " << poly8 << endl;
   cout << "Ending infinite loop test bugzilla #1117..." << endl;

   return 0;
}
