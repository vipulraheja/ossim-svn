package apps;

import java.awt.image.RenderedImage;

import jossim.base.ossimFilename;
import jossim.imaging.ossimImageHandler;
import jossim.imaging.ossimImageHandlerRegistry;
import jossim.init.ossimInit;

import org.apache.commons.lang.builder.ToStringBuilder;

public class ImageInfo
{
  static
  {
    System.loadLibrary( "jossim" );
  }

  /**
   * @param args
   */
  public static void main( String[] args )
  {
    if ( args.length > 0 )
    {
      ossimInit.instance().initialize( args.length, args );

      ossimImageHandlerRegistry factory = ossimImageHandlerRegistry.instance();

      ossimFilename filename = new ossimFilename( args[args.length - 1] );
      ossimImageHandler handler = factory.open( filename );

      if ( handler != null )
        printImageInfo( new ossimRenderedImage( handler ) );
      else
        System.err.println( "cannot open image" );

    }
    else
      System.err.println( "Error: must specify a filename." );
  }

  public static void printImageInfo( ossimImageHandler handler )
  {
    System.out.println( new ToStringBuilder( handler ).append( "tileWidth",
        handler.getTileWidth() ).append( "tileHeight", handler.getTileHeight() )
        .append( "width", handler.getBoundingRect().width() ).append( "height",
            handler.getBoundingRect().height() ).append(
            "numberOfReducedresSets", handler.getNumberOfReducedResSets() )
        .append( "numBands", handler.getNumberOfOutputBands() ).append( "open",
            handler.isOpen() ).toString() );
  }

  public static void printImageInfo( RenderedImage image )
  {
    System.out.println( new ToStringBuilder( image ).append( "tileWidth",
        image.getTileWidth() ).append( "tileHeight", image.getTileHeight() )
        .append( "width", image.getWidth() ).append( "height",
            image.getHeight() ).append( "numXTiles", image.getNumXTiles() )
        .append( "numYTiles", image.getNumYTiles() ) );
  }
}
