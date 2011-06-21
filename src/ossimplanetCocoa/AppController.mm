//
//  AppController.m
//  ossimplanetCocoa
//
//  Created by Eric Wing on 4/22/07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import "AppController.h"

#import "ossimPlanetCocoaConstants.h"
#import "ossimplanetView.h"

#include <ossimPlanet/ossimPlanet.h>
#include <ossimPlanet/ossimPlanetTextureLayerRegistry.h>
#include <ossim/init/ossimInit.h>
#include <ossimPlanet/ossimPlanet.h>
#include <ossimPlanet/ossimPlanetLand.h>
#include <ossimPlanet/ossimPlanetTextureLayerRegistry.h>
#include <osg/ArgumentParser>
#include <osg/ApplicationUsage>
#include <osgDB/FileUtils>
//#include <wms/wms.h>
#include <ossim/base/ossimEnvironmentUtility.h>
#include <ossim/base/ossimKeywordlist.h>
#include <ossim/base/ossimDirectory.h>
#include <ossim/base/ossimArgumentParser.h>
#include <osg/Texture>



#if  !defined(_WIN32) && !defined(__WIN32__) && !defined(_MSC_VER)
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/errno.h>
static int getMaximumFiles() 
{
    int result = -1;
    struct rlimit lim;
    if ( getrlimit(RLIMIT_NOFILE, &lim) == 0 ) 
    {
        result = (int)lim.rlim_max;
    };

    return result;
}

static int setMaximumFiles(int filecount)
{
   struct rlimit lim;
   lim.rlim_cur = lim.rlim_max = (rlim_t)filecount;
   if ( setrlimit(RLIMIT_NOFILE, &lim) == 0 )
   {
      return 0;
   }
   else
   {
      return errno;
   }
}
#else
static int setMaximumFiles(int filecount)
{
   return 0;
}
static int getMaximumFiles()
{
   return 0;
}
#endif

static void addCommandLineOptions(osg::ArgumentParser& args)
{
   args.getApplicationUsage()->setApplicationName(args.getApplicationName());
   args.getApplicationUsage()->setDescription(args.getApplicationName()+" is the test application for accessing wms servers.");
   args.getApplicationUsage()->setCommandLineUsage(args.getApplicationName()+" [options] ...");
   args.getApplicationUsage()->addCommandLineOption("-h or --help","Display this information");
   args.getApplicationUsage()->addCommandLineOption("--enable-flatland", "Uses the flat land model");
   args.getApplicationUsage()->addCommandLineOption("--disable-elevation", "Uses elevation");
   args.getApplicationUsage()->addCommandLineOption("--elev-estimation", "number of levels to estimate.  A value of 4 will say 2^4 or 16 number of rows and cols.");
   args.getApplicationUsage()->addCommandLineOption("--elev-patchsize", "number of points in each chunk.");
   args.getApplicationUsage()->addCommandLineOption("--elev-exag", "Multiplier for the height values");
   args.getApplicationUsage()->addCommandLineOption("--elev-cache", "Cache directory for elevation");
   args.getApplicationUsage()->addCommandLineOption("--level-detail", "Maximum level of detail to split to.  Default is 16 levels");
   args.getApplicationUsage()->addCommandLineOption("--enable-hud", "Enables the lat lon read outs");
}

/* There is a lesser known feature of UserDefaults where you may actually supply the
 * keys as command line parameters to override the defaults at launch. These overrides
 * are not persistent (though if you set a value during the program, the new values
 * become persistent). So for example, you might pass the switch -hudEnabled YES to
 * activate the HUD. 
 * Unfortunately, this switch convention is orthogonal to the pre-existing command line parser.
 * This function is an attempt to mimic the behavior of user defaults so we may make the existing
 * command line parameter syntax behave like UserDefaults. For a given key,
 * it sets the new value and then marks the value as volatite and removes it as persistent.
 * This is not identical to the UserDefaults behavior and has some subtle differences.
 * First, the key is removed from the persistent list in this function, whereas it seems to live
 * in both lists in the official behavior. But if I fail to remove it in this function, the key
 * still acts persistent so this had to be done. Second, if the user modifies a value during the 
 * run of the program for an overriden key, the key does not become persistent unlike the official
 * behavior. If you expect your option to be saved, don't run using non-UserDefaults switches.
 */
