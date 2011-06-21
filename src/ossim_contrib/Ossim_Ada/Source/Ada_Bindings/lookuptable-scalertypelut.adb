-- 
--  *  lookuptable-scalertypelut.adb
--  *  Ossim_Maps
--  *
--  *  Created by James E. Hopper on Sun Nov 16 2003.
--  *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
--  *
--  
with Interfaces.C.Strings; use Interfaces.C.Strings;
package body LookupTable.Scalertypelut is

    function Create(C_Object : Void_Ptr) return Object is
        TheObject : Object;
    begin
        TheObject.OssimObject:= C_Object;
        return TheObject;
    end Create;

    function Create return Object is
    
        function ossimScalarTypeLut return Void_Ptr;
        pragma Import(C, ossimScalarTypeLut, "ossimScalarTypeLutW");
        
    begin	
        return Create(ossimScalarTypeLut);
    end Create;

    function getEntryString(
                    The_Object 		: Object;
                    Entry_Number	: OssimScalarType) return String is
            
        function getEntryString(
                Instance 	: Void_Ptr;
                Entry_Number	: OssimScalarType) return chars_ptr;
        pragma Import(C, getEntryString, "getEntryStringW");

        Scaler_Type : chars_ptr;
    
    begin
        Scaler_Type:= getEntryString(LookupTable.C_Object(The_Object), Entry_Number);
        return Value(Scaler_Type, (Strlen(Scaler_Type)));
    end getEntryString;

end LookupTable.Scalertypelut;
