%Module pyossim 0

%Import QtGui/QtGuimod.sip
%Import QtCore/QtCoremod.sip

class ossimPlanetQtApplication: QApplication
{

%TypeHeaderCode
#include <osg/ArgumentParser>
#include <osg/ApplicationUsage>
#include <ossimPlanet/ossimPlanetConstants.h>
#include <ossim/base/ossimConstants.h>
#include <ossim/base/ossimFilename.h>
#include <ossimPlanet/ossimPlanetArchiveMapping.h>
#include <deque>
#include <ossimPlanet/ossimPlanetTextureLayerRegistry.h>
#include <ossimPlanet/ossimPlanetTextureLayer.h>
#include <ossimPlanetQt/ossimPlanetQtExport.h>
%End

public:
	typedef std::deque<osg::ref_ptr<ossimPlanetTextureLayer> > ReferenceImageListType;
	virtual ~ossimPlanetQtApplication();
	ossimPlanetQtApplication(int & argc, char ** argv, bool guiEnabled=true);

	static QString userSupportDirectory();
	static QString userDirectory();
	static QString sessionDirectory();
	static QString defaultSession();
	static QString defaultWmsCacheDir();
	static QString currentOpenSessionDirectory();
	static void setCurrentOpenSessionDirectory(const QString& dir);
	static QString currentOpenImageDirectory();
	static void setCurrentOpenImageDirectory(const QString& dir);
	static QString currentOpenKmlDirectory();
	static void setCurrentOpenKmlDirectory(const QString& dir);
	static QString currentOpenVideoDirectory();
	static void setCurrentOpenVideoDirectory(const QString& dir);
	static void addCommandLineOptions(osg::ArgumentParser& args);
	static bool initWithArgs(int& argc, char** argv);
	static ossimFilename compassRing();

	static QString stagingCacheDirectory();
	static void setStagingCacheDirectory(const QString& dir);
	static bool autoGenerateOverviewFlag();
	static void setAutoGenerateOverviewFlag(bool flag);
	static void setAutoHistogramStretchMode(const QString& setting);
	static QString autoHistogramStretchMode();
	static double wmsNetworkTimeoutInSeconds();
	static void setWmsNetworkTimeoutInSeconds(double seconds);
	static bool autoViewSyncFlag();
	static void setAutoViewSyncFlag(bool flag);
	static double autoViewSyncRateInSeconds();
	static void setAutoViewSyncRateInSeconds(double value);
	static bool autoHighlightLineOfSitFlag();
	static void setAutoHighlightLineOfSitFlag(bool flag);
	static void setElevFlag(bool flag);
	static bool elevEnabled();
	static std::string textureDetailType();
	static void setTextureDetailType(const std::string& type);
	static std::string elevationDetailType();
	static void setElevationDetailType(const std::string& type);
	static std::string cullAmountType();
	static void setCullAmountType(const std::string& type);
	static void setElevExag(ossim_float32 value);

	static ossim_float32 elevExag();
	static ossim_float32 splitMetricRatio();
	static ossim_uint32 elevEstimate();
	static void setEphemerisEnabledFlag(bool flag);

	static bool ephemerisEnabled();

	static void setEphemerisAutoUpdateToCurrentTimeFlag(bool flag);
	static bool ephemerisAutoUpdateToCurrentTimeFlag();
	static void setSunlightEnabledFlag(bool flag);

	static bool sunlightEnabled();
	static void setMoonEnabledFlag(bool flag);

	static bool moonEnabled();

	static void setSkyEnabledFlag(bool flag);
	static bool skyEnabled();
	static void setCloudsEnabledFlag(bool flag);
	static bool cloudsEnabled();
	static void setCloudCoverage(int value);
	static int cloudCoverage();
	static void setCloudSharpness(double value);
	static double cloudSharpness();
	static void setPercentVisibility(int value);
	static int percentVisibility();
	static const ossimFilename elevCacheDir();
	static ossim_uint32 levelOfDetail();
	static void setAutomaticStagingEnabledFlag(bool flag);
	static bool automaticStagingEnabledFlag();
	static void setHudFlag(bool flag);

	static bool hudEnabled();
	static bool mipMapping();

	static void setArchiveMappingEnabledFlag(bool flag);
	static bool archiveMappingEnabled();
	static void setSousaIdentityUserName(const QString& value);
	static QString sousaIdentityUserName();
	static void setSousaIdentityDomain(const QString& value);
	static QString sousaIdentityDomain();
	static void setSousaConnectionAutoConnectOnStart(bool value);
	static bool sousaConnectionAutoConnectOnStart();

	static void setSousaConnectionName(const QString& value);
	static QString sousaConnectionName();
	static void setSousaConnectionIp(const QString& value);
	static QString sousaConnectionIp();
	static void setSousaConnectionPort(const QString& value);
	static QString sousaConnectionPort();
	static void setSousaConnectionPortType(const QString& value);
	static QString sousaConnectionPortType();
	static std::deque<osg::ref_ptr<ossimPlanetTextureLayer> >& referenceImages();

	static ossimFilename themePath();
	static QStringList wmsSettingsSubkeyList();
	static QString readWmsSettingsEntry(const QString& key);
	static void writeWmsSettingsEntry(const QString& key,
			const QString& value);
	static void removeWmsSettingsKey(const QString& key);
	static QStringList preferenceSettingsSubkeyList(const QString& key);
	static void removePreferenceSetting(const QString& key);
	static QString readPreferenceSetting(const QString& key);
	static void    writePreferenceSetting(const QString& key,
		const QString& value);

	static QString readSettingsEntry(const QString& entry);
	static QStringList settingsSubKeyList(const QString& key);
	static void writeSettingsValue(const QString& key,
			const QString& value);
	static void settingsRemoveKey(const QString& key);    
	static long initInputDevices();
	static void terminateInputDevices();
/*
protected:
	static QSettings*                           theSettings;
	static QString                              theUserSupportDirectory;
	static QString                              theUserDirectory;
	static ReferenceImageListType               theReferenceImages;
	static std::vector<ossimFilename>           thePlugins;
	static ossimFilename                        theThemePath;
	static ossimFilename                        theCompassRing; 
	// static ossimFilename                        theCompassRose; */
};
