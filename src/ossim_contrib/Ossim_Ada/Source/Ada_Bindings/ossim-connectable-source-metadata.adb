-- 
--  *  ossim-connectable-source-metadata.adb
--  *  Ossim_Maps
--  *
--  *  Created by James E. Hopper on Sat Nov 15 2003.
--  *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
--  *
--  

package body Ossim.Connectable.Source.MetaData is

    function Create(C_Object : Void_Ptr) return Object is
       the_Object : Object;
    begin
        the_Object.OssimObject:= C_Object;
        return the_Object; 
    end Create;
    
end Ossim.Connectable.Source.MetaData;
