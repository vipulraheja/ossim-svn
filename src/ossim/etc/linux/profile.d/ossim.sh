###
# $Id: ossim.sh 9909 2006-11-17 20:18:29Z dburken $
# For sh / bash users do: . omar.sh
# The '.' is a dot.
# 
# Edit prefix as needed:
###
ossim_bin=/usr/local/ossim/bin
if ! echo ${PATH} | /bin/grep -q $ossim_bin ; then
   PATH=$ossim_bin:${PATH}
fi

export PATH
