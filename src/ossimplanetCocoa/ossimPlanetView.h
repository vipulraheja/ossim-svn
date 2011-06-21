#import <Cocoa/Cocoa.h>

#include <vector>
#include <osg/ref_ptr>
#include <osg/Matrixd>
#include <osg/Timer>
#include <osgGA/GUIEventAdapter>

#include "ossimPlanetCocoaActionAdapter.h"

class ossimPlanet;
class ossimPlanetTextureLayerGroup;
class ossimPlanetSceneView;
class ossimPlanetDatabasePager;
class ossimPlanetManipulator;

namespace osg
{
	class Node;
	class Timer;
	class Material;
	class FrameStamp;
}

namespace osgGA
{
	class GUIEventHandler;
	class EventQueue;
	class EventVisitor;
	class MatrixManipulator;
	class StateSetManipulator;
}




    enum RedrawPolicy
    {
        ossimPlanetQtGlWidgetRedraw_AS_NEEDED=0,      ///< Only redraw as needed (Default), e.g. when a window is popped forward
        ossimPlanetQtGlWidgetRedraw_CONSTANT=1        ///< Redraw constantly
    };

// Subclass NSOpenGLView. We could subclass NSView instead, but NSOpenGLView is easy.
@interface ossimPlanetView : NSOpenGLView
{
	// Note: In Objective-C++, if you use objects instead of pointers as
	// member instance variables, you MUST turn on "Call C++ Default Ctors/Dtors in Objective-C".
	// -fobjc-call-cxx-cdtors
	// This option makes sure constructors and destructors are run.
	// This option is only available for gcc 4.0+ (Mac OS X 10.4+)


	
	
	osg::ref_ptr<ossimPlanet> thePlanet;

	std::vector<osg::ref_ptr<ossimPlanetTextureLayerGroup> > theTextureLayers;





	// This timer is used to trigger animation callbacks since everything is event driven.
	NSTimer* animationTimer;

        // triggers reading pending Actions from NetworkConnections
        NSTimer* networkConnectionTimer;

	// Flags to help track whether ctrl-clicking or option-clicking is being used
	BOOL isUsingCtrlClick;
	BOOL isUsingOptionClick;
	
	// Flag to track whether the OpenGL multithreading engine is enabled or not
	BOOL isUsingMultithreadedOpenGLEngine;
	
	
	
   bool                                    thePassAllUnhandledEventsFlag;
   osg::ref_ptr<osgGA::EventQueue>         theEventQueue;
   osg::ref_ptr<ossimPlanetSceneView>      theSceneView;
   osg::ref_ptr<osgGA::EventVisitor>       theEventVisitor;
   osg::ref_ptr<ossimPlanetDatabasePager>  theDatabasePager;
   osg::ref_ptr<osg::FrameStamp>           theFrameStamp;
   osg::ref_ptr<osgGA::GUIEventHandler>    theGuiEventHandler;
   osg::ref_ptr<ossimPlanetManipulator>    theMatrixManipulator;
   osg::ref_ptr<osgGA::StateSetManipulator> theStateSetManipulator;
   ossimPlanetCocoaActionAdapter              theActionAdapter;

   int                                     theTimerId;
//   QTimer *theQTimer;	// This  should always be accessed via the timer() method
/*    bool theContinualUpdateFlag; */
   RedrawPolicy theRedrawPolicy;
   osg::ref_ptr<osg::Material> theMaterial;
   
//   static osg::Timer theTimer;
//   static const osg::Timer_t theInitialTick;
	osg::Timer theTimer;
   osg::Timer_t theInitialTick;
   unsigned int theTimerInterval;
   bool         theMouseNavigationFlag;
   osg::Matrixd theProjToWindowMatrix;
   osg::Matrixd theWindowToProjMatrix;

   mutable double theUpdateTime;
   mutable double theCullTime;
   mutable double theDrawTime;
   mutable double theFrameTime;

   double theViewLat;
   double theViewLon;
   double theViewHgt;
   double theViewHeading;
   double theViewPitch;
   double theViewRoll;	
	
	
}

// My custom static method to create a basic pixel format
+ (NSOpenGLPixelFormat*) basicPixelFormat;


// Official init methods
+ (void) initialize;
- (id) initWithFrame:(NSRect)frame_rect pixelFormat:(NSOpenGLPixelFormat*)pixel_format;
- (id) initWithCoder:(NSCoder*)the_coder;
- (id) initWithFrame:(NSRect)frame_rect;

// Official function, overridden by this class to prevent flashing/tearing when in splitviews, scrollviews, etc.
- (void) renewGState;

// My custom function for minimization.
- (void) prepareForMiniaturization:(NSNotification*)notification;


// Custom function to allow users to know if the Multithreaded OpenGL Engine is enabled
- (BOOL) isUsingMultithreadedOpenGLEngine;

// Private init helper methods
- (void) initSharedOpenGLContext;
- (void) commonInit;
- (void) initOSGViewer;
- (void) initAnimationTimer;
- (void) initNetworkConnectionTimer;

