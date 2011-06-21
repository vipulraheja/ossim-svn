//*****************************************************************************
// Copyright (C) 2003 James E. Hopper & ImageLinks Inc. 
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// You should have received a copy of the GNU General Public License
// along with this software. If not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
// 1307, USA.
//
// See the GPL in the COPYING.GPL file for more details.
//
// AUTHOR: James E. Hopper (hopperj@macconnect.com)
//         Garrett Potts (gpotts@imagelinks)
//
//*****************************************************************************
#include "ossimCImageFileWriter.h"
#include "imaging/formats/ossimImageFileWriter.h"
#include "imaging/factory/ossimImageWriterFactoryRegistry.h"
#include "base/data_types/ossimString.h"

#include "ossimCImageWriterFactoryRegistry.h"

    ossimImageWriterFactoryRegistryH instance();
    
    ossimImageFileWriterH createWriterKeyword(
            const ossimKeywordlistH kwl,
            const char *prefix) //default = 0
    {
        if(kwl)
        {
            return ossimImageWriterFactoryRegistry::instance()->
                createWriter(*((ossimKeywordlist*)kwl), prefix);
        }
        return (ossimImageFileWriterH)NULL;
    }
            
    ossimImageFileWriterH createWriter(
        const ossimStringH& typeName)
    {
        ossimImageFileWriterH result = (ossimImageFileWriterH)NULL;
        result = ossimImageWriterFactoryRegistry::instance()->
            createWriter(*(ossimString*)typeName);
        return result;
    }

    void getImageTypeList(ossimStringVectorH imageTypeList)
    {
        ossimImageWriterFactoryRegistry::instance()->getImageTypeList(
                            *(( std::vector<ossimString>*)imageTypeList));
    }
