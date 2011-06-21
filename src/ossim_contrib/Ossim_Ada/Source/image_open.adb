--
--
-- OVERVIEW:
--
-- this app is a simple image open.
-- It should open any image supported by the ossim library.
-- Once the image is open it prints out some general information
-- about the image.
--
-- PURPOSE:
--
-- Learn how to open an image and query attributes.  Also learn which
-- headers are required to perform these tasks.
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
with Ossim_Constants; 
 use Ossim_Constants;
-- within this program ossimCommon is used for ossimGetScalarSizeInBytes.
with Ossim_Common;
 use Ossim_Common;
-- this is the most important class and is called as the first line of all applications.
-- without this alll the important factories are not created.
with Init;
-- used to get the string name of the scalar type for the handler.  The scalar
-- type specifies if its unsigned char, float, double, ...etc
with LookupTable.Scalertypelut;
 use LookupTable.Scalertypelut;
with Ossim.Connectable.Source;
 use Ossim.Connectable.Source;
with Ossim.Connectable.Source.Image.Handler;
 use Ossim.Connectable.Source.Image.Handler;
with Ossim.Factory.Imagewriter;
 use Ossim.Factory.Imagewriter;
with Irect;
 use Irect;
procedure image_open is

	Image_Handler	: Image.Handler.Object; 
	Overviews		: Integer_32;
	Bounds			: IRect.Object;
	ScalarType		: ossimScalarType;
	Lut				: LookupTable.Scalertypelut.Object;

begin
    if Argument_Count = 1 then
		Init.Initialize;
		-- call the registries open and let it traverse through all registered
		-- factories to open up an image.
        Image_Handler := Open(Argument(1));
        if not Is_Null(Image_Handler) then
			 -- includes full resolution so if there are no overviews this value should be
			 -- 1. Note: resolution levels or overviews or indexed from 0 being full
			 -- resolution to (number of decimations or overviews -1..
			 --
			 -- Overviews are very import for resampling images to different resolutions efficiently.
			 -- The overviews are generally power of 2 decimations.  Assume we have an  image that has 
			 -- full resolution of 1024x1024 in size. When we are talking about resolution 0 then
			 -- we are talking about the full res 1024x1024, but when we are talking
			 -- about resolution level 1 then we are looking at the start of the overview and referes to
			 -- a decimation of 2^1 which is 512x512 image.  So when we ask for resolution level N then
			 -- we are talking about a decimation of 2^N
			 --
			 -- So again, when we query the number of decimation levels this includes resolution layer 0.
			 --
			Overviews := GetNumberOfDecimationLevels(Image_Handler);

			 -- the image bounds can take an argument to specify which resolution I would like to get
			 -- the bounding rect of.  By default if no argument is given it assumes full resolution or
			 -- resolution 0.
			 --
			 Bounds := GetBoundingRect(Image_Handler);

			 -- scalar type cooresponds to the pixel radiometry type.  The pixel can be of precision
			 -- float, double, unsigned char, unsigned short, signed short data values. Look at
			 -- ossimScalarType enumeration found in base/common/ossimConstants.h for supporting types
			 -- 
			ScalarType := GetOutputScalarType(Image_Handler);

			-- This is a utility class that maps enumeration values to strings.  So we will use this
			-- when we query the scalar type from the image and wish to print the text version of it.
			--
			--
			Lut := LookupTable.Scalertypelut.Create;
			
			Ada.Text_IO.Put_Line("filename        = " & GetFilename(Image_Handler));
			Ada.Text_IO.Put_Line("width           = " & ossim_uint32'image(IRect.width(bounds)));
			Ada.Text_IO.Put_Line("height          = " & ossim_uint32'image(IRect.height(bounds)));
			Ada.Text_IO.Put_Line("overview count  = " & Integer_32'image(overviews-1));
			Ada.Text_IO.Put_Line("scalar type     = " &  
				LookupTable.Scalertypelut.getEntryString(Lut, ScalarType));
			Ada.Text_IO.Put_Line("pixel size      = " & Ossim_Uint32'image(OssimGetScalarSizeInBytes(ScalarType)));
			Ada.Text_IO.Put_Line("Handler used    = " & Ossim.GetClassName(Image_Handler));
			
			Free(Image_Handler);
	 
 		else
            Ada.Text_IO.Put_Line("unable to open image " & Argument(1));
        end if;
		Init.Finalize;
    else
		Ada.Text_IO.Put_line("usage: open_image <file name>");
	end if;
end image_open;
