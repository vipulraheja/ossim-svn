package apps;

import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Transparency;
import java.awt.color.ColorSpace;
import java.awt.image.BandedSampleModel;
import java.awt.image.ColorModel;
import java.awt.image.ComponentColorModel;
import java.awt.image.DataBuffer;
import java.awt.image.DataBufferByte;
import java.awt.image.Raster;
import java.awt.image.RenderedImage;
import java.awt.image.SampleModel;
import java.awt.image.WritableRaster;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

import org.apache.commons.lang.builder.ToStringBuilder;

import jossim.base.PropertyUtil;
import jossim.base.ossimCoordSysOrientMode;
import jossim.base.ossimInterleaveType;
import jossim.base.ossimIrect;
import jossim.base.ossimPropertyRefPtr;
import jossim.base.ossimScalarType;
import jossim.base.ossimString;
import jossim.base.ossimStringVector;
import jossim.imaging.ImagingUtil;
import jossim.imaging.ossimImageDataRefPtr;
import jossim.imaging.ossimImageSource;

public class ossimRenderedImage2 implements RenderedImage
{
  protected ossimImageSource imageSource;

  protected int width;

  protected int height;

  protected int tileWidth;

  protected int tileHeight;

  protected int numBands;

  protected int numXTiles;

  protected int numYTiles;

  protected ColorModel colorModel;

  protected SampleModel sampleModel;

  protected Map<String, String> propertyMap;

  public ossimRenderedImage2( ossimImageSource imageSource )
  {
    this.imageSource = imageSource;

    ossimIrect bounds = imageSource.getBoundingRect();

    width = (int)bounds.width();
    height = (int)bounds.height();

    tileWidth = (int)imageSource.getTileWidth();
    tileHeight = (int)imageSource.getTileHeight();

    numXTiles = width / tileWidth;

    if ( width % tileWidth > 0 )
      numXTiles++;

    numYTiles = width / tileWidth;

    if ( height % tileHeight > 0 )
      numYTiles++;

    numBands = (int)imageSource.getNumberOfOutputBands();

    colorModel = new ComponentColorModel( ColorSpace
        .getInstance( ColorSpace.CS_sRGB ), false, false, Transparency.OPAQUE,
        DataBuffer.TYPE_BYTE );

    sampleModel = new BandedSampleModel( DataBuffer.TYPE_BYTE, width, height,
        width, new int[] {
            0, 0, 0
        }, new int[] {
            0, width * height, 2 * width * height
        } );

    ossimStringVector propertNameVector = new ossimStringVector();

    imageSource.getPropertyNames( propertNameVector );

    propertyMap = new HashMap<String, String>();

    for ( int i = 0; i < propertNameVector.size(); i++ )
    {
      ossimString key = propertNameVector.get( i );
      ossimPropertyRefPtr property = imageSource.getProperty( key );
      String value = PropertyUtil.getValue( property );

      propertyMap.put( key.toString(), value );
    }
  }

  public WritableRaster copyData( WritableRaster raster )
  {
    // TODO Auto-generated method stub
    return null;
  }

  public ColorModel getColorModel()
  {
    return colorModel;
  }

  public Raster getData()
  {
    return getData( new Rectangle( 0, 0, width, height ) );
  }

  public Raster getData( Rectangle rect )
  {
    Raster raster = method1( rect );
    //Raster raster = method2( rect );

    return raster;
  }

  public Raster method1( Rectangle rect )
  {
    byte[][] bytes = new byte[numBands][rect.width * rect.height];

    ossimIrect irect = new ossimIrect( rect.x, rect.y, rect.x + tileWidth - 1,
        rect.y + tileHeight - 1, ossimCoordSysOrientMode.OSSIM_LEFT_HANDED );

    ossimImageDataRefPtr imageData = imageSource.getTile( irect );

    for ( int i = 0; i < bytes.length; i++ )
    {
      ImagingUtil.unloadBand( imageData, irect, i, bytes[i] );
    }

    DataBufferByte byteBuffer = new DataBufferByte( bytes, numBands );

    Raster raster = Raster.createBandedRaster( byteBuffer, tileWidth,
        tileHeight, tileWidth, new int[] {
            0, 1, 2
        }, new int[] {
            0, 0, 0
        }, new Point( rect.x, rect.y ) );

    return raster;
  }

