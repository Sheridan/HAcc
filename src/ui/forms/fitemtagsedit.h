#ifndef FITEMTAGSEDIT_H
#define FITEMTAGSEDIT_H
// -------------------------------  h ----------------------------------------
#include <QDialog>
#include "wtagcontainer.h"
#include "hacc_types.h"
#include "ciditem.h"

namespace Ui { class FItemTagsEdit; }
namespace ui
{
namespace form
{

class FItemTagsEdit : public QDialog, public hacc::CIDItem
{
    Q_OBJECT
public:
    FItemTagsEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~FItemTagsEdit();
    int exec();

protected:
    void changeEvent(QEvent *e);
    virtual ui::tag::base::WTagContainer *constructContainer() = 0;

private:
    Ui::FItemTagsEdit *ui;
    ui::tag::base::WTagContainer *m_container;

};


}
}
#endif // FITEMTAGSEDIT_H
