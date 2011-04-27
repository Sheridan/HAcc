/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WCONTROLLABEL_H
#define WCONTROLLABEL_H

#include "wstyledwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include "wiconbutton.h"
#include <QList>

namespace ui
{
namespace widget
{

//! Метка с всплывающими иконками-кнопками
/** Иконка + метка + всплывающие кнопки*/
class WControlLabel : public QLabel
{
    Q_OBJECT
public:
    explicit WControlLabel(QWidget *parent = 0);
    ~WControlLabel();
    void setButtonsVisible(bool visible);  //!< Сдклать дополнительные кнопки видимыми?
    void addAction(QAction *action);       //!< Добавление действия.

private:
    QList< ui::widget::WIconButton *> m_wicons; //!< Список всплывающих кнопок
    void enterEvent ( QEvent * event );
    void leaveEvent( QEvent * event );
    void resizeEvent ( QResizeEvent * event );
    void fixButtonsPosition();             //!< Исправление положения кнопок
};

}
}
#endif // WCONTROLLABEL_H
