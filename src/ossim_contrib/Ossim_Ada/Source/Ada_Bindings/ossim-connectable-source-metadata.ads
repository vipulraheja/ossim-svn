-- 
--  *  ossim-connectable-source-metadata.ads
--  *  Ossim_Maps
--  *
--  *  Created by James E. Hopper on Sat Nov 15 2003.
--  *  Copyright (c) 2003 __MyCompanyName__. All rights reserved.
--  *
--  

package Ossim.Connectable.Source.MetaData is

    type Object is new Ossim.Connectable.Source.Object with private;

    function Create(C_Object : Void_Ptr) return Object;

private

    type Object is new Ossim.Connectable.Source.Object with
    record
        null;
    end record;

end Ossim.Connectable.Source.MetaData;
