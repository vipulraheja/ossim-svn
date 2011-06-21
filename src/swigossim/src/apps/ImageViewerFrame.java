package apps;

import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.image.RenderedImage;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.JScrollPane;

import com.sun.media.jai.widget.DisplayJAI;

import jossim.base.PropertyUtil;
import jossim.base.ossimFilename;
import jossim.base.ossimPropertyInterface;
import jossim.base.ossimPropertyRefPtr;
import jossim.base.ossimPropertyRefPtrVector;
import jossim.base.ossimString;
import jossim.imaging.ossimImageChain;
import jossim.imaging.ossimImageHandler;
import jossim.imaging.ossimImageHandlerRegistry;
import jossim.imaging.ossimImageSource;
import jossim.imaging.ossimImageSourceFactoryRegistry;
import jossim.init.ossimInit;

public class ImageViewerFrame extends JFrame
{
  private RenderedImage image;

  static
  {
    System.loadLibrary( "jossim" );
  }

  public ImageViewerFrame( String filename )
  {
    super( filename );

    setCursor( Cursor.getPredefinedCursor( Cursor.WAIT_CURSOR ) );
    image = loadImageFile( new File( filename ) );
    setCursor( Cursor.getPredefinedCursor( Cursor.DEFAULT_CURSOR ) );

    DisplayJAI display = new DisplayJAI();

    display.set( image );

    JScrollPane scrollPane = new JScrollPane( display );

    scrollPane.setPreferredSize( new Dimension( 512, 512 ) );
    getContentPane().add( scrollPane );
  }

  /**
   * @param imageFile
   * @return
   */
  private RenderedImage loadImageFile( File imageFile )
  {
    RenderedImage image = null;

    ossimImageHandlerRegistry registry = ossimImageHandlerRegistry.instance();
    ossimFilename filename = new ossimFilename( imageFile.getAbsolutePath() );
    ossimImageHandler handler = registry.open( filename );

    if ( handler != null && handler.isOpen() )
    {
      // printProperties( handler );

      ossimImageChain chain = new ossimImageChain();

      chain.addLast( handler );

      ossimImageSourceFactoryRegistry factory = ossimImageSourceFactoryRegistry
          .instance();

      ossimImageSource cache = factory.createImageSource( new ossimString(
          "ossimCacheTileSource" ) );

      // printProperties( cache );
      chain.addLast( cache );

      // ossimImageSource remapper = factory.createImageSource( new
      // ossimString(
      // "ossimScalarRemapper" ) );

      // printProperties( remapper );
      // chain.addLast( remapper );

      long numBands = handler.getNumberOfOutputBands();

      if ( numBands > 3 )
      {
        ossimImageSource bandSelector = factory
            .createImageSource( new ossimString( "ossimBandSelector" ) );

        bandSelector.setProperty( new ossimString( "Selected bands" ),
            new ossimString( "0,1,2" ) );
        chain.addLast( bandSelector );

        // printProperties( bandSelector );
      }

      chain.initialize();
      // printProperties( chain );

      //image = new ossimRenderedImage( chain );

      image = new ossimRenderedImage2( chain );
      System.out.println( image );
    }

    return image;
  }

  public static void printProperties( ossimPropertyInterface source )
  {
    ossimPropertyRefPtrVector properties = new ossimPropertyRefPtrVector();

    source.getPropertyList( properties );
    System.out.println( "numProps: " + properties.size() );

    for ( int i = 0; i < properties.size(); i++ )
    {
      ossimPropertyRefPtr property = properties.get( i );

      System.out.println( PropertyUtil.getName( property ) + ": "
          + PropertyUtil.getValue( property ) );
    }
  }

  /**
   * @param args
   */
  public static void main( String[] args )
  {
    ossimInit.instance().initialize( args.length, args );

    if ( args.length > 0 )
    {
      JFrame frame = new ImageViewerFrame( args[args.length - 1] );

      frame.pack();
      frame.setVisible( true );
      frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    }
    else
      System.err.println( "Please specify a filename" );
  }
}
