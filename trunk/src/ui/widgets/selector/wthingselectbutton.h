/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WTHINGSELECTBUTTON_H
#define WTHINGSELECTBUTTON_H

#include "wselectorbutton.h"
#include <QHBoxLayout>
#include "wicon.h"
namespace ui
{
namespace selector
{

class WThingSelectButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    explicit WThingSelectButton(QWidget *parent = 0);
    ~WThingSelectButton();

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setThingData(const hacc::TDBID &iconID, const QString &name);
    void setManufacturergData(const hacc::TDBID &iconID, const QString &name);
    QHBoxLayout      *m_layout;
    QLabel           *m_thingName;
    ui::icons::WIcon *m_thingIcon;
    QLabel           *m_manufacturerName;
    ui::icons::WIcon *m_manufacturerIcon;

private slots:
    void thingCreated(const hacc::TDBID &thingID);
};

}
}
#endif // WTHINGSELECTBUTTON_H
