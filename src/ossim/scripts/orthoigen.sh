#!/bin/bash
#--------------------------------------------------------------------
# -*-Shell-script-*-
#
# Script wrapper for ossim igen application.  Intention is to set
# environment up for application, then call it.
#
# License: LGPL
#
#--------------------------------------------------------------------
# $Id: orthoigen.sh 8065 2005-09-12 15:30:21Z dburken $

# Source the environment file.
. /usr/local/ossim/bin/ossim_environment

###
# Call the orthoigen application passing all args.
# We're going to use the full path to avoid problems with MPI.
###
/usr/local/ossim/bin/orthoigen $*
