--*****************************************************************************
-- Copyright (C) 2003 James E. Hopper. 
--
-- This is free software; you can redistribute it and/or
-- modify it under the terms of the GNU General Public License
-- as published by the Free Software Foundation.
--
-- This software is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--
-- You should have received a copy of the GNU General Public License
-- along with this software. If not, write to the Free Software
-- Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
-- 1307, USA.
--
-- See the GPL in the COPYING.GPL file for more details.
--
-- AUTHOR: James E. Hopper (hopperj@macconnect.com)
--
--*****************************************************************************
package body ListenerManager is

    function AddListener(
            Writer		: Object;
            theListener : Listener.Process.StdOutProgress.Object) return Boolean is

        function AddListener(Writer : Void_Ptr;
                        theListener : Void_Ptr) return Boolean;
        pragma Import(C, AddListener, "ossimAddListener");

    begin
        return AddListener(C_Object(Writer), Listener.C_Object(
                theListener));
    end AddListener;

    function AddListener(
            Writer 		: Object;
            theListener : Listener.Process.ProgressPercent.Object) return Boolean is

        function AddListener(Writer 	: Void_Ptr;
                            theListener : Void_Ptr) return Boolean;
        pragma Import(C, AddListener, "ossimAddListener");

    begin
        return AddListener(C_Object(Writer), Listener.C_Object(
                theListener));
    end AddListener;

    function RemoveListener(
            Writer 		: Object;
            theListener 	: Listener.Process.StdOutProgress.Object) return Boolean is
        function RemoveListener(
            Writer 		: Void_Ptr;
            Listener 	: Void_Ptr) return Boolean;
        pragma Import(C, RemoveListener, "ossimRemoveListener");
    begin
        return RemoveListener(C_Object(Writer), Listener.C_Object(theListener));
    end RemoveListener;

    function RemoveListener(
            Writer 		: Object;
            theListener 	: Listener.Process.ProgressPercent.Object) return Boolean is
        function RemoveListener(
            Writer 		: Void_Ptr;
            Listener 	: Void_Ptr) return Boolean;
        pragma Import(C, RemoveListener, "ossimRemoveListener");
    begin
        return RemoveListener(C_Object(Writer), Listener.C_Object(theListener));
    end RemoveListener;

end ListenerManager;
