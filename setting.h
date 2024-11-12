#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QMouseEvent>
#include <QPainter>
namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    void loadQssFile();
protected:
    void mousePressEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    void paintEvent(QPaintEvent*event);

private:
    Ui::Setting *ui;
    bool isPressed{false};
    QPoint curPos;
};

#endif // SETTING_H
