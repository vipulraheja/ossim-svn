-- 
--  *  lookuptable-scalertypelut.ads
--  *  Ossim_Maps
--  *
--  *  Created by James E. Hopper on Sun Nov 16 2003.
--  *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
--  *
--  
with Interfaces; use Interfaces;
with Interfaces.C.Extensions;
 use Interfaces.C.Extensions;
with Ossim_Constants;
 use Ossim_Constants;
package LookupTable.Scalertypelut is

    type Object is new LookupTable.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;

    function getEntryString(
                    The_Object 	: Object;
                    Entry_Number: OssimScalarType) return String;

private

    type Object is new LookupTable.Object with
    record
        null;
    end record;

end LookupTable.Scalertypelut;