// Official/Special NSOpenGLView method that gets called for you to prepare your OpenGL state.
- (void) prepareOpenGL;
// Class dealloc method
- (void) dealloc;
- (void) finalize;

// Official mouse event methods
- (void) mouseDown:(NSEvent*)the_event;
- (void) mouseDragged:(NSEvent*)the_event;
- (void) mouseUp:(NSEvent*)the_event;
- (void) rightMouseDown:(NSEvent*)the_event;
- (void) rightMouseDragged:(NSEvent*)the_event;
- (void) rightMouseUp:(NSEvent*)the_event;
- (void) otherMouseDown:(NSEvent*)the_event;
- (void) otherMouseDragged:(NSEvent*)the_event;
- (void) otherMouseUp:(NSEvent*)the_event;

// Private setter/getter methods to track ctrl/option-clicking
- (void) setIsUsingCtrlClick:(BOOL)is_using_ctrl_click;
- (BOOL) isUsingCtrlClick;
- (void) setIsUsingOptionClick:(BOOL)is_using_option_click;
- (BOOL) isUsingOptionClick;
// Private helper methods to help deal with mouse events
- (void) doLeftMouseButtonDown:(NSEvent*)the_event;
- (void) doLeftMouseButtonUp:(NSEvent*)the_event;
- (void) doRightMouseButtonDown:(NSEvent*)the_event;
- (void) doRightMouseButtonUp:(NSEvent*)the_event;
- (void) doMiddleMouseButtonDown:(NSEvent*)the_event;
- (void) doExtraMouseButtonDown:(NSEvent*)the_event buttonNumber:(int)button_number;
- (void) doMiddleMouseButtonUp:(NSEvent*)the_event;
- (void) doExtraMouseButtonUp:(NSEvent*)the_event buttonNumber:(int)button_number;

- (NSPoint) convertToOsgPoint:(NSPoint)the_pt;
// Official scrollWheel (scrollball) method
- (void) scrollWheel:(NSEvent*)the_event;


// Official methods for keyboard events
- (BOOL) acceptsFirstResponder;
- (void) keyDown:(NSEvent*)the_event;
- (void) keyUp:(NSEvent*)the_event;


// helper methods for keyboard events
- (void) handleModifiers:(NSEvent*)the_event;
// Note: Pass-by-ref is C++/Obj-C++ only. Return value says whether we found a key we could handle.
- (BOOL) getOsgKey:(osgGA::GUIEventAdapter::KeySymbol&)osg_key fromCocoaEvent:(NSEvent*)the_event;



// My custom method to handle timer callbacks
- (void) animationCallback;

// My custom callbacks method to handle reading NetworkConnections for Actions
- (void) networkConnectionCallback;

// Official methods for view stuff and drawing
- (BOOL) isOpaque;
- (void) resizeViewport;
- (void) reshape;
- (void) drawRect:(NSRect)the_rect;

// Private helper methods for drawing
- (void) updateScene;
- (void) renderScene;
- (NSBitmapImageRep*) renderOpenGLSceneToFramebuffer;
- (NSBitmapImageRep*) renderOpenGLSceneToFramebufferAsFormat:(int)gl_format viewWidth:(float)view_width viewHeight:(float)view_height;
- (NSBitmapImageRep*) renderOpenGLSceneToFramebufferAsFormat:(int)gl_format viewWidth:(float)view_width viewHeight:(float)view_height clearColorRed:(float)clear_red clearColorGreen:(float)clear_green clearColorBlue:(float)clear_blue clearColorAlpha:(float)clear_alpha;
- (NSImage*)imageFromBitmapImageRep:(NSBitmapImageRep*)bitmap_image_rep;


// Official methods for drag and drop (view as target)
- (unsigned int) draggingEntered:(id <NSDraggingInfo>)the_sender;
- (void) draggingExited:(id <NSDraggingInfo>)the_sender;
- (BOOL) prepareForDragOperation:(id <NSDraggingInfo>)the_sender;
- (BOOL) performDragOperation:(id <NSDraggingInfo>)the_sender;
- (void) concludeDragOperation:(id <NSDraggingInfo>)the_sender;

// Official method for copy (i.e. copy & paste)
- (IBAction) copy:(id)sender;

// Private helper methods for drag and drop and copy/paste (view as source)
- (NSData*) dataWithTIFFOfContentView;
- (NSData*) contentsAsDataOfType:(NSString *)pboardType;
- (void) startDragAndDropAsSource:(NSEvent*)the_event;


- (void) stopClearPaging;
- (void) clearPager;
- (void) startPaging;
- (void) setSceneData:(osg::Node*)scene_data;

// Problem: ossimPlanet contains view stuff, but is outside this class.
// Temporary workaround is to get access to the pointer.
- (void) setPlanet:(ossimPlanet*)the_planet;

// Note: Pass-by-ref is C++/Obj-C++ only.
- (void) getViewPositionLat:(double&)lat lon:(double&)lon height:(double&)height heading:(double&)heading pitch:(double&)pitch roll:(double&)roll;


// Bindings stuff
- (NSArray*) exposedBindings;


- (void) setHudEnabled:(BOOL)is_hud_enabled;
- (BOOL) isHudEnabled;


@end

