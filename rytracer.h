#ifndef __RYTRACER__
#define __RYTRACER__

#include <vector>

#include <QtGui/QMainWindow>
#include <QScrollArea>
#include <QtCore/QThread>
#include <QtCore/QTimer>
#include <QPalette>
#include <QImage>
#include <QPixmap>


#include "ui_rytracer.h"

#include "World.h"

using namespace std;

class RenderCanvas;
class RenderThread;
class RenderPixel;

class Rytracer : public QMainWindow
{
	Q_OBJECT

public:

	Rytracer(QWidget *parent = 0);
	~Rytracer();


public slots:

	void begin();

private:

	Ui::RytracerClass ui;
	RenderCanvas*	canvas;
};


class RenderCanvas : public QScrollArea
{
	Q_OBJECT

public:

	RenderCanvas(QWidget * parent = 0):QScrollArea(parent)
	{
		setBackgroundRole(QPalette::Light);
		setAutoFillBackground(false);
	};

	~RenderCanvas(){};

	void startRender();

	QSize sizeHint() const;
	QSize minimumSizeHint() const;


public slots:

	void OnUpdateImage(const QImage& image);


 //protected:
 //    void paintEvent(QPaintEvent *event);

public:

	QPixmap pixmap;
	World*		world;
	RenderThread*	thread;

};

class RenderThread : public QThread
{
	Q_OBJECT

public:

	RenderThread()
	{
		changed = false;
		timer = new QTimer(this);
		connect(timer,SIGNAL(timeout()),this,SLOT(notifyCanvas()));
		timer->start(40);

	};

	~RenderThread(){};

	void run();

	void setPixel(int x,int y, int red, int green, int blue);

	
public slots:

	void notifyCanvas();

signals:

	void updateImage(const QImage& image);

public:

	QTimer*			timer;
	World*			world;
	vector<RenderPixel*>	pixels;
	vector<RenderPixel*> *pixelsUpdate;
	QImage			image;
	bool			changed;
};


class RenderPixel
{
public:
	RenderPixel(int _x, int _y, int _red ,int _green, int _blue)
		:x(_x),y(_y),red(_red),green(_green),blue(_blue){};

public:
	int x,y;
	int red,green,blue;
};

#endif 
