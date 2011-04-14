#ifndef FTHINGENUMERATEDTYPESEDIT_H
#define FTHINGENUMERATEDTYPESEDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FThingEnumeratedTypesEdit; }
namespace ui
{
namespace form
{

class FThingEnumeratedTypesEdit : public QDialog
{
    Q_OBJECT
public:
    explicit FThingEnumeratedTypesEdit(QWidget *parent = 0);
    explicit FThingEnumeratedTypesEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~FThingEnumeratedTypesEdit();
    QString name();
    int precision();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FThingEnumeratedTypesEdit *m_ui;
    void init();
};

}
}
#endif // FTHINGENUMERATEDTYPESEDIT_H
