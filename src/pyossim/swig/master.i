%module pyossim

/* This tells SWIG to treat char ** as a special case */
%typemap(in) (int&, char **) 
{
        /* Check if is a list */
        if (PyList_Check($input)) 
        {
                $1 = PyList_Size($input);
        
                int i = 0;
                $2 = (char **) malloc(($1+1)*sizeof(char *));
                
                for (i = 0; i < $1; i++) 
                {
                        PyObject *o = PyList_GetItem($input,i);
                
                        if (PyString_Check(o))
                                $2[i] = PyString_AsString(PyList_GetItem($input,i));
                        
                        else 
                        {
                                PyErr_SetString(PyExc_TypeError,"list must contain strings");
                                free($2);
                                return NULL;
                        }
                }
                $2[i] = 0;
        } 
        
        else 
        {
                PyErr_SetString(PyExc_TypeError,"not a list");
                return NULL;
        }
}

/* This cleans up the char ** array we malloc'd before the function call */
%typemap(freearg) (int&, char **)
{
        free((char *) $2);
}

/* Importing Init Interfaces */
%include "init/ossimInit.i"

/* Importing Elevation Interfaces */
%include "elevation/ossimDtedElevationDatabase.i"
%include "elevation/ossimDtedFactory.i"
%include "elevation/ossimDtedHandler.i"
%include "elevation/ossimElevationDatabaseFactory.i"
%include "elevation/ossimElevationDatabase.i"
%include "elevation/ossimElevationDatabaseRegistry.i"
%include "elevation/ossimElevCellHandlerFactory.i"
%include "elevation/ossimElevCellHandler.i"
%include "elevation/ossimElevManager.i"
%include "elevation/ossimElevSourceFactory.i"
%include "elevation/ossimElevSource.i"
%include "elevation/ossimGeneralRasterElevationDatabase.i"
%include "elevation/ossimGeneralRasterElevFactory.i"
%include "elevation/ossimGeneralRasterElevHandler.i"
%include "elevation/ossimImageElevationDatabase.i"
%include "elevation/ossimImageElevationHandler.i"
%include "elevation/ossimSrtmElevationDatabase.i"
%include "elevation/ossimSrtmFactory.i"
%include "elevation/ossimSrtmHandler.i"


/* Importing Base Interfaces */
%include "base/ossim2dBilinearTransform.i"
%include "base/ossim2dLinearRegression.i"
%include "base/ossim2dTo2dIdentityTransform.i"
%include "base/ossim2dTo2dShiftTransform.i"
%include "base/ossim2dTo2dTransformFactory.i"
%include "base/ossim2dTo2dTransform.i"
%include "base/ossim2dTo2dTransformRegistry.i"
%include "base/ossimAdjustableParameterInfo.i"
%include "base/ossimAdjustableParameterInterface.i"
%include "base/ossimConnectableContainer.i"
%include "base/ossimConnectableContainerInterface.i"
%include "base/ossimConnectableDisplayListener.i"
%include "base/ossimConnectableObject.i"
%include "base/ossimConnectableObjectListener.i"
%include "base/ossimContainerEvent.i"
%include "base/ossimContainerProperty.i"
%include "base/ossimDataObject.i"
%include "base/ossimDateProperty.i"
%include "base/ossimDatumFactory.i"
%include "base/ossimDatumFactoryRegistry.i"
%include "base/ossimDatum.i"
%include "base/ossimDirectoryData.i"
%include "base/ossimDirectory.i"
%include "base/ossimDisplayEventListener.i"
%include "base/ossimDisplayInterface.i"
%include "base/ossimDisplayListEvent.i"
%include "base/ossimDisplayRefreshEvent.i"
%include "base/ossimDpt3d.i"
%include "base/ossimDpt.i"
%include "base/ossimEvent.i"
%include "base/ossimException.i"
%include "base/ossimFilename.i"
%include "base/ossimFilenameProperty.i"
%include "base/ossimIpt.i"
%include "base/ossimIrect.i"
%include "base/ossimLine.i"
%include "base/ossimListener.i"
%include "base/ossimListenerManager.i"
%include "base/ossimLsrPoint.i"
%include "base/ossimLsrRay.i"
%include "base/ossimLsrSpace.i"
%include "base/ossimLsrVector.i"
%include "base/ossimNadconGridDatum.i"
%include "base/ossimNadconGridFile.i"
%include "base/ossimNadconGridHeader.i"
%include "base/ossimNadconNarDatum.i"
%include "base/ossimNadconNasDatum.i"
%include "base/ossimObjectDestructingEvent.i"
%include "base/ossimObjectFactory.i"
%include "base/ossimObjectFactoryRegistry.i"
%include "base/ossimObject.i"
%include "base/ossimProperty.i"
%include "base/ossimPropertyInterfaceFactory.i"
%include "base/ossimPropertyInterface.i"
%include "base/ossimPropertyInterfaceRegistry.i"
%include "base/ossimString.i"
%include "base/ossimStringListProperty.i"
%include "base/ossimStringProperty.i"
%include "base/ossimViewController.i"
%include "base/ossimViewEvent.i"
%include "base/ossimViewInterface.i"
%include "base/ossimViewListener.i"


