#ifndef WABSTRACTSCROLLAREA_H
#define WABSTRACTSCROLLAREA_H

#include <QAbstractScrollArea>
#include <QLayout>

namespace ui
{
namespace widget
{

class WAbstractScrollArea : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit WAbstractScrollArea(QWidget *parent = 0);
    virtual ~WAbstractScrollArea();

protected:
    virtual int contentHeight() = 0;
    void resizeWievport();
    void setViewportLayout(QLayout *ly);
    void resizeEvent ( QResizeEvent * event );

private:
    QWidget *m_wArea;
    QLayout *m_lArea;
    int      m_topPosition;
    void buildSelfUi();

//events
    void scrollContentsBy ( int dx, int dy );
};

}
}
#endif // WABSTRACTSCROLLAREA_H
