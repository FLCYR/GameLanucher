#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H


#include <QCheckBox>
#include <QPainter>
#include <QStyleOptionButton>
#include <QPainterPath>
class CustomCheckBox : public QCheckBox
{
    Q_OBJECT

public:
    CustomCheckBox(QWidget *parent = nullptr) : QCheckBox(parent)
    {

    }

protected:
    void paintEvent(QPaintEvent *event) override
    {


        QCheckBox::paintEvent(event);
        QPainter painter(this);


        // 绘制复选框
        QStyleOptionButton opt;
        initStyleOption(&opt);

        QRect checkBoxRect = style()->subElementRect(QStyle::SE_CheckBoxIndicator, &opt, this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (isChecked())
        {
            // 绘制选中时的圆角背景
            painter.setBrush(QColor("#BB9F5E"));  // 设置选中时的背景颜色
            painter.setPen(Qt::NoPen);  // 去除边框
        }
        else
        {
            // 绘制未选中时的圆角边框
            painter.setBrush(Qt::NoBrush);  // 不填充背景
            painter.setPen(QPen(QColor("#8C8C8C"), 2));  // 使用灰色边框，线宽为2
        }

        // 绘制圆角矩形，圆角半径为3
        painter.drawRoundedRect(checkBoxRect.adjusted(1, 1, -1, -1), 3, 3);

        // 如果复选框被选中，绘制白色的勾
        if (isChecked())
        {
            painter.setPen(QPen(Qt::white, 2));  // 设置勾的颜色为白色，线宽为2

            // 使用 QPainterPath 绘制勾的形状
            QPainterPath checkMarkPath;
            checkMarkPath.moveTo(checkBoxRect.left() + checkBoxRect.width() * 0.3, checkBoxRect.center().y());
            checkMarkPath.lineTo(checkBoxRect.center().x()-2, checkBoxRect.bottom() - checkBoxRect.height() * 0.3);
            checkMarkPath.lineTo(checkBoxRect.right() - checkBoxRect.width() * 0.3, checkBoxRect.top() + checkBoxRect.height() * 0.35);
            painter.drawPath(checkMarkPath);  // 绘制勾
        }

    }

};

#endif // CUSTOMCHECKBOX_H
