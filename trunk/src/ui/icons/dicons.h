/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef DICONS_H
#define DICONS_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class DIcons; }

namespace ui
{
namespace icons
{

//! Диалог редактирования иконок
class DIcons : public QDialog
{
    Q_OBJECT

public:
    explicit DIcons(QWidget *parent = 0);
    ~DIcons();
    hacc::TDBID selected();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DIcons *m_ui;
    hacc::TDBID m_selectedId;

private slots:
    void selected(hacc::TDBID id);
    void add();
};

}
}
#endif // DICONS_H
