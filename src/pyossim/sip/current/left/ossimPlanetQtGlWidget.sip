%Module pyossim 0

%Import QtOpenGL/QtOpenGLmod.sip

class ossimPlanetQtGlWidget : QGLWidget
{

%TypeHeaderCode
#include <osgGA/MatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osg/Node>
#include <osg/Timer>
#include <osg/Matrixd>
#include <osg/Material>
#include <osg/FrameStamp>
#include <osgDB/DatabasePager>
#include <osgGA/GUIEventHandler>
#include <osgGA/EventQueue>
#include <osgGA/EventVisitor>
#include <osgDB/ReadFile>
#include <osgDB/DatabasePager>
#include <osgViewer/ViewerEventHandlers>
#include <OpenThreads/ReentrantMutex>
#include <iostream>
#include <ossimPlanet/ossimPlanetLookAt.h>
#include <ossimPlanet/ossimPlanetViewer.h>
#include <ossimPlanet/ossimPlanetVisitors.h>
%End

public:
	ossimPlanetQtGlWidget( QWidget * parent /TransferThis/ = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
	ossimPlanetQtGlWidget( const QGLFormat & format, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
	virtual ~ossimPlanetQtGlWidget();

//	osgViewer::GraphicsWindow* getGraphicsWindow();
//	const osgViewer::GraphicsWindow* getGraphicsWindow() const; 

	void setMouseNavigationFlag(bool flag);
	bool getMouseNavigationFlag()const;

	virtual void dropEvent ( QDropEvent * event );
	virtual void dragEnterEvent(QDragEnterEvent *event);

signals:
	void signalMouseMoveEvent(QMouseEvent* event);
	void signalMousePressEvent(QMouseEvent* event);
	void signalMouseReleaseEvent(QMouseEvent* event);
	void signalMouseDoubleClickEvent(QMouseEvent* event);
	void signalViewPositionChangedLatLonHgtHPR(double lat, double lon, double height,
		double heading, double pitch, double roll);
	void signalDropEvent(QDropEvent * event);
	void signalDragEnterEvent(QDragEnterEvent *event);
};


//class ossimPlanetQtViewer : public ossimPlanetQtGlWidget
//{
//public:
//	ossimPlanetQtViewer(QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
//	ossimPlanetQtViewer( const QGLFormat & format, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0 );
//	virtual ~ossimPlanetQtViewer();
//	void setViewer(ossimPlanetViewer* viewer);
///	virtual void paintGL();
//	virtual void frameIfNeeded();
//	virtual void mouseMoveEvent( QMouseEvent* event );
//	ossimPlanetViewer* viewer();
//	void setCurrentSimulationTime(double simtime = USE_REFERENCE_TIME);
//	void setTargetFrameTimeInMilliseconds(float millisecondRate);
//	void setTargetFramesPerSecond(float framesPerSecond);
//};
