#ifndef FACCOUNTEDIT_H
#define FACCOUNTEDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FAccountEdit; }
namespace ui
{
namespace form
{

//! Диалог. Редактирование счета
class FAccountEdit : public QDialog
{
    Q_OBJECT
public:
    FAccountEdit(QWidget *parent = 0);
    FAccountEdit(const hacc::TDBID & id, QWidget *parent = 0);
    ~FAccountEdit();
    QString name();
    hacc::TDBID iconId();
    hacc::TDBID currencyID();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FAccountEdit *m_ui;
    void init();
};

}
}
#endif // FACCOUNTEDIT_H
