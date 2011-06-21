-- 
--  *  ossim-connectable-source-image-filter-casttilesource.adb
--  *  Ossim_Maps
--  *
--  *  Created by James E. Hopper on Thu Nov 13 2003.
--  *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
--  *
--  

package body Ossim.Connectable.Source.Image.Filter.CastTileSource is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;

    function Create(
            inputObject	: Ossim.Connectable.Object'class;
            ScalarType	: OssimScalarType) return Object is

        function Create(
            Source	: Void_Ptr;
            ScalarType  : OssimScalarType) return Void_Ptr;
        pragma Import(C, Create, "ossimCreateCastTileSourceFilter");

    begin
        return Create(Create(Ossim.C_Object(inputObject), ScalarType));
    end Create;

    procedure Delete(Cast : Object) is

        procedure Delete(Cast : Void_Ptr);
        pragma Import(C, Delete, "ossimDeleteCastTileSourceFilter");

    begin
        Delete(Ossim.C_Object(Cast));
    end Delete;

end Ossim.Connectable.Source.Image.Filter.CastTileSource;

