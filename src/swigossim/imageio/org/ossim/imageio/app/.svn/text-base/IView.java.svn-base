package org.ossim.imageio.app;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.imageio.ImageReader;
import javax.imageio.stream.ImageInputStream;
import javax.media.jai.JAI;
import javax.swing.JFrame;
import javax.swing.JScrollPane;

import jossim.base.ossimFilename;
import jossim.imaging.ossimImageHandler;
import jossim.imaging.ossimImageHandlerRegistry;
import jossim.init.ossimInit;

import apps.ossimRenderedImage;

import com.sun.media.jai.widget.DisplayJAI;

public class IView
{

  /**
   * @param args
   * @throws IOException
   */
  public static void main( String[] args ) throws IOException
  {
    System.loadLibrary( "jossim" );
    ossimInit.instance().initialize( args.length, args );

    File imageFile = new File( "c:/data/test_data/sanfran/sanfran.tif" );
    // RenderedImage image = loadWithImageIO( imageFile );
    // RenderedImage image = loadWithJAI( imageFile );
    RenderedImage image = loadWithJossim( imageFile );
    String title = "image-io";

    showImage( title, image );
  }

  public static RenderedImage loadWithJossim( File imageFile )
  {
    ossimFilename fileName = new ossimFilename( imageFile.getAbsolutePath() );

    ossimImageHandler handler = ossimImageHandlerRegistry.instance().open(
        fileName );

    RenderedImage image = new ossimRenderedImage( handler );

    return image;
  }

  public static RenderedImage loadWithOssimImageIO( File imageFile )
      throws IOException
  {
    ImageReader reader = ImageIO.getImageReadersByFormatName( "ossim" ).next();

    reader.setInput( imageFile );

    RenderedImage image = reader.readAsRenderedImage( 0, null );

    return image;
  }

  public static RenderedImage loadWithJAI( File imageFile )
  {
    RenderedImage image = JAI.create( "fileload", imageFile.getAbsolutePath() );

    return image;
  }

  public static void showImage( String title, RenderedImage image )
  {
    JFrame frame = new JFrame( title );
    DisplayJAI displayJAI = new DisplayJAI( image );
    JScrollPane scrollPane = new JScrollPane( displayJAI );

    displayJAI.setBackground( Color.black );
    scrollPane.setPreferredSize( new Dimension( 512, 512 ) );
    frame.getContentPane().add( scrollPane );
    frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    frame.pack();
    frame.setVisible( true );
  }

  public static RenderedImage loadWithImageIO( File imageFile )
      throws IOException
  {
    ImageInputStream istream = ImageIO.createImageInputStream( imageFile );
    ImageReader reader = ImageIO.getImageReaders( istream ).next();

    reader.setInput( istream );

    RenderedImage image = reader.readAsRenderedImage( 0, null );
    return image;
  }

}