static void OverrideNSUserDefaultsWithTemporaryValue(NSString* user_defaults_key, NSObject* new_value)
{
	NSUserDefaults* user_defaults = [NSUserDefaults standardUserDefaults];
	NSString* bundle_identifier = [[NSBundle mainBundle] bundleIdentifier];
//		NSLog(@"key=%@, object=%@", user_defaults_key, new_value);

	// Must set this before doing the domain change or it gets written back to the persistent domain.
	[user_defaults setObject:new_value forKey:user_defaults_key];

	NSDictionary* dict_of_key_value_to_override = [NSDictionary dictionaryWithObjectsAndKeys:new_value, user_defaults_key, nil];
//		NSLog(@"dict_of_key_value_to_override = %@", dict_of_key_value_to_override);

	// The key is in the persistent domain, so we want to remove it from that so the new (override) value won't be permanent
	NSDictionary* the_persist_dict = [user_defaults persistentDomainForName:bundle_identifier];
	NSMutableDictionary* the_persist_dict_minus_override_key;
	if(the_persist_dict != nil)
	{
		the_persist_dict_minus_override_key = [[the_persist_dict mutableCopy] autorelease];
		[the_persist_dict_minus_override_key removeObjectForKey:user_defaults_key];
	}
	else
	{
		the_persist_dict_minus_override_key = [[dict_of_key_value_to_override mutableCopy] autorelease];
	}
//		NSLog(@"the_persist_dict_minus_override_key = %@", the_persist_dict_minus_override_key);
//	NSLog(@"persistentDomainForName0:%@ %@", bundle_identifier, [user_defaults persistentDomainForName:[[NSBundle mainBundle] bundleIdentifier]]);

	// Clear the persistent domain of this bundleIdentifier so we can reset it with the new dictionary
	[user_defaults removePersistentDomainForName:bundle_identifier];

//	NSLog(@"persistentDomainForName1:%@ %@", bundle_identifier, [user_defaults persistentDomainForName:[[NSBundle mainBundle] bundleIdentifier]]);

	// Reset the persistent domain with the new dictionary
	[user_defaults setPersistentDomain:the_persist_dict_minus_override_key forName:bundle_identifier];
//	NSLog(@"persistentDomainForName2:%@ %@", bundle_identifier, [user_defaults persistentDomainForName:bundle_identifier]);

	// Get the existing volatile dictionary and add this key to the list
	NSMutableDictionary* new_volatile_dict;
	if([user_defaults volatileDomainForName:NSArgumentDomain] != nil)
	{
		new_volatile_dict = [[[user_defaults volatileDomainForName:NSArgumentDomain] mutableCopy] autorelease];
		[new_volatile_dict addEntriesFromDictionary:dict_of_key_value_to_override];
	}
	else
	{
		new_volatile_dict = [[dict_of_key_value_to_override mutableCopy] autorelease];
	}
//				NSLog(@"new_volatile_dict = %@", new_volatile_dict);

	// Clear the NSArgumentDomain so we can set it with the appended list
	[user_defaults removeVolatileDomainForName:NSArgumentDomain];
	// Set the NSArgumentDomain with the new list
	[user_defaults setVolatileDomain:new_volatile_dict forName:NSArgumentDomain];
	
//	NSLog(@"persistentDomainForName3:%@ %@", bundle_identifier, [user_defaults persistentDomainForName:bundle_identifier]);
//	NSLog(@"volatileDomainForName:NSArgumentDomain %@", [user_defaults volatileDomainForName:NSArgumentDomain]);
	
}

@implementation AppController
   
