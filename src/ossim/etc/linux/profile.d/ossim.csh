###
# $Id: ossim.csh 9909 2006-11-17 20:18:29Z dburken $
# For csh / tcsh users do: source omar.sh
# The '.' is a dot.
# 
# Edit prefix as needed:
###
set ossim_bin=/usr/local/ossim/bin
if ( "${path}" !~ *$ossim_bin* ) then
   set path = ( $ossim_bin $path )
endif



