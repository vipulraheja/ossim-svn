package apps;

import java.awt.Point;
import java.awt.Rectangle;
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
import java.util.Vector;


import jossim.base.PropertyUtil;
import jossim.base.ossimCoordSysOrientMode;
import jossim.base.ossimIrect;
import jossim.base.ossimPropertyRefPtr;
import jossim.base.ossimScalarType;
import jossim.base.ossimString;
import jossim.base.ossimStringVector;
import jossim.imaging.ImagingUtil;
import jossim.imaging.ossimImageDataRefPtr;
import jossim.imaging.ossimImageSource;

public class ossimRenderedImage implements RenderedImage
{
    protected ossimImageSource imageSource;

    public ossimRenderedImage( ossimImageSource imageSource )
    {
        this.imageSource = imageSource;
    }

    public Vector getSources()
    {
        // TODO Auto-generated method stub
        return null;
    }

    public Object getProperty( String name )
    {
        ossimString propName = new ossimString( name );
        ossimPropertyRefPtr property = imageSource.getProperty( propName );
        String value = PropertyUtil.getValue( property );

        return value;
    }

    public String[] getPropertyNames()
    {
        ossimStringVector nameVector = new ossimStringVector();

        imageSource.getPropertyNames( nameVector );

        String[] names = new String[(int)nameVector.size()];

        for ( int i = 0; i < names.length; i++ )
        {
            names[i] = nameVector.get( i ).toString();
        }

        return names;
    }

    public ColorModel getColorModel()
    {
        int dataType = ossimToJavaType( imageSource.getOutputScalarType() );

        ColorModel colorModel = new ComponentColorModel( ColorSpace
                .getInstance( ColorSpace.CS_sRGB ), false, false,
                ColorModel.OPAQUE, dataType );

        return colorModel;
    }

    public SampleModel getSampleModel()
    {
        int dataType = ossimToJavaType( imageSource.getOutputScalarType() );
        int numBands = (int)imageSource.getNumberOfOutputBands();

        SampleModel sampleModel = new BandedSampleModel( dataType, getWidth(),
                getHeight(), numBands );

        return sampleModel;
    }

    public int getWidth()
    {
        return (int)imageSource.getBoundingRect().width();
    }

    public int getHeight()
    {
        return (int)imageSource.getBoundingRect().height();
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
        int width = getWidth();
        int tileWidth = getTileWidth();
        int numXTiles = width / tileWidth;

        if ( width % tileWidth > 0 )
            numXTiles++;

        return numXTiles;
    }

    public int getNumYTiles()
    {
        int height = getHeight();
        int tileHeight = getTileHeight();
        int numYTiles = height / tileHeight;

        if ( height % tileHeight > 0 )
            numYTiles++;

        return numYTiles;
    }

    public int getMinTileX()
    {
        return 0;
    }

    public int getMinTileY()
    {
        return 0;
    }

    public int getTileWidth()
    {
        return (int)imageSource.getTileWidth();
    }

    public int getTileHeight()
    {
        return (int)imageSource.getTileHeight();
    }

    public int getTileGridXOffset()
    {
        return 0;
    }

    public int getTileGridYOffset()
    {
        return 0;
    }

    public Raster getTile( int tileX, int tileY )
    {
        int tileWidth = getTileWidth();
        int tileXOffset = tileX * tileWidth;
        int tileHeight = getTileHeight();
        int tileYOffset = tileY * tileHeight;
        int numBands = (int)imageSource.getNumberOfOutputBands();

        // Raster raster = Raster.createInterleavedRaster( DataBuffer.TYPE_BYTE,
        // tileWidth, tileHeight, numBands, new Point( tileXOffset,
        // tileYOffset ) );

        Raster raster = Raster.createBandedRaster( DataBuffer.TYPE_BYTE,
                tileWidth, tileHeight, numBands, new Point( tileXOffset,
                        tileYOffset ) );

        DataBufferByte byteBuffer = (DataBufferByte)raster.getDataBuffer();
        byte[][] bytes = byteBuffer.getBankData();

        ossimIrect irect = new ossimIrect( tileXOffset, tileYOffset,
                tileXOffset + tileWidth - 1, tileYOffset + tileHeight - 1,
                ossimCoordSysOrientMode.OSSIM_LEFT_HANDED );

        ossimImageDataRefPtr imageData = imageSource.getTile( irect );

        for ( int i = 0; i < bytes.length; i++ )
        {
            ImagingUtil.unloadBand( imageData, irect, i, bytes[i] );
        }

        return raster;
    }

    public Raster getData()
    {
        // TODO Auto-generated method stub
        return null;
    }

    public Raster getData( Rectangle rect )
    {
        ossimIrect irect = new ossimIrect( rect.x, rect.y, rect.width,
                rect.height );

        ossimImageDataRefPtr imageData = imageSource.getTile( irect );
        int numBands = (int)imageSource.getNumberOfOutputBands();

        Raster raster = Raster.createBandedRaster( DataBuffer.TYPE_BYTE,
                rect.width, rect.height, numBands, new Point( 0, 0 ) );

        DataBufferByte byteBuffer = (DataBufferByte)raster.getDataBuffer();
        byte[][] bytes = byteBuffer.getBankData();

        for ( int i = 0; i < bytes.length; i++ )
        {
            ImagingUtil.unloadBand( imageData, irect, i, bytes[i] );
        }
        
        return raster;
    }

    public WritableRaster copyData( WritableRaster arg0 )
    {
        // TODO Auto-generated method stub
        return null;
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
}