+ (void) initialize
{
	// NSUserDefaults stuff
	NSDictionary* application_defaults = [NSDictionary dictionaryWithObjectsAndKeys:
		[NSNumber numberWithBool:YES], OSSIMPLANETCOCOA_HUD_ENABLED,
		[NSNumber numberWithBool:YES], OSSIMPLANETCOCOA_ELEVATION_ENABLED,
		[NSNumber numberWithFloat:1.0f], OSSIMPLANETCOCOA_ELEVATION_EXAG,
		[NSNumber numberWithUnsignedInt:16], OSSIMPLANETCOCOA_ELEVATION_ESTIMATE,
		[NSNumber numberWithUnsignedInt:(unsigned int)ossimPlanetLandType_NORMALIZED_ELLIPSOID], OSSIMPLANETCOCOA_LAND_TYPE,
		[NSNumber numberWithUnsignedInt:20], OSSIMPLANETCOCOA_LEVEL_OF_DETAIL,
		nil];
	[[NSUserDefaults standardUserDefaults] registerDefaults:application_defaults];
	[[NSUserDefaultsController sharedUserDefaultsController] setInitialValues:application_defaults];
	
}

- (id) init
{
	self = [super init];
	if(self)
	{
		if(getMaximumFiles() < 1024)
		{
			setMaximumFiles(1024);
		}  
//		ossimInit::instance()->initialize();
	
		thePlanet = new ossimPlanet;
	}
	return self;
}

- (void) dealloc
{
	thePlanet = NULL;	
	[super dealloc];
}

- (void) finalize
{
	thePlanet = NULL;
	[super finalize];
}

// Remember that this class must be set as the delegate to NSApplication for this
// this to have any effect. This may be set through either IB or calling
// [NSApp setDelegate:self]; in awakeFromNib
- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)the_application
{
	return YES;
}

