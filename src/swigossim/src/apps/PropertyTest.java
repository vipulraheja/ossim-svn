package apps;


import jossim.base.PropertyUtil;
import jossim.base.ossimFilename;
import jossim.base.ossimKeywordlist;
import jossim.base.ossimPropertyInterface;
import jossim.base.ossimPropertyRefPtr;
import jossim.base.ossimPropertyRefPtrVector;
import jossim.imaging.ossimImageHandler;
import jossim.imaging.ossimImageHandlerRegistry;
import jossim.imaging.ossimImageSource;
import jossim.init.ossimInit;


public class PropertyTest
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
        ossimInit.instance().initialize( args.length, args );

        ossimImageSource source = loadImage( args[0] );

        System.out.println( "width: " + source.getBoundingRect().width() );
        System.out.println( "height: " + source.getBoundingRect().height() );

        printProperties( source );
        printGeometry( source );
    }

    private static void printGeometry( ossimImageSource source )
    {
        ossimKeywordlist kwl = new ossimKeywordlist();

        source.getImageGeometry( kwl );
 
        System.out.println( kwl );
    }

    private static void printProperties( ossimPropertyInterface source )
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

    private static ossimImageSource loadImage( String filename )
    {
        ossimImageHandler handler = ossimImageHandlerRegistry.instance().open(
                new ossimFilename( filename ) );
        return handler;
    }

}
