--
--
-- OVERVIEW:
--
-- We will retrieve information from the input source and manipulate the data.
-- All filters will have a data access point called getTile that can take a
-- rectangle/region of interest and a resolution level.  Once we have
-- retrieved the data we will show documented examples on how to manipulate
-- the data.
--
--
-- PURPOSE:
--
-- 1. Learn how to request data from the connected input and output some basic
--    information about the requested area of interest
-- 2. Learn how to use ossimImageData object to manipulate pixel data.
-- 3. Learn how to query subregions and copy subregions.
-- 4. Understand what is a NULL, EMPTY, FULL, and PARTIAL data object.
--    this is very import for mosaicking and other pixel
--    manipulation filters.
--
--

-- this is the most important class and is called as the first line of all applications.
-- without this all the important factories are not created.
--
with System; use type System.Address;
with Interfaces.C.Extensions;
use Interfaces.C.Extensions;
with Ada.Text_IO;
with Ada.Float_Text_IO;
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
with IRect;
with OssimString;
with OssimString.Filename;
with Ossim.Connectable.Source;
 use Ossim.Connectable.Source;
with Ossim.Connectable.Source.Image;
 use Ossim.Connectable.Source.Image;
with Ossim.Connectable.Source.Image.Handler;
 use Ossim.Connectable.Source.Image.Handler;
with Ossim.Data.Rectilinear.Image;
 use Ossim.Data.Rectilinear.Image;
with LookupTable.Scalertypelut;
 use LookupTable.Scalertypelut;
