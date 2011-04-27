/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef WVALUABLESELECTBUTTON_H
#define WVALUABLESELECTBUTTON_H

#include "wselectorbutton.h"
#include <QHBoxLayout>
#include "wicon.h"
namespace ui
{
namespace selector
{

class WValuableSelectButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    explicit WValuableSelectButton(QWidget *parent = 0);
    ~WValuableSelectButton();

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setThingData(const hacc::TDBID &iconID, const QString &name);
    void setManufacturerData(const hacc::TDBID &iconID, const QString &name);
    void setValuableData(const QString &serialNumber);
    QHBoxLayout      *m_layout;
    QLabel           *m_thingName;
    ui::icons::WIcon *m_thingIcon;
    QLabel           *m_manufacturerName;
    ui::icons::WIcon *m_manufacturerIcon;
    QLabel           *m_serialNumber;

private slots:
    void valuableCreated(const hacc::TDBID &valuableID);
};

}
}
// ui::selector::WValuableSelectButton
#endif // WVALUABLESELECTBUTTON_H
