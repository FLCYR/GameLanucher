#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>

namespace Ui {
class ManageWidget;
}
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

class ManageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManageWidget(QWidget *parent = nullptr);
    ~ManageWidget();
    void getDiskInfo(QString path);
protected:
    //void enterEvent(QEvent*e);
    void mouseMoveEvent(QMouseEvent*e);

    bool eventFilter(QObject*obj,QEvent*e);

private:
    Ui::ManageWidget *ui;

};

#endif // MANAGEWIDGET_H
