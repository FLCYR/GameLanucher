#include <QRadioButton>
#include <QPainter>
#include <QStyleOptionButton>
#include <QStyle>
#include <QDebug>
class CustomRadioButton : public QRadioButton
{
    Q_OBJECT

public:
    CustomRadioButton(QWidget* parent = nullptr) : QRadioButton(parent)
    {
    

    }

protected:
    void paintEvent(QPaintEvent* event) override
    {

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);


        QStyleOptionButton option;
        initStyleOption(&option);
        painter.save();



        // ��ȡ��ѡ��ľ�������
        QRect radioButtonRect = style()->subElementRect(QStyle::SE_RadioButtonIndicator, &option, this);

        // ����ѡ��ĳߴ�
        int enlargedSize = 24;  // �Զ��嵥ѡ��Ĵ�С�������Ĵ�С��
        radioButtonRect.setWidth(enlargedSize);
        radioButtonRect.setHeight(enlargedSize);

      
       
        painter.setBrush(Qt::NoBrush);  // ����䱳��
        painter.setPen(QPen(QColor("#8C8C8C"), 2));  // ʹ�û�ɫ�߿��߿�Ϊ2

        // ���������Բ�εĵ�ѡ��
        QRect circleRect = radioButtonRect.adjusted(2, 2, -2, -2); // ��������Բ�ε�λ��
        painter.drawEllipse(circleRect);

        // �����ǰ��ѡ��ѡ�У����������
        if (isChecked()) 
        {   

            painter.setPen(QPen(QColor("#BB9F5E"), 2));
            painter.drawEllipse(circleRect);
         

            painter.setBrush(QColor("#BB9F5E"));   // ����ѡ��ʱ�������ɫΪ��ɫ
            painter.drawEllipse(circleRect.adjusted(5,5, -5, -5));  // ����СԲȦ����ʾѡ��
        }

        // �����ı���ȷ���ı�λ�ö���
        QRect textRect = option.rect;

        // ���ı����ƣ�ʹ��������ĵ�ѡ���ұ߶���
        textRect.setLeft(radioButtonRect.right() + 5);  // ���ı��Ƶ���ѡ���Ҳ�

        // ʹ�ı���ֱ����
        textRect.moveTop(radioButtonRect.top() + (radioButtonRect.height() - textRect.height()) / 2);
        painter.restore();
        
        // ʹ��Ĭ�ϵ��ı���ɫ������ʽ��Ϳؼ�״̬������
        style()->drawItemText(&painter, textRect, Qt::AlignVCenter, option.palette, isEnabled(), option.text);
    }

};
