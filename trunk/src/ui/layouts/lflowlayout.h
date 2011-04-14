#ifndef LFLOWLAYOUT_H
#define LFLOWLAYOUT_H

#include <QLayout>
#include <QStyle>
namespace ui
{
//!< Раскладки
namespace layout
{

//!< "Плавающая" раскладка
class LFlowLayout : public QLayout
{
public:
    LFlowLayout(QWidget *parent, int margin = 0, int hSpacing = 0, int vSpacing = 0);
    LFlowLayout(int margin = 0, int hSpacing = 0, int vSpacing = 0);
    ~LFlowLayout();

    void addItem(QLayoutItem *item);
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

    int totalHeight();

private:
    int doLayout(const QRect &rect, bool testOnly) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;
    mutable int m_height;
    mutable int m_width;
};

}
}
#endif // LFLOWLAYOUT_H
