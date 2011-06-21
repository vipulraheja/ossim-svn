//-----------------------------------------------------------------------------
// File:  Foo.java
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Java foo/test app.  Please do not commit your code.
//
//-----------------------------------------------------------------------------
// $Id: Foo.java 19748 2011-06-12 15:34:56Z dburken $

package org.ossim.jni.apps;

// import java.io.File;
// import java.lang.String;
// import org.ossim.jni.base.Util;

public class Foo
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
      try
      {
         // Your code here...
      }
      catch( Exception e )
      {
         System.err.println("Caught Exception: " + e.getMessage());
      }
   }
}

