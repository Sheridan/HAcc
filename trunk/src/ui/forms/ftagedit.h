/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef FTAGEDIT_H
#define FTAGEDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FTagEdit; }
namespace ui
{
namespace form
{

//! Диалог. Редактирование тега
class FTagEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FTagEdit(QWidget *parent = 0);
    explicit FTagEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~FTagEdit();
    QString name();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FTagEdit *m_ui;
};

}
}
#endif // FTAGEDIT_H