- (void) awakeFromNib
{
	[glView setPlanet:thePlanet.get()];

	[glView setSceneData:thePlanet.get()];
   
   	NSUserDefaults* user_defaults = [NSUserDefaults standardUserDefaults];
   	NSUserDefaultsController* user_defaults_controller = [NSUserDefaultsController sharedUserDefaultsController];

	[glView bind:@"hudEnabled" toObject:user_defaults_controller withKeyPath:@"values.hudEnabled" options:nil];
   
   
   
   
	bool theHudEnabled = [user_defaults boolForKey:OSSIMPLANETCOCOA_HUD_ENABLED];
	bool theElevEnabled = [user_defaults boolForKey:OSSIMPLANETCOCOA_ELEVATION_ENABLED];
	ossim_float32 theElevExag = [user_defaults floatForKey:OSSIMPLANETCOCOA_ELEVATION_EXAG];
	ossim_uint32 theElevEstimate = [[user_defaults objectForKey:OSSIMPLANETCOCOA_ELEVATION_ESTIMATE] unsignedIntValue];
	ossimPlanetLandType theLandType = static_cast<ossimPlanetLandType>([[user_defaults objectForKey:OSSIMPLANETCOCOA_LAND_TYPE] unsignedIntValue]);
	ossim_uint32 theLevelOfDetail = [[user_defaults objectForKey:OSSIMPLANETCOCOA_LEVEL_OF_DETAIL] unsignedIntValue];
	ossimFilename theElevCache;
	
	osgDB::DatabasePager* databasePager = osgDB::Registry::instance()->getOrCreateDatabasePager();

    // set wether the DatabasePager thread should be blocked while the scene graph is being used to render a frame
    // setting frame block to true can help achieve constant frame rates on single CPU systems.
    databasePager->setUseFrameBlock(true);
    
	
	NSArray* command_line_arguments = [[NSProcessInfo processInfo] arguments];
	NSEnumerator* argument_enumerator = [command_line_arguments objectEnumerator];
	int my_argc;
	my_argc = [command_line_arguments count];
	// This would probably be much less painful with C99.
	char** my_argv;
	// Allocate an argv large enough to hold all arguments.
	my_argv = (char**)malloc(my_argc*sizeof(char*));
	NSString* an_argument;
	int current_argv_index = 0;

	while (an_argument = [argument_enumerator nextObject])
	{
		NSLog(@"an_argument: %@", an_argument);
		size_t string_length = strlen([an_argument UTF8String]);
		// For each argv[] entry, allocate enough space to copy the argument string
		my_argv[current_argv_index] = (char*)calloc((string_length+1),sizeof(char)); // don't forget to add 1 for the NULL character
		strncpy(my_argv[current_argv_index], [an_argument UTF8String], string_length);
		current_argv_index++;
	}


   ossimArgumentParser argumentParser(&my_argc, my_argv);


   

   ossimInit::instance()->setPluginLoaderEnabledFlag(false);
   ossimInit::instance()->initialize(argumentParser);
   osg::ArgumentParser arguments(&argumentParser.argc(),argumentParser.argv());
   
   std::string tempString;
   osg::ArgumentParser::Parameter stringParam(tempString);
   addCommandLineOptions(arguments);
   
	if(arguments.read("-h") || arguments.read("--help"))
	{
		arguments.getApplicationUsage()->write(std::cout);
		[[NSApplication sharedApplication] terminate:nil];
	}
   
	if(arguments.read("--enable-flatland"))
	{
		theLandType = ossimPlanetLandType_FLAT;
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_LAND_TYPE, [NSNumber numberWithUnsignedInt:static_cast<unsigned int>(ossimPlanetLandType_FLAT)]);
	}
	if(arguments.read("--disable-elevation"))
	{
		theElevEnabled = false;
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_ELEVATION_ENABLED, [NSNumber numberWithBool:NO]);
	}
	if(arguments.read("--elev-estimation", stringParam))
	{
		theElevEstimate = 1<<ossimString(tempString.c_str()).toUInt32();
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_ELEVATION_ESTIMATE, [NSNumber numberWithUnsignedInt:theElevEstimate]);
	}
	if(arguments.read("--elev-patchsize", stringParam))
	{
		theElevEstimate = ossimString(tempString.c_str()).toUInt32();
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_ELEVATION_ESTIMATE, [NSNumber numberWithUnsignedInt:theElevEstimate]);
	}
	if(arguments.read("--elev-exag", stringParam))
	{
		theElevExag = ossimString(tempString.c_str()).toDouble();
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_ELEVATION_EXAG, [NSNumber numberWithFloat:theElevEstimate]);
	}
	if(arguments.read("--elev-cache", stringParam))
	{
		theElevCache = tempString.c_str();
	}
	if(arguments.read("--level-detail", stringParam))
	{
		theLevelOfDetail = ossimString(tempString.c_str()).toUInt32();
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_LEVEL_OF_DETAIL, [NSNumber numberWithUnsignedInt:theLevelOfDetail]);
	}
	if(arguments.read("--enable-hud"))
	{
		theHudEnabled = true;
		OverrideNSUserDefaultsWithTemporaryValue(OSSIMPLANETCOCOA_HUD_ENABLED, [NSNumber numberWithBool:YES]);
	}  
	arguments.reportRemainingOptionsAsUnrecognized();
	
	if (arguments.errors())
	{
		arguments.writeErrorMessages(std::cout);
	}
	
   ossimFilename referenceImageBundle;
   ossimInit::instance()->setPluginLoaderEnabledFlag(true);
