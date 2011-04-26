#ifndef WLABEL_H
#define WLABEL_H

#include "wstyledwidget.h"
#include "wcontrollabel.h"
#include "wicon.h"
#include <QHBoxLayout>

namespace ui
{
namespace item
{
namespace base
{

//! Ячейка грида
/** Грубо - Иконка+текст*/
class WItemLabel : public ui::widget::WStyledWidget
{
    Q_OBJECT
public:
    WItemLabel(QWidget *parent = 0);
    ~WItemLabel();
    void setText(const QString     &text); //!< Установка текста
    void setIcon(const QIcon       &icon); //!< Установка иконки
    void setIcon(const QString     &file); //!< Установка иконки из файла
    void setIcon(const hacc::TDBID &id  ); //!< Установка иконки из БД по идентификатору
    ui::widget::WControlLabel * label();    //!< Установка иконки возвращает метку
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    QHBoxLayout               *m_layout;
    ui::widget::WControlLabel *m_label;
    ui::icons::WIcon          *m_icon;
    QSize                      m_sizeHint;
    void createIcon();

};

}
}
}
#endif // WLABEL_H
