###
# $Id$
#
# File: makedefs.pri
# 
# Included by qt project files to set common things.
###

###
# OSSIM_DEV_HOME is needed by project files so if not set in your environment
# you can set it here.  Usually this is the root development directory where 
# software is compiled.  Uncomment and edit as needed.
#
# Example:
#
#       /ossim_dev
#         /     \
#      ossim  ossim_qt
###
# OSSIM_DEV_HOME=/ossim_dev

###
# LOCAL_ROOT also used for linking things like geotiff and OpenThread which
# are typically installed in /usr/local or /opt/local
###
unix:LOCAL_ROOT=/usr/local
macx:LOCAL_ROOT=/opt/local

###
# Edit to set the destination directory for "make install" target.
###
INSTALL_PREFIX=$$LOCAL_ROOT
