#include <QFile>
#include <QMenu>
#include "fmainwindow.h"
#include "ui_fmainwindow.h"
#include "dicons.h"
#include "cfiledialogs.h"
#include "ui_defines.h"
#include "actions.h"
#include "icons.h"
#include "st.h"

namespace ui
{
namespace form
{

HACC_STD_TRANSLATE_UI(FMainWindow, QMainWindow)

FMainWindow::FMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FMainWindow)
{
    ui->setupUi(this);

    ui->menuView->addAction(ui->mainToolBar->toggleViewAction());
    ui->menuView->addAction(ui->actionsWindowsToolbar->toggleViewAction());
    ui->menuView->addSeparator();

    ui->mainToolBar->addAction(HACC_CONTRACTORS->addAction());
    ui->mainToolBar->addAction(HACC_CONTRACTORS->addSelfAction());
    ui->mainToolBar->addAction(HACC_THINGS->addAction());
    ui->mainToolBar->addAction(HACC_TAGS->addAction());
    ui->mainToolBar->addAction(HACC_MANUFACTURERS->addAction());
    ui->mainToolBar->addAction(HACC_ENUMERATED_THING_TYPES->addAction());

    ui->menuManage->addSeparator();
    ui->menuManage->addAction(HACC_CONTRACTORS->addAction());
    ui->menuManage->addAction(HACC_CONTRACTORS->addSelfAction());
    ui->menuManage->addAction(HACC_THINGS->addAction());
    ui->menuManage->addAction(HACC_MANUFACTURERS->addAction());
    ui->menuManage->addAction(HACC_ENUMERATED_THING_TYPES->addAction());
    ui->menuManage->addSeparator();
    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionLocalAction());
    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionBuyAction());
    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionSellAction());
    ui->menuManage->addSeparator();
    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyIncomingAction());
    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyOutgoingAction());
    ui->menuManage->addSeparator();
//    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionAcceptGiftAction());
//    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionGiveGiftAction());

    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionLocalAction());
    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionBuyAction());
    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionSellAction());
    ui->transactionsBar->addSeparator();
    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyIncomingAction());
    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyOutgoingAction());
    ui->transactionsBar->addSeparator();
//    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionAcceptGiftAction());
//    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionGiveGiftAction());

    m_transactionPoolBase = NULL;
    m_MdiArea = NULL;

    bool mdi = HACC_OPTIONS->sectionValue("view", "mdi", false).toBool();
    ui->actionMDI_mode->setChecked(mdi);
    changeViewMode(mdi);
}

FMainWindow::~FMainWindow()
{
    clearUi();
    delete ui;
}

void FMainWindow::clearUi()
{
    HACC_SAVE_DIALOG;
    while(!m_docks.empty())
    {
        ui::dock::DWContainerBase *d = m_docks.takeLast();
        removeDockWidget(d);
        delete d;
    }
    while(!m_mdiChilds.empty())
    {
        FMDIChild *w = m_mdiChilds.takeLast();
        m_MdiArea->removeSubWindow(w);
        delete w;
    }
    while(!m_wActions.empty())
    {
        QAction *a = m_wActions.takeLast();
        if(ui->menuView->actions().contains(a))
        {
            ui->menuView->removeAction(a);
            ui->actionsWindowsToolbar->removeAction(a);
            delete a;
        }
    }
    delete m_transactionPoolBase;
    delete m_MdiArea;
    m_transactionPoolBase = NULL;
    m_MdiArea = NULL;
}

void FMainWindow::appendAction(QAction *a)
{
    m_wActions.append(a);
    ui->menuView->addAction(a);
    ui->actionsWindowsToolbar->addAction(a);
}

template <typename TContainerBase> void FMainWindow::addMdiSubWindow(const QString &title, const QIcon &icon)
{
    TMDIChild<TContainerBase> * sw = new TMDIChild<TContainerBase>(title, icon, m_MdiArea);
    sw->init();
    sw->setIndex(m_mdiChilds.count());
    connect(sw, SIGNAL(closing(int)), this, SLOT(mdiClose(int)));
    m_mdiChilds.append(sw);
    m_MdiArea->addSubWindow(sw);
    sw->show();
}

template <typename TContainerBase> void FMainWindow::addDock(const QString &title, const QIcon &icon)
{
    ui::dock::TDWContainerBase<TContainerBase> *dw = new ui::dock::TDWContainerBase<TContainerBase>(title, icon, this);
    dw->init();
    m_docks.append(dw);
    QAction *a = dw->toggleViewAction();
    a->setIcon(icon);
    a->setToolTip(title);
    appendAction(a);
    addDockWidget(Qt::TopDockWidgetArea, dw);
}

