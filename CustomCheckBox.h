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


        // ���Ƹ�ѡ��
        QStyleOptionButton opt;
        initStyleOption(&opt);

        QRect checkBoxRect = style()->subElementRect(QStyle::SE_CheckBoxIndicator, &opt, this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (isChecked())
        {
            // ����ѡ��ʱ��Բ�Ǳ���
            painter.setBrush(QColor("#BB9F5E"));  // ����ѡ��ʱ�ı�����ɫ
            painter.setPen(Qt::NoPen);  // ȥ���߿�
        }
        else
        {
            // ����δѡ��ʱ��Բ�Ǳ߿�
            painter.setBrush(Qt::NoBrush);  // ����䱳��
            painter.setPen(QPen(QColor("#8C8C8C"), 2));  // ʹ�û�ɫ�߿��߿�Ϊ2
        }

        // ����Բ�Ǿ��Σ�Բ�ǰ뾶Ϊ3
        painter.drawRoundedRect(checkBoxRect.adjusted(1, 1, -1, -1), 3, 3);

        // �����ѡ��ѡ�У����ư�ɫ�Ĺ�
        if (isChecked())
        {
            painter.setPen(QPen(Qt::white, 2));  // ���ù�����ɫΪ��ɫ���߿�Ϊ2

            // ʹ�� QPainterPath ���ƹ�����״
            QPainterPath checkMarkPath;
            checkMarkPath.moveTo(checkBoxRect.left() + checkBoxRect.width() * 0.3, checkBoxRect.center().y());
            checkMarkPath.lineTo(checkBoxRect.center().x()-2, checkBoxRect.bottom() - checkBoxRect.height() * 0.3);
            checkMarkPath.lineTo(checkBoxRect.right() - checkBoxRect.width() * 0.3, checkBoxRect.top() + checkBoxRect.height() * 0.35);
            painter.drawPath(checkMarkPath);  // ���ƹ�
        }

    }

};

#endif // CUSTOMCHECKBOX_H
