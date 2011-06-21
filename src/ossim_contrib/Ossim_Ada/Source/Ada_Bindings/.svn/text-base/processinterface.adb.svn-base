-- 
--  *  processinterface.adb
--  *  Ossim_Maps
--  *
--  *  Created by James E. Hopper on Sat Nov 15 2003.
--  *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
--  *
--  

package body ProcessInterface is

    function Execute(theObject : Object) return Boolean is
    
        procedure Execute(theObject : Void_Ptr);
        pragma Import(C, Execute, "ossimExecute");

    begin
        Execute(C_Object(theObject));
		return true;
    end Execute;

end ProcessInterface;
