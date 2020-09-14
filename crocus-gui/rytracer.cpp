#include "rytracer.h"
#include <QPen>
#include <QPainter>
#include <QGridLayout>
#include <QPointF>
#include <QVBoxLayout>
#include <QMutex>
#include <QLabel>

QMutex mutex;

 static const QPointF points[3] = 
 {
     QPointF(10.0, 80.0),
     QPointF(20.0, 10.0),
     QPointF(200.0, 200.0),
 };

Rytracer::Rytracer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.action, SIGNAL(triggered()), this, SLOT(begin()));
	
}

Rytracer::~Rytracer()
{

}

void Rytracer::begin()
{
	
	canvas = new RenderCanvas;
	canvas->startRender();
	canvas->show();

}


// canvas class
 QSize RenderCanvas::sizeHint() const
 {
    return QSize(420, 420);
 }

 QSize RenderCanvas::minimumSizeHint() const
 {
     return QSize(100, 100);
 }


void RenderCanvas::startRender()
{

	thread = new RenderThread();

	connect(thread,SIGNAL(updateImage(const QImage& )),this,SLOT(OnUpdateImage(const QImage&)));

	thread->start();

}

void RenderCanvas::OnUpdateImage(const QImage& image)
{


	 QLabel *imageLabel = new QLabel;
	 imageLabel->setPixmap(QPixmap::fromImage(image));
	 
	 setBackgroundRole(QPalette::NoRole);
	 setWidget(imageLabel);

}



// render Thread 
void RenderThread::setPixel(int x, int y, int red, int green, int blue)
{
	int flip_y = world->vp.vres - 1 - y;
	image.setPixel(x,flip_y,qRgba(red,green,blue,255));
	changed = true;
}


void RenderThread::run()
{
	world = new World();

	world->build();

	world->thread = this; //Íê³É»¥ÏàÇ¶Ì×
	
	//image = QImage(world->vp.hres,world->vp.vres,QImage::Format_ARGB32); // changed after set stero camera
	//image.fill(qRgba(0, 0, 0, 0));

	world->camera_ptr->render_scene(*world);
	exec();
}

void RenderThread::notifyCanvas()
{
   if(changed)
	emit updateImage(image);
   changed = false;
}