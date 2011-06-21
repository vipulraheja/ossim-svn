//-----------------------------------------------------------------------------
// File:  OssimInfo.java
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Java ossim-info app:
//
//-----------------------------------------------------------------------------
// $Id: OssimInfo.java 19748 2011-06-12 15:34:56Z dburken $

package org.ossim.jni.apps;

import org.ossim.jni.Info;

public class OssimInfo
{
   static
   {
      System.loadLibrary( "ossimjni-swig" );
   }
   
   /**
    * @param args
    */
   public static void main( String[] args )
   {
      // Copy the args with app name for c++ initialize.
      String[] newArgs = new String[args.length + 1];
      newArgs[0] = "org.ossim.oms.apps.Info";
      System.arraycopy(args, 0, newArgs, 1, args.length);
      
      org.ossim.jni.Info info = new org.ossim.jni.Info();
      if ( info.initialize( newArgs.length, newArgs) )
      {
         try
         {
            info.execute();
         }
         catch( Exception e )
         {
            System.err.println("Caught Exception: " + e.getMessage());
         }
      }
   }
}

