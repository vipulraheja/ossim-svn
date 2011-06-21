default: 
	(cd Ada_Bindings; $(MAKE))
	(cd C_Bindings; $(MAKE))
image_copy: 
	gnatmake -g -IAda_Bindings/ image_copy -largs -L../ -lossimbindings -L/usr/local/lib -lossim -lstdc++
image_open: 
	gnatmake -g -IAda_Bindings/ image_open -largs -L../ -lossimbindings -L/usr/local/lib -lossim -lstdc++
image_data: 
	gnatmake -g -IAda_Bindings/ image_data -largs -L../ -lossimbindings -L/usr/local/lib -lossim -lstdc++
