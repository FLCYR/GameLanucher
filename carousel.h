#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

namespace Ui {
class Carousel;
}

class Carousel : public QWidget
{
    Q_PROPERTY(qreal offset READ getOffset WRITE setOffset) //添加新属性，用于属性动画
    Q_OBJECT
public:
    explicit Carousel(QWidget *parent = nullptr);
    ~Carousel();

    void createAnimations();
    qreal getOffset();
    void setOffset(qreal offset);
protected:
    void enterEvent(QEvent*e);
    void leaveEvent(QEvent*e);
    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent*e);

private:
    Ui::Carousel *ui;
    QTimer * nextTimer;
    QVector<QImage>imgArr;
    QVector<QString>urls;
    int curIndex;
    int nextIndex;
    bool left;
    qreal offset;
    QPropertyAnimation*animation;

};

#endif // CAROUSEL_H
