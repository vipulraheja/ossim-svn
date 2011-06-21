package org.ossim.imageio.spi;

import java.io.File;
import java.io.IOException;
import java.util.Locale;

import javax.imageio.ImageReader;
import javax.imageio.spi.ImageReaderSpi;

import jossim.base.ossimFilename;
import jossim.imaging.ossimImageHandler;
import jossim.imaging.ossimImageHandlerRegistry;

import org.ossim.imageio.OssimImageReader;

public class OssimImageReaderSpi extends ImageReaderSpi
{
  static final String vendorName = "L-3";

  static final String version = "1.0";

  static final String readerClassName = "org.ossim.imageio.OssimImageReader";

  static final String[] names = {
    "ossim"
  };

  static final String[] suffixes = {
      "tif", "jpg", "toc", "ntf"
  };

  static final String[] MIMETypes = {
    "image/x-ossim"
  };

  static final String[] writerSpiNames = {
    "org.ossim.imageio.OssimImageWriterSpi"
  };

  // Metadata formats, more information below
  static final boolean supportsStandardStreamMetadataFormat = false;

  static final String nativeStreamMetadataFormatName = null;

  static final String nativeStreamMetadataFormatClassName = null;

  static final String[] extraStreamMetadataFormatNames = null;

  static final String[] extraStreamMetadataFormatClassNames = null;

  static final boolean supportsStandardImageMetadataFormat = false;

  static final String nativeImageMetadataFormatName = "org.ossim.imageio.OssimMetadata_1.0";

  static final String nativeImageMetadataFormatClassName = "org.ossim.imageio.OssimMetadata";

  static final String[] extraImageMetadataFormatNames = null;

  static final String[] extraImageMetadataFormatClassNames = null;

  static final Class[] inputTypes = new Class[] {
    File.class
  };

  public OssimImageReaderSpi()
  {
    super( vendorName, version, names, suffixes, MIMETypes, readerClassName,
        inputTypes, writerSpiNames, supportsStandardStreamMetadataFormat,
        nativeStreamMetadataFormatName, nativeStreamMetadataFormatClassName,
        extraStreamMetadataFormatNames, extraStreamMetadataFormatClassNames,
        supportsStandardImageMetadataFormat, nativeImageMetadataFormatName,
        nativeImageMetadataFormatClassName, extraImageMetadataFormatNames,
        extraImageMetadataFormatClassNames );
  }

  public String getDescription( Locale locale )
  {
    // Localize as appropriate
    return "OSSIM Java Image I/O PlugIn";
  }

  public boolean canDecodeInput( Object input ) throws IOException
  {
    boolean status = false;

    if ( input instanceof File )
    {
      File imageFile = (File)input;
      ossimFilename fileName = new ossimFilename( imageFile.getAbsolutePath() );

      ossimImageHandler handler = ossimImageHandlerRegistry.instance().open(
          fileName );

      status = handler.isOpen();

      if ( status )
      {
        handler.close();
      }
    }

    return status;
  }

  public ImageReader createReaderInstance( Object extension )
  {
    return new OssimImageReader( this );
  }
}