  public Raster method2( Rectangle rect )
  {
    byte[] bytes = new byte[rect.width * rect.height * numBands];

    ossimIrect irect = new ossimIrect( rect.x, rect.y, rect.x + tileWidth - 1,
        rect.y + tileHeight - 1, ossimCoordSysOrientMode.OSSIM_LEFT_HANDED );

    ossimImageDataRefPtr imageData = imageSource.getTile( irect );

    ImagingUtil.unloadTile( imageData, irect, ossimInterleaveType.OSSIM_BSQ,
        bytes );

    DataBufferByte byteBuffer = new DataBufferByte( bytes, numBands );
    Point location = new Point( rect.x, rect.y );

    Raster raster = Raster.createBandedRaster( byteBuffer, tileWidth,
        tileHeight, tileWidth, new int[] {
            0, 0, 0
        }, new int[] {
            0, tileWidth * tileHeight, 2 * tileWidth * tileHeight
        }, location );

    return raster;
  }

  public int getHeight()
  {
    return height;
  }

  public int getMinTileX()
  {
    return 0;
  }

  public int getMinTileY()
  {
    return 0;
  }

  public int getMinX()
  {
    return 0;
  }

  public int getMinY()
  {
    return 0;
  }

  public int getNumXTiles()
  {
    return numXTiles;
  }

  public int getNumYTiles()
  {
    return numYTiles;
  }

  public Object getProperty( String name )
  {
    return propertyMap.get( name );
  }

  public String[] getPropertyNames()
  {
    String[] propertyNames = (String[])propertyMap.keySet().toArray();

    return propertyNames;
  }

  public SampleModel getSampleModel()
  {
    return sampleModel;
  }

  public Vector<RenderedImage> getSources()
  {
    // TODO Auto-generated method stub
    return null;
  }

  public Raster getTile( int tileX, int tileY )
  {
    Rectangle rect = new Rectangle( tileX * tileWidth, tileY * tileHeight,
        tileWidth, tileHeight );

    return getData( rect );
  }

  public int getTileGridXOffset()
  {
    return 0;
  }

  public int getTileGridYOffset()
  {
    return 0;
  }

  public int getTileHeight()
  {
    return tileHeight;
  }

  public int getTileWidth()
  {
    return tileWidth;
  }

  public int getWidth()
  {
    return width;
  }

  public static int ossimToJavaType( ossimScalarType ossimType )
  {
    int javaType = -1;

    if ( ossimType.equals( ossimScalarType.OSSIM_SCALAR_UNKNOWN ) )
      javaType = DataBuffer.TYPE_UNDEFINED;
    else if ( ossimType.equals( ossimScalarType.OSSIM_UCHAR ) )
      javaType = DataBuffer.TYPE_BYTE;
    else if ( ossimType.equals( ossimScalarType.OSSIM_UINT8 ) )
      javaType = DataBuffer.TYPE_BYTE;
    else if ( ossimType.equals( ossimScalarType.OSSIM_USHORT16 ) )
      javaType = DataBuffer.TYPE_USHORT;
    else if ( ossimType.equals( ossimScalarType.OSSIM_SSHORT16 ) )
      javaType = DataBuffer.TYPE_SHORT;
    else if ( ossimType.equals( ossimScalarType.OSSIM_USHORT11 ) )
      javaType = DataBuffer.TYPE_USHORT;
    else if ( ossimType.equals( ossimScalarType.OSSIM_FLOAT ) )
      javaType = DataBuffer.TYPE_FLOAT;
    else if ( ossimType.equals( ossimScalarType.OSSIM_NORMALIZED_FLOAT ) )
      javaType = DataBuffer.TYPE_FLOAT;
    else if ( ossimType.equals( ossimScalarType.OSSIM_DOUBLE ) )
      javaType = DataBuffer.TYPE_DOUBLE;
    else if ( ossimType.equals( ossimScalarType.OSSIM_NORMALIZED_DOUBLE ) )
      javaType = DataBuffer.TYPE_DOUBLE;
    else
      javaType = DataBuffer.TYPE_UNDEFINED;

    return javaType;
  }

  @Override
  public String toString()
  {
    return ToStringBuilder.reflectionToString( this );
  }
}
