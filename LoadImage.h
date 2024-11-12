#pragma once

#include <QObject>
#include <QThread>
#include<QPixmap>
class LoadImage : public QThread
{
	Q_OBJECT

public:
	LoadImage(QObject *parent);
	~LoadImage();

	void loadImage();
	void setFPS(int fps);
	void stopThread();
protected:
	void run();
private:
	QVector<QString>imgNameList;
	int curIndex;
	int fps;
	bool stop;
signals:
		void sendPixmap(QPixmap pixmap);
};


