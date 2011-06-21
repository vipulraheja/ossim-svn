-- *!
-- *
-- * OVERVIEW:
-- *
-- * this app is a simple image copy. It will use
-- * the image writer factory to instantiate a registered
-- * writer and connect to the input and execute the writer.
-- *
-- * The writers can be instantiatd by class name or by output image
-- * type.  
-- *
-- * PURPOSE:
-- *
-- * Learn how to construct a writer from a factory. Connect the
-- * writer to the image loadeer/reader and output the image.
-- *
-- */
--
-- Author(s)
--   Original C++ version written by Garrett Potts
--   Converted to Ada by James E. Hopper
--
--

with Ada.Text_IO;
with Ada.Command_Line;
 use Ada.Command_Line;
with Interfaces; use Interfaces;
-- this is the most important class and is called as the first line of all applications.
-- without this alll the important factories are not created.
with Init;
with Ossim_Common; use Ossim_Common;
with Ossim_Constants;
 use Ossim_Constants;
with OssimString;
 use OssimString;
with Ossim.Factory.Imagewriter;
 use Ossim.Factory.Imagewriter;
with Ossim.Connectable.Source;
 use Ossim.Connectable.Source;
with Ossim.Connectable.Source.Output.Imagewriter.File;
 use Ossim.Connectable.Source.Output.Imagewriter.File;
with Ossim.Connectable.Source.Image.Handler;
 use Ossim.Connectable.Source.Image.Handler;
with Listener.Process.StdOutProgress;
 use Listener.Process.StdOutProgress;
with Ossim.Connectable;
 use Ossim.Connectable;
with Ossim.Connectable.Source.MetaData.Writer.File.Readme;
procedure image_copy is

	Open_Error		: Exception;
	Create_Exception: Exception;
	Image_Handler	: Image.Handler.Object;
	Image_Writer	: Output.Imagewriter.File.Object;
	Process 		: Listener.Process.StdOutProgress.Object;
	ReadMe			: Ossim.Connectable.Source.MetaData.Writer.File.Readme.Object;
	
    procedure PrintOutputTypes is
        OutputType : StringList;
    begin
        OutputType:= Ossim.Factory.Imagewriter.GetImageTypeList;
        for I in 0..Integer(GetNumberImageType(OutputType)) - 1 loop
            Ada.Text_IO.Put_Line(GetImageType(OutputType, ossim_uint32(I)));
        end loop;
    end PrintOutputTypes;
 
    procedure Usage is
    begin
        Ada.Text_IO.Put_Line("image_copy <output_type> <input filename> <output filename>");
		Ada.Text_IO.Put_Line("where output types are:");
        PrintOutputTypes;
    end Usage;

begin
    if Argument_Count /= 3 then
		Usage;
	else
		Init.Initialize;
		-- try to open up the passed in image
		--
        Image_Handler := Open(Argument(2));
        if Is_Null(Image_Handler) then
			Ada.Text_IO.Put_Line("Unable to open input image: " & Argument(2));
			raise Open_Error;
		end if;
		-- try to create a writer for the output image type.
		-- 
		Image_Writer := Ossim.Factory.Imagewriter.CreateWriter(Argument(1));
        if Is_Null(Image_Writer) then
            Ada.Text_IO.Put_Line("unable to create writer for " & Argument(1));
            raise Create_Exception;
        end if;
		-- specify the output file name
        Output.Imagewriter.File.SetFilename(Image_Writer, Argument(3));
		-- within OSSIM we have a concept of inputs that can be connected together
		-- writer have only 1 input and we index them starting from 0. If we only
		-- supplied the second argument it would find the first available input and connect
		-- it to that slot.  Here, we explicitly say connect the handler to slot 0 of the
		-- writer.
		-- 
		Ossim.Connectable.OssimConnectObject(Image_Writer, Image_Handler, 0);
		-- Optionally we can add listeners to listen for certain events.
		-- 
		-- all writers should execute event processing and generate a progress event.
		-- we have a default event listener that listens for this event and can be used
		-- to output the progress of the exected process.
		-- 
		--  the first argument is to specify the precision of the percent complete
		-- output, here we default to 0 for whole number outputs. The second argument
		-- specifies to flush the stream on each print If you don't want progress
		-- output then don't add this listener
		-- 
		-- the defalut standard out listener is found in base/common/ossimStdOutProgress.h"
		-- 
        Process:= Listener.Process.StdOutProgress.Create(0, True);
        if not Output.Imagewriter.File.AddListener(Image_Writer, Process) then
            Ada.Text_IO.Put_Line("Error adding Listener");
        end if;
		-- execute the writer.  Writer will start sequencing through
		-- all the tiles from the input and output it to disk.
		-- 
        Output.Imagewriter.File.Execute(Image_Writer);

		readMe :=  Ossim.Connectable.Source.MetaData.Writer.File.Readme.Create(
			Image_Handler, Argument(3) & ".readme");
		Ossim.Connectable.Source.MetaData.Writer.File.Readme.Execute(Readme);
		Ossim.Connectable.Source.MetaData.Writer.File.Readme.Delete(readMe);
		Free(Image_Writer);
		Free(Image_Handler);
		Init.Finalize;
	end if;
exception
	when Open_Error|Create_Exception =>
		null;
end image_copy;