#ifdef __MACOSX__
   // test for a bundle
   //
   ossimFilename currentPath = ossimFilename(argv[0]).path();
   ossimFilename contentsFolder = currentPath.path();

   // Check for embedded geoid grid nder the resource folder Resources/egm96.grd
   ossimFilename resourceFolder = contentsFolder.dirCat("Resources");
   ossimFilename geoid1996File = resourceFolder.dirCat("egm96.grd");
   if(geoid1996File.exists())
   {
      ossimRefPtr<ossimGeoid> geoid96 = new ossimGeoidEgm96;
      if(geoid96->open(geoid1996File, OSSIM_BIG_ENDIAN))
      {
         ossimGeoidManager::instance()->addGeoid(geoid96.get());
      }
   }

   // Check for embedded plugins and reference images

   ossimFilename ossimPluginsBundle = contentsFolder.dirCat("plugins");
   ossimFilename osgPlugins         = contentsFolder.dirCat("osgplugins");
   referenceImageBundle = contentsFolder.dirCat("Resources");
   referenceImageBundle = referenceImageBundle.dirCat("images");
   referenceImageBundle = referenceImageBundle.dirCat("reference");
   if(ossimPluginsBundle.exists())
   {
      ossimInit::instance()->loadPlugins(ossimPluginsBundle);
   }
   osgDB::Registry::instance()->getLibraryFilePathList().push_back(osgPlugins);

//    addLibraryPath(contentsFolder.dirCat("qtplugins").c_str());
#endif
   // we will now initialize any other plugins outside the bundle in standard locations
   //
   ossimInit::instance()->initializePlugins();

    osg::ref_ptr<ossimPlanetTextureLayerGroup> layers = new ossimPlanetTextureLayerGroup();

   if(arguments.argc() > 1)
   {
      ossimKeywordlist kwl;
      if(kwl.addFile(arguments.argv()[1]))
      {
         osg::ref_ptr<ossimPlanetTextureLayer> layer = ossimPlanetTextureLayerRegistry::instance()->createLayer(kwl.toString());
         if(layer.valid())
         {
                     layers->addTop(layer.get());
         }
      }
   }
   else
   {
	

      ossimFilename userDir    = ossimEnvironmentUtility::instance()->getUserOssimSupportDir();
      ossimFilename installDir = ossimEnvironmentUtility::instance()->getInstalledOssimSupportDir();
      ossimFilename refFile;
      bool userOverrideFlag = false;
      userDir = userDir.dirCat("images");
      userDir = userDir.dirCat("reference");
      installDir = installDir.dirCat("images");
      installDir = installDir.dirCat("reference");
      if(userDir.exists())
      {
         refFile = userDir;
      }
      else if(installDir.exists())
      {
         refFile = installDir;
      }
      if(refFile.exists())
      {
         ossimDirectory dir;
         if(dir.open(refFile))
         {
            ossimFilename file;
            dir.getFirst(file);
            do
            {
               ossimString ext = file.ext();
               if((ext != "ovr")&&
                  (ext != "omd")&&
                  (ext != "geom")&&
                  (ext != "his"))
               {
                  osg::ref_ptr<ossimPlanetTextureLayer> layer = ossimPlanetTextureLayerRegistry::instance()->createLayer(ossimString(file.c_str()));
                  if(layer.valid())
                  {
                     layers->addTop(layer.get());
                  }
               }
               
            }while(dir.getNext(file));
         }
      }
   }

   layers->sortByGsd();
   thePlanet->getLand()->setTextureLayer(layers.get());
 //  thePlanet->setEnableHudFlag(theHudEnabled);
//	[glView setHudEnabled:theHudEnabled];
     thePlanet->getLand()->setLandType(theLandType);
   thePlanet->getLand()->setElevationEnabledFlag(theElevEnabled);
   thePlanet->getLand()->setHeightExag(theElevExag);
   thePlanet->getLand()->setElevationPatchSize(theElevEstimate);
   thePlanet->getLand()->setMaxLevelDetail(theLevelOfDetail);
   thePlanet->getLand()->setElevationCacheDir(theElevCache);
   thePlanet->getLand()->resetGraph();








	// Must free the allocated memory in my_argv
	for(current_argv_index=0; current_argv_index<my_argc; current_argv_index++)
	{
//		NSLog(@"argv_argument: %s", my_argv[current_argv_index]);
		// Must free each string
		free(my_argv[current_argv_index]);
		 my_argv[current_argv_index] = NULL;
	}
	// Must free the argv array.
	free(my_argv);
	my_argv = NULL;


}


@end
