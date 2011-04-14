#ifndef FMANUFACTUREREDIT_H
#define FMANUFACTUREREDIT_H

#include <QDialog>
#include "hacc_types.h"

namespace Ui { class FManufacturerEdit; }

namespace ui
{
namespace form
{

class FManufacturerEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FManufacturerEdit(QWidget *parent = 0);
    explicit FManufacturerEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~FManufacturerEdit();
    QString name();
    QString description();
    hacc::TDBID iconId();
    QByteArray pixmapData();
    bool hasImage();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_tbLoadLogo_clicked();
    void on_tbClearLogo_clicked();

private:
    Ui::FManufacturerEdit *ui;
    void init();
};

}
}
#endif // FMANUFACTUREREDIT_H
