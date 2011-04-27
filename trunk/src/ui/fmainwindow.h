/**
  \author Горлов Максим <sheridan@sheridan-home.ru
  */
#ifndef FMAINWINDOW_H
#define FMAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "wexpandedmanufacturerbase.h"
#include "wexpandedcontractorbase.h"
#include "wexpandedthingbase.h"
#include "wsimpleenumeratedthingtypebase.h"
#include "wsimpletagbase.h"
#include "wexpandedtransactionpoolbase.h"
#include "wexpandedvaluablebase.h"
#include "wsimplemovementbase.h"
#include "wsimplecurrencybase.h"
#include <QDockWidget>
#include "tmdichild.h"
#include "tdwcontainerbase.h"



namespace Ui { class FMainWindow; }
namespace ui
{
namespace form
{

//! Основное окно приложения
/** Может быть как окном-с-доклетами, так и MDI.
*/
class FMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    FMainWindow(QWidget *parent = 0);
    ~FMainWindow();
    void changeViewMode(bool mdi); //!< Устанавливает режим окна

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FMainWindow                                  *m_ui;
    QMdiArea                                         *m_mdiArea;
    ui::item::expanded::WExpandedTransactionPoolBase *m_transactionPoolBase;
    QList<FMDIChild                 *>                m_mdiChilds;
    QList<ui::dock::DWContainerBase *>                m_docks;
    QList<QAction                   *>                m_wActions;
    void clearUi();
    void appendAction(QAction *a);

    template <typename TContainerBase> void addMdiSubWindow(const QString &title, const QIcon &icon);
    template <typename TContainerBase> void addDock(const QString &title, const QIcon &icon);

private slots:
    void newEnumeratedThingTypeBaseMdiChild();
    void newTransactionPoolBaseMdiChild();
    void newManufacturerBaseMdiChild();
    void newContractorBaseMdiChild();
    void newValuablesBaseMdiChild();
    void newMovementBaseMdiChild();
    void newCurrencyBaseMdiChild();
    void newThingBaseMdiChild();
    void newTagBaseMdiChild();

    void mdiClose(int index);

    void on_actionClose_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionIcons_triggered();
    void dbClosing();
    void dbIsOpen();
    void on_actionMDI_mode_triggered(bool checked);
    void on_actionOptions_triggered();
};

}
}

#endif // FMAINWINDOW_H
