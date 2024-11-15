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



        // 获取单选框的矩形区域
        QRect radioButtonRect = style()->subElementRect(QStyle::SE_RadioButtonIndicator, &option, this);

        // 增大单选框的尺寸
        int enlargedSize = 24;  // 自定义单选框的大小（增大后的大小）
        radioButtonRect.setWidth(enlargedSize);
        radioButtonRect.setHeight(enlargedSize);

      
       
        painter.setBrush(Qt::NoBrush);  // 不填充背景
        painter.setPen(QPen(QColor("#8C8C8C"), 2));  // 使用灰色边框，线宽为2

        // 绘制增大的圆形的单选框
        QRect circleRect = radioButtonRect.adjusted(2, 2, -2, -2); // 调整绘制圆形的位置
        painter.drawEllipse(circleRect);

        // 如果当前单选框被选中，则填充中心
        if (isChecked()) 
        {   

            painter.setPen(QPen(QColor("#BB9F5E"), 2));
            painter.drawEllipse(circleRect);
         

            painter.setBrush(QColor("#BB9F5E"));   // 设置选中时的填充颜色为白色
            painter.drawEllipse(circleRect.adjusted(5,5, -5, -5));  // 绘制小圆圈，表示选中
        }

        // 绘制文本，确保文本位置对齐
        QRect textRect = option.rect;

        // 将文本左移，使其与增大的单选框右边对齐
        textRect.setLeft(radioButtonRect.right() + 5);  // 将文本移到单选框右侧

        // 使文本垂直居中
        textRect.moveTop(radioButtonRect.top() + (radioButtonRect.height() - textRect.height()) / 2);
        painter.restore();
        
        // 使用默认的文本颜色（由样式表和控件状态决定）
        style()->drawItemText(&painter, textRect, Qt::AlignVCenter, option.palette, isEnabled(), option.text);
    }

};
