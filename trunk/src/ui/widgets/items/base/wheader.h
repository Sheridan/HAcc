/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WHEADER_H
#define WHEADER_H

#include "wstyledwidget.h"
#include "citemlabels.h"

namespace ui
{
namespace item
{
//! Базовые классы для грида
namespace base
{

//! Заголовок грида
class WHeader :
        public ui::widget::WStyledWidget,
        public CItemLabels
{
    Q_OBJECT
public:
    explicit WHeader(QWidget *parent = 0);
    ~WHeader();
    void setLabels(const int &columns, const int &rows, const QStringList& strings); //!< Установка заголовков

private:
    QGridLayout *m_layout;

};

}
}
}
#endif // WHEADER_H
