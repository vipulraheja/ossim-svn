package org.ossim.oms.apps;
import joms.oms.Init;
import joms.oms.DataInfo;

public class DataInfoTest
{
  public static void printInfo( DataInfo app, String filename )
	{
    		app.open( filename );
    		System.out.println( app.getInfo() );
    		app.close();
	}
  /**
   * @param args
   */
  public static void main( String[] args )
  {
    DataInfo app = new DataInfo();
	String[] newArgs = new String[0];

    Init.instance().initialize( newArgs.length, newArgs);

	if ( args.length > 0 )
	{
      int idx = 0;
      // this block is for testing an open and close to make sure all resources are freed up
      // we will do this 3000 times.
      //
//      System.out.println("--------------------------------------Testing 3000 opens------------------------------------");
//      for(idx = 0; idx < 3000; ++idx)
//      {
//         //app = new DataInfo();
//         app.open(args[0]);
//         if(idx == 2999)
//         {
//            System.out.println("Printing Information");
//            System.out.println( app.getInfo() );
//         }
//         app.close();
//      }
//      System.out.println("----------------------------Doing a simple printing of data info-----------------------------");
      // this block of coe is for printing a data info
		for ( idx = 0; idx < args.length; ++idx )
		{
         
			DataInfoTest.printInfo( app, args[idx] );
		}
	}

  }

}
