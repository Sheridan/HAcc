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
    m_ui(new Ui::FMainWindow)
{
    m_ui->setupUi(this);

    m_ui->menuView->addAction(m_ui->mainToolBar->toggleViewAction());
    m_ui->menuView->addAction(m_ui->actionsWindowsToolbar->toggleViewAction());
    m_ui->menuView->addSeparator();

    m_ui->mainToolBar->addAction(HACC_CONTRACTORS->addAction());
    m_ui->mainToolBar->addAction(HACC_CONTRACTORS->addSelfAction());
    m_ui->mainToolBar->addAction(HACC_THINGS->addAction());
    m_ui->mainToolBar->addAction(HACC_TAGS->addAction());
    m_ui->mainToolBar->addAction(HACC_MANUFACTURERS->addAction());
    m_ui->mainToolBar->addAction(HACC_ENUMERATED_THING_TYPES->addAction());

    m_ui->menuManage->addSeparator();
    m_ui->menuManage->addAction(HACC_CONTRACTORS->addAction());
    m_ui->menuManage->addAction(HACC_CONTRACTORS->addSelfAction());
    m_ui->menuManage->addAction(HACC_THINGS->addAction());
    m_ui->menuManage->addAction(HACC_MANUFACTURERS->addAction());
    m_ui->menuManage->addAction(HACC_ENUMERATED_THING_TYPES->addAction());
    m_ui->menuManage->addSeparator();
    m_ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionLocalAction());
    m_ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionBuyAction());
    m_ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionSellAction());
    m_ui->menuManage->addSeparator();
    m_ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyIncomingAction());
    m_ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyOutgoingAction());
    m_ui->menuManage->addSeparator();
//    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionAcceptGiftAction());
//    ui->menuManage->addAction(HACC_TRANSACTIONS_POOLS->addTransactionGiveGiftAction());

    m_ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionLocalAction());
    m_ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionBuyAction());
    m_ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionSellAction());
    m_ui->transactionsBar->addSeparator();
    m_ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyIncomingAction());
    m_ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionMoneyOutgoingAction());
    m_ui->transactionsBar->addSeparator();
//    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionAcceptGiftAction());
//    ui->transactionsBar->addAction(HACC_TRANSACTIONS_POOLS->addTransactionGiveGiftAction());

    m_transactionPoolBase = NULL;
    m_mdiArea = NULL;

    bool mdi = HACC_OPTIONS->sectionValue("view", "mdi", false).toBool();
    m_ui->actionMDI_mode->setChecked(mdi);
    changeViewMode(mdi);
}

FMainWindow::~FMainWindow()
{
    clearUi();
    delete m_ui;
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
        m_mdiArea->removeSubWindow(w);
        delete w;
    }
    while(!m_wActions.empty())
    {
        QAction *a = m_wActions.takeLast();
        if(m_ui->menuView->actions().contains(a))
        {
            m_ui->menuView->removeAction(a);
            m_ui->actionsWindowsToolbar->removeAction(a);
            delete a;
        }
    }
    delete m_transactionPoolBase;
    delete m_mdiArea;
    m_transactionPoolBase = NULL;
    m_mdiArea = NULL;
}

void FMainWindow::appendAction(QAction *a)
{
    m_wActions.append(a);
    m_ui->menuView->addAction(a);
    m_ui->actionsWindowsToolbar->addAction(a);
}

template <typename TContainerBase> void FMainWindow::addMdiSubWindow(const QString &title, const QIcon &icon)
{
    TMDIChild<TContainerBase> * sw = new TMDIChild<TContainerBase>(title, icon, m_mdiArea);
    sw->init();
    sw->setIndex(m_mdiChilds.count());
    connect(sw, SIGNAL(closing(int)), this, SLOT(mdiClose(int)));
    m_mdiChilds.append(sw);
    m_mdiArea->addSubWindow(sw);
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
        m_mdiArea = new QMdiArea(this);
        setCentralWidget(m_mdiArea);
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
        appendAction(tools::actions::constructAction(HACC_ICONS->icon(tools::icons::iCurrency       , tools::icons::oNewWindow),
                                                    tr("Currency")                , tr("New window of currency")                , this, SLOT(newCurrencyBaseMdiChild())           ));
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
        addDock<ui::item::simple::WSimpleCurrencyBase           > (tr("Currency"),                 HACC_ICONS->icon(tools::icons::iCurrency)    );
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
void FMainWindow::newCurrencyBaseMdiChild           () { addMdiSubWindow<ui::item::simple::WSimpleCurrencyBase           > (tr("Currency"),                 HACC_ICONS->icon(tools::icons::iCurrency)       ); }

void FMainWindow::mdiClose(int index)
{
    if(0 <= index && index < m_mdiChilds.count())
    {
        FMDIChild *w = m_mdiChilds.takeAt(index);
        m_mdiArea->removeSubWindow(w);
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