void FMainWindow::changeViewMode(bool mdi)
{
    clearUi();
    if(mdi)
    {
        setObjectName("MainWindowMDI");
        m_MdiArea = new QMdiArea(this);
        setCentralWidget(m_MdiArea);
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iThing          , tools::icons::oNewWindow),
                                                    tr("Things")                  , tr("New window of things")                  , this, SLOT(newThingBaseMdiChild())              ));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iTag            , tools::icons::oNewWindow),
                                                    tr("Tags")                    , tr("New window of tags")                    , this, SLOT(newTagBaseMdiChild())                ));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iContractor     , tools::icons::oNewWindow),
                                                    tr("Contractors")             , tr("New window of contractors")             , this, SLOT(newContractorBaseMdiChild())         ));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iManufacturer   , tools::icons::oNewWindow),
                                                    tr("Manufacturers")           , tr("New window of manufacturers")           , this, SLOT(newManufacturerBaseMdiChild())       ));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iEnumerated     , tools::icons::oNewWindow),
                                                    tr("Things enumeration types"), tr("New window of things enumeration types"), this, SLOT(newEnumeratedThingTypeBaseMdiChild())));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iTransactionPool, tools::icons::oNewWindow),
                                                    tr("Transaction pools")       , tr("New window of transaction pools")       , this, SLOT(newTransactionPoolBaseMdiChild())    ));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iValuable       , tools::icons::oNewWindow),
                                                    tr("Valuables")               , tr("New window of valuables")               , this, SLOT(newValuablesBaseMdiChild())          ));
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iMovement       , tools::icons::oNewWindow),
                                                    tr("Movement")                , tr("New window of movement")                , this, SLOT(newMovementBaseMdiChild())           ));
    }
    else
    {
        setObjectName("MainWindowDocks");
        m_transactionPoolBase = new ui::item::expanded::WExpandedTransactionPoolBase(this);
        m_transactionPoolBase->buildUi();
        m_transactionPoolBase->container()->refresh();
        setCentralWidget(m_transactionPoolBase);
        addDock<ui::item::expanded::WExpandedThingBase          > (tr("Things"),                   HACC_ICONS->icon(tools::icons::iThing)       );
        addDock<ui::item::simple::WSimpleTagBase                > (tr("Tags"),                     HACC_ICONS->icon(tools::icons::iTag)         );
        addDock<ui::item::expanded::WExpandedContractorBase     > (tr("Contractors"),              HACC_ICONS->icon(tools::icons::iContractor)  );
        addDock<ui::item::expanded::WExpandedManufacturerBase   > (tr("Manufacturers"),            HACC_ICONS->icon(tools::icons::iManufacturer));
        addDock<ui::item::simple::WSimpleEnumeratedThingTypeBase> (tr("Things enumeration types"), HACC_ICONS->icon(tools::icons::iEnumerated)  );
        addDock<ui::item::expanded::WExpandedValuableBase       > (tr("Valuables"),                HACC_ICONS->icon(tools::icons::iValuable)    );
        addDock<ui::item::simple::WSimpleMovementBase           > (tr("Movement"),                 HACC_ICONS->icon(tools::icons::iMovement)    );
    }
    HACC_RESTORE_DIALOG;
}

void FMainWindow::newThingBaseMdiChild              () { addMdiSubWindow<ui::item::expanded::WExpandedThingBase          > (tr("Things"),                   HACC_ICONS->icon(tools::icons::iThing)          ); }
void FMainWindow::newTagBaseMdiChild                () { addMdiSubWindow<ui::item::simple::WSimpleTagBase                > (tr("Tags"),                     HACC_ICONS->icon(tools::icons::iTag)            ); }
void FMainWindow::newContractorBaseMdiChild         () { addMdiSubWindow<ui::item::expanded::WExpandedContractorBase     > (tr("Contractors"),              HACC_ICONS->icon(tools::icons::iContractor)     ); }
void FMainWindow::newManufacturerBaseMdiChild       () { addMdiSubWindow<ui::item::expanded::WExpandedManufacturerBase   > (tr("Manufacturers"),            HACC_ICONS->icon(tools::icons::iManufacturer)   ); }
void FMainWindow::newEnumeratedThingTypeBaseMdiChild() { addMdiSubWindow<ui::item::simple::WSimpleEnumeratedThingTypeBase> (tr("Things enumeration types"), HACC_ICONS->icon(tools::icons::iEnumerated)     ); }
void FMainWindow::newTransactionPoolBaseMdiChild    () { addMdiSubWindow<ui::item::expanded::WExpandedTransactionPoolBase> (tr("Transaction pools"),        HACC_ICONS->icon(tools::icons::iTransactionPool)); }
void FMainWindow::newValuablesBaseMdiChild          () { addMdiSubWindow<ui::item::expanded::WExpandedValuableBase       > (tr("Valuables"),                HACC_ICONS->icon(tools::icons::iValuable)       ); }
void FMainWindow::newMovementBaseMdiChild           () { addMdiSubWindow<ui::item::simple::WSimpleMovementBase           > (tr("Movement"),                 HACC_ICONS->icon(tools::icons::iMovement)       ); }

void FMainWindow::mdiClose(int index)
{
    if(0 <= index && index < m_mdiChilds.count())
    {
        FMDIChild *w = m_mdiChilds.takeAt(index);
        m_MdiArea->removeSubWindow(w);
        delete w;
    }
}

void FMainWindow::on_actionIcons_triggered()
{
    ui::icons::DIcons icons(this);
    icons.exec();
}

void FMainWindow::on_actionOpen_triggered()
{
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getOpenFileName(tr("Open database"),  tr("Database") + "(*.hacc)");
    if(dlgResult.dialogOk && QFile::exists(dlgResult.fileNames[0]))
    {
        HACC_DB->open(dlgResult.fileNames[0]);
    }
}

void FMainWindow::on_actionNew_triggered()
{
    tools::dialog::SFileDialogResult dlgResult =
            tools::dialog::CFileDialogs::getNewFileName(tr("New database"),  tr("Database") + "(*.hacc)", "hacc");
    if(dlgResult.dialogOk)
    {
        HACC_DB->open(dlgResult.fileNames[0], true);
    }
}

void FMainWindow::on_actionClose_triggered()
{
    HACC_DB->close();
}

void FMainWindow::dbClosing()
{
    setWindowTitle("hacc");
}

void FMainWindow::dbIsOpen()
{
    setWindowTitle(QString("hacc [%1]").arg(HACC_DB->dbFileName()));
}

void FMainWindow::on_actionMDI_mode_triggered(bool checked)
{
    HACC_OPTIONS->setSectionValue("view", "mdi", checked);
    changeViewMode(checked);
}

}
}