with OssimImageDataFactory;
with Unchecked_Conversion;
procedure image_data is

	File_Name : OssimString.Filename.Object;
	procedure Usage is
	begin
		Ada.Text_IO.Put_Line("image_data <image file>");
	end Usage;
	
	--
	-- The data object status is very useful and is used to determine
	-- if the data is NULL( not initialized), empty (initialized but blank or empty,
	-- partial(contains some null/invalid values), or full (all valid data).
	--
	-- partial data means you have part of the information with valid data and the
	-- rest of it is set to the null or invalid pixel value for that band.
	--
	-- full data means that every pixel for each band has valid information.
	--
	-- empty means that no data is present
	--
	-- null means no data and the buffer is null.
	--
	-- For this status to be set on the ossimImageData there is a method
	-- validate that is called. Typically this is called when you implement
	-- a filter that changes the stored data.
	--
	procedure PrintDataStatus(status : ossimDataObjectStatus) is
	
	begin
	
		-- now lets output some of the information about the tile.  The tile
		-- 
		case status is
			when OSSIM_NULL =>
				Ada.Text_IO.Put_Line("data status = null");
			when OSSIM_EMPTY =>
				Ada.Text_IO.Put_Line("data status = empty");
			when OSSIM_PARTIAL =>
				Ada.Text_IO.Put_Line("data status = partial");
			when OSSIM_FULL =>
				Ada.Text_IO.Put_Line("data status = full");
			when others =>
				Ada.Text_IO.Put_Line("data status = unknown");
		end case;
	end PrintDataStatus;
	
	-- Demo 1 will retrieve a region of interest using the 
	-- ossimIrect which is an integer rectangle.
	-- 
	procedure Demo1(Filename : OssimString.Filename.Object) is
	
		Image_Handler		: Image.Handler.Object;
		RegionsOfInterest   : IRect.Object;
		Data				: Ossim.Data.Rectilinear.Image.Object;
		Bounds				: IRect.Object;
		Lut					: LookupTable.Scalertypelut.Object := 
									LookupTable.Scalertypelut.Create;
		UpperBound			: ossim_uint32;
		totalNumberOfPixels : Long_Float;
		sumOfThePixels		: Long_Float;
		np					: ossim_uint8;
		
	begin
		Ada.Text_IO.Put_Line("___________________________________DEMO 1_____________________________________");
        Image_Handler := Open(Filename);
        if Is_Null(Image_Handler) then
			Ada.Text_IO.Put_Line("Unable to open image: " & OssimString.GetString(Filename));
		else
			-- we will query the first 100 by 100 pixel of data from the input
			-- and compute the average value of each band.  We will only allow
			-- this to happen with unsigned char data.
			--
			-- Rectangles in ossim take absolute coordinates for upper
			-- left and lower right and does not take an upper left
			-- point and then a width height.  So if I want the data
			-- starting at point location 0,0 and ending at 100 pixels along
			-- the x and y direction then we have 0 to 99 along x = 100 and
			-- 0 to 99 along y = 100.
			--
			-- the second argument to getTile is optional and corresponds
			-- to the resolution level or overview.
			--
			RegionsOfInterest := IRect.Create(0,0, 99, 99);

			-- the data returned from the call getTile is not owned by you and
			-- you should not delete the pointer.
			--
			Data := GetTile(Image_Handler, RegionsOfInterest);
			If Ossim.Data.Rectilinear.Image.Is_Null(Data) then
				Ada.Text_IO.Put_Line("Data Handle is Null");
			else
				-- output the rectangle of the tile.
				Bounds:= Ossim.Data.Rectilinear.Image.GetImageRectangle(Data);
				Ada.Text_IO.Put_Line("tile rect =  ( " & ossim_int32'image(IRect.Left(Bounds)) & 
				" " & ossim_int32'image(IRect.Top(Bounds)) & " )( " & 
				ossim_int32'image(IRect.Right(Bounds)) & " " & ossim_int32'image(IRect.Bottom(Bounds))
				& " )");
			end if;
			-- output the status of the tile.  See printDataStatus above for
			-- documentation of status.
			PrintDataStatus(Ossim.Data.GetDataObjectStatus(Data));
			-- how many bands are there.
			--
			Ada.Text_IO.Put_Line("Number of bands = " & 
				ossim_uint32'image(Ossim.Data.Rectilinear.Image.getNumberOfBands(Data)));
			-- as in image_open lets use the scaler lut to pint the scalar type as a
			-- string.
			Ada.Text_IO.Put_Line("Pixel scalar type = " &
				LookupTable.Scalertypelut.getEntryString(Lut, Ossim.Data.Rectilinear.GetScalarType(Data)));
			-- for each band let's print the min, max and null pixel values
			-- note:  the min max values are not for the tile but for the entire
			--        input.  Typically these are used for tile normalization
			--        and clamping to data bounds.
			--
			Ada.Text_IO.Put("min pix: ");
			for i in 0..Integer(Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data)) - 1 loop
				Ada.Text_IO.Put(Integer'image(Integer(Ossim.Data.Rectilinear.Image.getMinPix(Data, ossim_uint32(i)))));
				if i < Integer(Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data)) - 1 then
					Ada.Text_IO.Put(", ");
				end if;
			end loop;
			Ada.Text_IO.New_Line;
			Ada.Text_IO.Put("max pix: ");
			for i in 0..Integer(Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data)) - 1 loop
				Ada.Text_IO.Put(Integer'image(Integer(Ossim.Data.Rectilinear.Image.getMaxPix(Data, ossim_uint32(i)))));
				if i < Integer(Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data)) - 1 then
					Ada.Text_IO.Put(", ");
				end if;
			end loop;
			Ada.Text_IO.New_Line;
			Ada.Text_IO.Put("null pix: ");
			for i in 0..Integer(Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data)) - 1 loop
				Ada.Text_IO.Put(Integer'image(Integer(Ossim.Data.Rectilinear.Image.getNullPix(Data, ossim_uint32(i)))));
				if i < Integer(Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data)) - 1 then
					Ada.Text_IO.Put(", ");
				end if;
			end loop;
			Ada.Text_IO.New_Line;
			if Ossim.Data.Rectilinear.GetScalarType(Data) = OSSIM_UCHAR then
				-- Now lets compute the average pixel for each band.  The data buffer is
				-- internally stored in osismImageData object as a void* buffer.  We must cast
				-- to the scalar type or work in normalized space.  For this example we will
				-- work the tile in its native type and will not normalize and we will also
				-- only work with unsigned char  or uchar data.
				--
				-- Note:  ossimImageData already has a compute mean and sigma.  We will re-implement
				--        some code here
				--
				-- I will implement a more efficient algorithm by only checking for invalid data
				-- if the status is not full.  If its full we don't have to check for
				-- null value and all we need to do is compute the sum.  Although we can just check for null
				-- all the time and not worry about 2 different loops.
				--
				UpperBound := Ossim.Data.Rectilinear.Image.getWidth(Data)*Ossim.Data.Rectilinear.Image.getHeight(Data);
				if Ossim.Data.GetDataObjectStatus(Data) = OSSIM_Full then

					-- since the data is full all pixls are used in the avverage
					for i in 0..Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data) - 1 loop
						totalNumberOfPixels := Long_Float(UpperBound);
						sumOfThePixels:= 0.0;
						-- get access to the raw band data.
						declare
							type Buffer is array(0..UpperBound) of ossim_uint8;
							type Buffer_Ptr is access Buffer;
							
							function Get_Buffer is new Ossim.Data.Rectilinear.Image.GetBuff_Band(Buffer_Ptr);
							Pixel_Buffer : Buffer_Ptr := Get_Buffer(Data, integer(i));
						begin
							for j in 0..UpperBound loop
								sumOfThePixels := sumOfThePixels + Long_Float(Pixel_Buffer(j));
							end loop;
						end;
						if totalNumberOfPixels > 0.0 then
							Ada.Text_IO.Put("band " & ossim_uint32'image(i) & " average = ");
							Ada.Float_Text_IO.Put(Float(sumOfThePixels/totalNumberOfPixels), Aft => 4, Exp =>0);
							Ada.Text_IO.New_Line;
						else
							Ada.Text_IO.Put_Line("band " & ossim_uint32'image(i) & " average = 0.0");
						end if;
					end loop;
					
				elsif Ossim.Data.GetDataObjectStatus(Data) = OSSIM_Partial then
					-- since tje data is full all pixls are used in the average
					for i in 0..Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data) - 1 loop
						totalNumberOfPixels := 0.0;
						sumOfThePixels:= 0.0;
						-- get access to the raw band data.
						declare
							type Buffer is array(0..UpperBound - 1) of ossim_uint8;
							type Buffer_Ptr is access Buffer;
							
							function Get_Buffer is new Ossim.Data.Rectilinear.Image.GetBuff_Band(Buffer_Ptr);
							Pixel_Buffer : Buffer_Ptr := Get_Buffer(Data, integer(i));
							
						begin
							np := ossim_uint8(Ossim.Data.Rectilinear.Image.getNullPix(Data, i));
							for j in 0..UpperBound - 1 loop
								if np /= Pixel_Buffer(j) then
									sumOfThePixels := sumOfThePixels + Long_Float(Pixel_Buffer(j));
									totalNumberOfPixels:= totalNumberOfPixels + 1.0;
								end if;
							end loop;
						end;
						if totalNumberOfPixels > 0.0 then
							Ada.Text_IO.Put("band " & ossim_uint32'image(i) & " average = ");
							Ada.Float_Text_IO.Put(Float(sumOfThePixels/totalNumberOfPixels), Aft => 4, Exp =>0);
							Ada.Text_IO.New_Line;
						else
							Ada.Text_IO.Put_Line("band " & ossim_uint32'image(i) & " average = 0.0");
						end if;
					end loop;
					
				end if;
			else
				Ada.Text_IO.Put_Line("Demo 1 only works for uchar data images");
			end if;
		end if;
		
		Ossim.Connectable.Source.Image.Handler.Free(Image_Handler);
		Ada.Text_IO.Put_Line("_________________________________END DEMO 1___________________________________");
	end Demo1;

	-- Demo 2 will show how to create your own data objects
	-- there are several ways to do this.
	procedure Demo2(Filename : OssimString.Filename.Object) is

		Image_Handler	: Image.Handler.Object;
		Data			: Ossim.Data.Rectilinear.Image.Object;
		DupData			: Ossim.Data.Rectilinear.Image.Object;
		Data2			: Ossim.Data.Rectilinear.Image.Object;
		Null_Source		: Ossim.Connectable.Source.Object := 
					Ossim.Connectable.Source.Create(System.Null_Address);
		NewRect			: IRect.Object;

	begin
		Ada.Text_IO.Put_Line("___________________________________DEMO 2_____________________________________");
        Image_Handler := Open(Filename);
        if Is_Null(Image_Handler) then
			Ada.Text_IO.Put_Line("Unable to open image: " & OssimString.GetString(Filename));
		else
			-- Create image data using the factory technique.
			-- This might be the best way to do it.  We might have optimized
			-- implementations for certain input types.  For instance you might
			-- want to create an ossimImageData that is optimized for 3 band
			-- ossim_uint8 data.
			--
			-- there other create methods but this takes as its 
			-- first argument a source that owns this data object
			-- and the second argument is the input source to use
			-- to help instantiate the object.  Please refer to 
			-- ossim_core/imaging/factory/ossimImageDataFactory
			-- for further implementation
			--
			Data := OssimImageDataFactory.Create(Null_Source, Image_Handler);
		   -- note: the data is not initialized/allocated.  We have 
		   -- a concept of a NULL or un initialized tile so all the
		   -- meta data is carried with it but just don't take up space
		   -- by allocating the buffer.  The number of bands, the rectangle
		   -- of interest, min, max, null are all set.
		   --
		   -- We will now initialize the data.  The initialize will
		   -- allocate the buffer based on the number of bands, width,
		   -- height and scalar type and then will set the buffer to 
		   -- the null pixel value and set the status OSSIM_EMPTY.
		   --
		   Ossim.Data.Rectilinear.Image.Initialize(Data);
			-- if you ever want to see if the initialization has been
			-- done then you must call isInitialize.
			--
			Ada.Text_IO.Put_Line("data initialized: " & 
				Boolean'image(Ossim.Data.Rectilinear.Image.isInitialize(Data)));

			-- To make a duplicate copy of the ossimImageData the easiest
			-- way to do this is to call the dup method.
			--
			DupData := Ossim.Data.Rectilinear.Image.Dup(Data);
			
			NewRect:= IRect.Create(10,20,200,200);

			-- this particualr method will reallocate the tile
			-- if already initialized and set it to the new
			-- rectangle of interest.
			--
			Ossim.Data.Rectilinear.Image.SetImageRectangle(DupData,NewRect);

			-- allocating without the factory
			-- 
			Data2 := Ossim.Data.Rectilinear.Image.Create(
				Null_Source,
				OSSIM_UCHAR, -- what scalar type
				3,  -- number of bands
				128, -- width
				128); -- height
		   Ossim.Data.Rectilinear.Image.Initialize(Data2);

			-- delete the allocated data objects.
			Ossim.Data.Rectilinear.Image.Free(DupData);
			Ossim.Data.Rectilinear.Image.Free(Data);
			Ossim.Data.Rectilinear.Image.Free(Data2);
		end if;
		Ossim.Connectable.Source.Image.Handler.Free(Image_Handler);
		Ada.Text_IO.Put_Line("_________________________________END DEMO 2___________________________________");
	end Demo2;

	procedure Demo3(Filename : OssimString.Filename.Object) is

		Image_Handler	: Image.Handler.Object;
		Data			: Ossim.Data.Rectilinear.Image.Object;
		Data2			: Ossim.Data.Rectilinear.Image.Object;
		Bounds			: IRect.Object;
		Status			: ossimDataObjectStatus;
		Null_Source		: Ossim.Connectable.Source.Object := 
					Ossim.Connectable.Source.Create(System.Null_Address);

	begin
		Ada.Text_IO.Put_Line("___________________________________DEMO 3_____________________________________");
        Image_Handler := Open(Filename);
        if Is_Null(Image_Handler) then
			Ada.Text_IO.Put_Line("Unable to open image: " & OssimString.GetString(Filename));
		else
			-- lets just get some data. we will get a 128 by 
			-- 128 tile that has upper left origin at 10, 10.
			--
			Bounds := IRect.Create(10, 10, 10+127, 10+127);
			Data := Ossim.Connectable.Source.Image.GetTile(Image_Handler, Bounds);
			if Ossim.Data.Rectilinear.Image.Is_Null(Data) then
				Ada.Text_IO.Put_Line("Failed to get tile");
			else
				Bounds:= Ossim.Data.Rectilinear.Image.GetImageRectangle(Data);
				Ada.Text_IO.Put_Line("Data rectangle =  ( " & ossim_int32'image(IRect.Left(Bounds)) & 
				" " & ossim_int32'image(IRect.Top(Bounds)) & " )( " & 
				ossim_int32'image(IRect.Right(Bounds)) & " " & ossim_int32'image(IRect.Bottom(Bounds))
				& " )");
				Data2 := OssimImageDataFactory.Create(Null_Source, Image_Handler);
				Bounds:= IRect.Create(0, 0, 127, 127);
				Ossim.Data.Rectilinear.Image.SetImageRectangle(Data2, Bounds);
				Ossim.Data.Rectilinear.Image.Initialize(Data2);
				Bounds:= Ossim.Data.Rectilinear.Image.GetImageRectangle(Data2);
				Ada.Text_IO.Put_Line("Data 2 rectangle =  ( " & ossim_int32'image(IRect.Left(Bounds)) & 
				" " & ossim_int32'image(IRect.Top(Bounds)) & " )( " & 
				ossim_int32'image(IRect.Right(Bounds)) & " " & ossim_int32'image(IRect.Bottom(Bounds))
				& " )");

				-- now load the data 2 region with data.  Notice the
				-- tile overlaps the data tile and only the 
				-- overlapping region is copied.
				--
				Ossim.Data.Rectilinear.Image.LoadTile(Data2, Data);
				
				-- now we can use the raw load tile where you supply the
				-- rectangle.  Now if you do this your buffer is assumed
				-- to have the same number of bands.
				--
				-- Now you must pass in the interleave type of your buffer
				-- The ossimImageData has interleave band sequential, OSSIM_BSQ
				-- which means the bands are sequential in memory where
				-- all of band 1 data followed by all of band 2 ... etc.  
				-- The other interleave type are OSSIM_BIP or band
				-- interleaved by pixel.  For instance if you had an RGB
				-- data object then it would be RGB, RGB, RGB ... etc.
				-- The final interleave type is by line OSSIM_BIL.  This
				-- just says band 1 line1 followed by band2 line2 ... etc until all
				-- lines are stored.
				--
				Ada.Text_IO.Put_Line("loading data2 rectangle");
				declare
					
					function Get_Buffer is new Ossim.Data.Rectilinear.Image.GetBuff(Void_ptr);
					Pixel_Buffer : Void_ptr := Get_Buffer(Data);
					
				begin
					Bounds:= Ossim.Data.Rectilinear.Image.GetImageRectangle(Data);
					Ossim.Data.Rectilinear.Image.LoadTile(Data2, Pixel_Buffer, Bounds, OSSIM_BSQ);
				end;

				-- I manipulated the buffer so lets validate it for future 
				-- use.  I would only validate after you get done doing your
				-- data manipulation.
				--
				Status := Ossim.Data.Rectilinear.Image.Validate(Data2);
				
				Ada.Text_IO.Put_Line("status after load is should be partial");
				PrintDataStatus(Ossim.Data.GetDataObjectStatus(Data2));
				
				-- loadBand has simalar arguments but allows
				-- you to do band loads.
				--
				declare
					
					function Get_Buffer is new Ossim.Data.Rectilinear.Image.GetBuff(Void_ptr);
					Pixel_Buffer : Void_ptr := Get_Buffer(Data);
					
				begin
					Bounds:= Ossim.Data.Rectilinear.Image.GetImageRectangle(Data);
					for i in 0..Ossim.Data.Rectilinear.Image.GetNumberOfBands(Data) - 1 loop
						Ossim.Data.Rectilinear.Image.LoadBand(Data2, Pixel_Buffer, Bounds, i);
					end loop;
				end;

				-- I manipulated the buffer so lets validate it for future 
				-- use.  I would only validate after you get done doing your
				-- data manipulation.
				--
				Status := Ossim.Data.Rectilinear.Image.Validate(Data2);

				-- please refer to ossim_core/imaging/ossimImageData.h for 
				-- other load methods
				--
			end if;

		end if;
		Ossim.Connectable.Source.Image.Handler.Free(Image_Handler);
		Ada.Text_IO.Put_Line("_________________________________END DEMO 3___________________________________");
	end Demo3;
	
begin
    if Argument_Count /= 1 then
		Usage;
	else
		Init.Initialize;
		
		File_Name := OssimString.Filename.Create(Argument(1));
		-- demo 1 we will access some data from the input and print
		-- some basic information about the data dn then access the data
		-- buffers for each band.
		--
		Demo1(File_Name);


		-- Demo 2 just shows ways to allocate the ossimImageData
		--
		Demo2(File_Name);

       -- Demo 3 just show how to load region of a tile
       --
       Demo3(File_Name);

		Init.Finalize;
	end if;
end image_data;
