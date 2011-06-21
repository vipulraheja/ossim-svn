//
//  AppController.h
//  ossimplanetCocoa
//
//  Created by Eric Wing on 4/22/07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include <osg/ref_ptr>


@class ossimPlanetView;

class ossimPlanet;


@interface AppController : NSObject {
	IBOutlet ossimPlanetView* glView;
	osg::ref_ptr<ossimPlanet> thePlanet;
}

+ (void) initialize;

- (id) init;
- (void) dealloc;
- (void) finalize;
- (void) awakeFromNib;


- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)the_application;



@end
