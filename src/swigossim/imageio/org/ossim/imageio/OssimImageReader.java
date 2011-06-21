package org.ossim.imageio;

import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;
import java.util.Iterator;

import javax.imageio.ImageReadParam;
import javax.imageio.ImageReader;
import javax.imageio.ImageTypeSpecifier;
import javax.imageio.metadata.IIOMetadata;

import jossim.base.ossimFilename;
import jossim.imaging.ossimImageHandler;
import jossim.imaging.ossimImageHandlerRegistry;

import org.ossim.imageio.spi.OssimImageReaderSpi;

import apps.ossimRenderedImage;

public class OssimImageReader extends ImageReader
{
  @Override
  public int getTileHeight( int imageIndex ) throws IOException
  {
    handler.setCurrentEntry( imageIndex );
    return (int)handler.getTileHeight();
  }

  @Override
  public int getTileWidth( int imageIndex ) throws IOException
  {
    handler.setCurrentEntry( imageIndex );
    return (int)handler.getTileWidth();
  }

  protected File imageFile;

  protected ossimImageHandler handler;

  @Override
  public void setInput( Object input )
  {
    super.setInput( input );

    if ( input instanceof File )
    {
      imageFile = (File)input;

      ossimFilename fileName = new ossimFilename( imageFile.getAbsolutePath() );

      handler = ossimImageHandlerRegistry.instance().open( fileName );

      RenderedImage image = new ossimRenderedImage( handler );
    }

  }

  public OssimImageReader( OssimImageReaderSpi originatingProvider )
  {
    super( originatingProvider );
  }

  @Override
  public int getHeight( int imageIndex ) throws IOException
  {
    handler.setCurrentEntry( imageIndex );

    return (int)handler.getBoundingRect().height();
  }

  @Override
  public IIOMetadata getImageMetadata( int imageIndex ) throws IOException
  {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public Iterator<ImageTypeSpecifier> getImageTypes( int imageIndex )
      throws IOException
  {
    handler.setCurrentEntry( imageIndex );
    
//    ImageTypeSpecifier imageTypeSpecifier = new ImageTypeSpecifier();
    
    return null;
  }

  @Override
  public int getNumImages( boolean allowSearch ) throws IOException
  {
    return (int)handler.getNumberOfEntries();
  }

  @Override
  public IIOMetadata getStreamMetadata() throws IOException
  {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public int getWidth( int imageIndex ) throws IOException
  {
    handler.setCurrentEntry( imageIndex );

    return (int)handler.getBoundingRect().width();
  }

  @Override
  public BufferedImage read( int imageIndex, ImageReadParam param )
      throws IOException
  {
    // TODO Auto-generated method stub
    return null;
  }

  @Override
  public boolean isImageTiled( int imageIndex ) throws IOException
  {
    return true;
  }

}
