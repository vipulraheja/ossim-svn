package org.ossim.imageio.app;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.ImageTypeSpecifier;
import jossim.init.ossimInit;

public class TestImageIO
{
  static
  {
    System.loadLibrary( "jossim" );

  }

  public static void main( String[] args ) throws IOException
  {

    ossimInit.instance().initialize( args.length, args );

    File imageFile = new File( "c:/data/test_data/sanfran/sanfran.tif" );
    // File imageFile = new File( "c:/data/test_data/katrina/24329590.jpg" );

    // test1(imageFile);

    // test2( imageFile );

    // ImageInputStream istream = ImageIO.createImageInputStream( imageFile );
    // ImageReader reader = ImageIO.getImageReaders( istream ).next();
    //
    // reader.setInput( istream );

    ImageReader reader = ImageIO.getImageReadersByFormatName( "ossim" ).next();

    reader.setInput( imageFile );

    for ( int x = 0, numImages = reader.getNumImages( true ); x < numImages; x++ )
    {
      Map<String, Object> imageDataMap = new HashMap<String, Object>();

      imageDataMap.put( "imageTiled", reader.isImageTiled( x ) );
      imageDataMap.put( "width", reader.getWidth( x ) );
      imageDataMap.put( "height", reader.getHeight( x ) );
      imageDataMap.put( "tileWidth", reader.getTileWidth( x ) );
      imageDataMap.put( "tileHeight", reader.getTileHeight( x ) );

      for ( Iterator<ImageTypeSpecifier> it = reader.getImageTypes( x ); it != null
          && it.hasNext(); )
      {
        ImageTypeSpecifier specifier = it.next();
        int numBands = specifier.getNumBands();
        List<Integer> bitsPerBand = new ArrayList<Integer>();

        imageDataMap.put( "numBands", numBands );

        for ( int band = 0; band < numBands; band++ )
        {
          bitsPerBand.add( specifier.getBitsPerBand( band ) );
        }

        imageDataMap.put( "bitsPerBand", bitsPerBand );
      }

      System.out.println( imageDataMap );
    }
  }

  public static void test2( File imageFile )
  {
    Iterator<ImageReader> i = null;

    i = ImageIO.getImageReadersByFormatName( "ossim" );
    System.out.println( "getImageReadersByFormatName:" );

    while ( i.hasNext() )
      System.out.println( "\t" + i.next().getClass().getName() );

    i = ImageIO.getImageReadersByMIMEType( "image/x-ossim" );
    System.out.println( "getImageReadersByMIMEType:" );

    while ( i.hasNext() )
      System.out.println( "\t" + i.next().getClass().getName() );

    i = ImageIO.getImageReadersBySuffix( "tif" );
    System.out.println( "getImageReadersBySuffix:" );

    while ( i.hasNext() )
      System.out.println( "\t" + i.next().getClass().getName() );

    System.out.println( "getImageReaders:" );
    i = ImageIO.getImageReaders( imageFile );

    while ( i.hasNext() )
      System.out.println( "\t" + i.next().getClass().getName() );
  }

  public static void test1( File imageFile ) throws IOException
  {

    Iterator<ImageReader> i = ImageIO.getImageReaders( ImageIO
        .createImageInputStream( imageFile ) );

    if ( imageFile.exists() )
    {
      System.out.println( "finding readers for " + imageFile );

      while ( i.hasNext() )
      {
        ImageReader reader = i.next();

        System.out.println( reader.getClass().getName() );
      }
    }
  }
}
