#ifndef FMDICHILD_H
#define FMDICHILD_H

#include <QMdiSubWindow>
#include <QAction>
#include "wbase.h"
namespace ui
{
namespace form
{

class FMDIChild : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit FMDIChild(const QString &title, const QIcon &icon, QWidget *parent = 0);
    ~FMDIChild();
    void init();
    void setIndex(const int &index);

protected:
    virtual ui::item::base::WBase *constructContainerBase() = 0;

private:
    ui::item::base::WBase *m_containerBase;
    void closeEvent ( QCloseEvent * closeEvent );
    int m_index;
//    void changeEvent(QEvent *e);

signals:
    void closing(int);
};

}
}

#endif // FMDICHILD_H