/* Importing Imaging Interfaces */
%include "imaging/ossimGeneralRasterInfo.i"
%include "imaging/ossimHistogramEqualization.i"
%include "imaging/ossimHistogramMatchFilter.i"
%include "imaging/ossimHistogramRemapper.i"
%include "imaging/ossimHistogramThreshholdFilter.i"
%include "imaging/ossimHistogramWriter.i"
%include "imaging/ossimHistoMatchRemapper.i"
%include "imaging/ossimIgenGenerator.i"
%include "imaging/ossimImageChain.i"
%include "imaging/ossimImageDataFactory.i"
%include "imaging/ossimImageFileWriter.i"
%include "imaging/ossimImageGeometryFactory.i"
%include "imaging/ossimImageGeometry.i"
%include "imaging/ossimImageGeometryRegistry.i"
%include "imaging/ossimImageHandler.i"
%include "imaging/ossimImageMetaData.i"
%include "imaging/ossimImageMetaDataWriterFactoryBase.i"
%include "imaging/ossimImageMetaDataWriterFactory.i"
%include "imaging/ossimImageMetaDataWriterRegistry.i"
%include "imaging/ossimImageModel.i"
%include "imaging/ossimImageMosaic.i"
%include "imaging/ossimImageSourceFactoryBase.i"
%include "imaging/ossimImageSourceFactory.i"
%include "imaging/ossimImageSourceFactoryRegistry.i"
%include "imaging/ossimImageSourceFilter.i"
%include "imaging/ossimImageSourceHistogramFilter.i"
%include "imaging/ossimImageSource.i"
%include "imaging/ossimImageSourceSequencer.i"
%include "imaging/ossimImageWriterFactoryBase.i"
%include "imaging/ossimImageWriterFactory.i"
%include "imaging/ossimImageWriterFactoryRegistry.i"
%include "imaging/ossimJpegWriter.i"
%include "imaging/ossimMetadataFileWriter.i"


/* Importing Projection Interfaces */
%include "projection/ossimImageProjectionModel.i"
%include "projection/ossimImageViewAffineTransform.i"
%include "projection/ossimImageViewProjectionTransform.i"
%include "projection/ossimImageViewTransformFactory.i"
%include "projection/ossimImageViewTransform.i"
%include "projection/ossimLandSatModel.i"
%include "projection/ossimMapProjectionFactory.i"
%include "projection/ossimMapProjection.i"
%include "projection/ossimMapProjectionInfo.i"
%include "projection/ossimMercatorProjection.i"
%include "projection/ossimObliqueMercatorProjection.i"
%include "projection/ossimOrthoGraphicProjection.i"
%include "projection/ossimProjectionFactoryBase.i"
%include "projection/ossimProjectionFactoryRegistry.i"
%include "projection/ossimProjection.i"
%include "projection/ossimProjectionViewControllerFactory.i"
%include "projection/ossimSensorModelFactory.i"
%include "projection/ossimSensorModel.i"
%include "projection/ossimSensorModelTuple.i"
%include "projection/ossimTransMercatorProjection.i"

/* Importing Util Interfaces */
%include "util/ossimElevUtil.i"
%include "util/ossimFileWalker.i"
%include "util/ossimInfo.i"
%include "util/ossimRpfUtil.i"

