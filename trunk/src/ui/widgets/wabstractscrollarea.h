#ifndef WABSTRACTSCROLLAREA_H
#define WABSTRACTSCROLLAREA_H

#include <QAbstractScrollArea>
#include <QLayout>

namespace ui
{
//! Разные контролы
namespace widget
{

//! Виджет со скроллингом
/**
  Базовый класс для всех контролов, у которых есть скроллинг. Например гриды, теги.
*/
class WAbstractScrollArea : public QAbstractScrollArea
{
    Q_OBJECT
public:
    explicit WAbstractScrollArea(QWidget *parent = 0);
    virtual ~WAbstractScrollArea();

protected:
    virtual int contentHeight() = 0; //!< Полная высота содержимого под скроллом
    void resizeWievport();
    void setViewportLayout(QLayout *ly);
    void resizeEvent ( QResizeEvent * event );

private:
    QWidget *m_wArea;       //!< Виджет-подложка
    QLayout *m_lArea;       //!< Лайоут-подложка
    int      m_topPosition; //!< "Верх" для вычисления куда скроллить
    void buildSelfUi();

//events
    void scrollContentsBy ( int dx, int dy );
};

}
}
#endif // WABSTRACTSCROLLAREA_H
