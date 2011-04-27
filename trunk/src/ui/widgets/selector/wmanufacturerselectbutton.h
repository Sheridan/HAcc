/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WMANUFACTURERSELECTBUTTON_H
#define WMANUFACTURERSELECTBUTTON_H

#include "wselectorbutton.h"
#include <QHBoxLayout>
#include "wicon.h"
namespace ui
{
//! Выбор из списка
namespace selector
{

class WManufacturerSelectButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    explicit WManufacturerSelectButton(QWidget *parent = 0);
    ~WManufacturerSelectButton();
private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setData(const hacc::TDBID &iconID, const QString &name);
    QHBoxLayout      *m_layout;
    QLabel           *m_lName;
    ui::icons::WIcon *m_wIcon;
private slots:
    void manufacturerCreated(const hacc::TDBID &manufacturerID);
};

}
}
#endif // WMANUFACTURERSELECTBUTTON_H
