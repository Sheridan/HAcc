#ifndef WICONBUTTONBASE_H
#define WICONBUTTONBASE_H

#include <QToolButton>
#include "ciditem.h"

namespace ui
{
namespace icons
{

class WIconButtonBase : public QToolButton, public hacc::CIDItem
{
    Q_OBJECT
public:
    explicit WIconButtonBase(const hacc::TDBID &iconId, QWidget *parent = 0);
    ~WIconButtonBase();
    void setID(const hacc::TDBID & id);

signals:

public slots:

};

}
}

#endif // WICONBUTTONBASE_H
