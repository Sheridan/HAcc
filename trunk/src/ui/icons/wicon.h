#ifndef WICON_H
#define WICON_H

#include "wimage.h"
#include <QIcon>
#include <QPixmap>
#include "hacc_types.h"
#include "ciditem.h"

namespace ui
{
namespace icons
{

class WIcon : public ui::images::WImage, public hacc::CIDItem
{
    Q_OBJECT
public:
    explicit WIcon(QWidget *parent = 0);
    explicit WIcon(int side, QWidget *parent = 0);
    ~WIcon();
    void setIcon(const QIcon &icon, int extent = 16);
    void setIcon(const hacc::TDBID &iconID);
    void setIcon(const QString &iconFile, int extent = 16);

private:
    void init();
    void refreshIdIcon();
    bool m_connected;

private slots:
    void updated(hacc::TDBID iconID);
};

}
}

#endif // WICON_H
