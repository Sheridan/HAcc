#ifndef WENUMERATEDTHINGTYPEBUTTON_H
#define WENUMERATEDTHINGTYPEBUTTON_H

#include "wselectorbutton.h"
#include <QHBoxLayout>
#include "wicon.h"
#include <QLabel>

namespace ui
{
namespace selector
{

class WEnumeratedThingTypeButton : public base::WSelectorButton
{
    Q_OBJECT
public:
    explicit WEnumeratedThingTypeButton(QWidget *parent = 0);
    ~WEnumeratedThingTypeButton();

private:
    void idChanged();
    base::WSelectorPopup * constructPopup();
    void setData(const QString &enumeratedThingTypeName);
    QHBoxLayout      *m_layout;
    QLabel           *m_eTThingName;
    ui::icons::WIcon *m_eTThingIcon;

private slots:
    void eTTCreated(const hacc::TDBID &eTTID);
};

}
}
#endif // WENUMERATEDTHINGTYPEBUTTON_H
