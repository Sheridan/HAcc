/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef FTHINGEDIT_H
#define FTHINGEDIT_H

#include <QDialog>
#include <QPixmap>
#include "hacc_types.h"

namespace Ui { class FThingEdit; }
namespace ui
{
namespace form
{

//! Диалог. Редактирование вещи
class FThingEdit : public QDialog
{
    Q_OBJECT
public:
    explicit FThingEdit(QWidget *parent = 0);
    FThingEdit(const hacc::TDBID &id, QWidget *parent = 0);
    ~FThingEdit();
    QString name();
    QString description();
    hacc::TDBID iconID();
    hacc::TDBID enumeratedThingTypeID();
    hacc::TDBID manufacturerID();
    QByteArray pixmapData();
    bool hasImage();
    int expiration();
    int guarantee();
    int thingType();

protected:
    void changeEvent(QEvent *e);

private:
    void init();

private slots:
    void on_tbLoadImage_clicked();
    void on_tbClearImage_clicked();

private:
    Ui::FThingEdit *m_ui;
};

}
}
#endif // FTHINGEDIT_H
