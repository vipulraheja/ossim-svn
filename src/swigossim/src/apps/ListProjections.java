package apps;
import jossim.base.ossimStringVector;
import jossim.init.ossimInit;
import jossim.projection.ossimProjectionFactoryRegistry;

public class ListProjections
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
        ossimStringVector typeList = new ossimStringVector();
        ossimProjectionFactoryRegistry.instance().getTypeNameList( typeList );

        for ( int i = 0; i < typeList.size(); i++ )
        {
            System.out.println( typeList.get( i ).toString() );
        }
    }

}
