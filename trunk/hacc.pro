# -------------------------------------------------
# Project created by QtCreator 2010-11-20T19:27:51
# -------------------------------------------------
QT += sql
TARGET = hacc
TEMPLATE = app

DESTDIR = ../build/bin
OBJECTS_DIR = ../build/obj
MOC_DIR = ../build/moc
UI_DIR = ../build/ui
RCC_DIR = ../build/rcc

SOURCES += src/main.cpp \
    src/ui/fmainwindow.cpp \
    src/tools/db/cdatabase.cpp \
    src/csingletone.cpp \
    src/tools/coptions.cpp \
    src/capplication.cpp \
    src/model/caccounts.cpp \
    src/ui/forms/faccountedit.cpp \
    src/model/ciditem.cpp \
    src/tools/cfiledialogs.cpp \
    src/model/ccontractors.cpp \
    src/ui/forms/fcontractoredit.cpp \
    src/tools/icons.cpp \
    src/model/base/cbases.cpp \
    src/ui/widgets/items/base/witem.cpp \
    src/ui/widgets/items/base/wcontainer.cpp \
    src/model/base/cbase.cpp \
    src/model/ccontractor.cpp \
    src/tools/actions.cpp \
    src/ui/widgets/items/base/wbase.cpp \
    src/model/caccount.cpp \
    src/ui/widgets/wresizer.cpp \
    src/ui/icons/wiconscontainer.cpp \
    src/ui/layouts/lflowlayout.cpp \
    src/ui/widgets/wabstractscrollarea.cpp \
    src/ui/icons/wiconitem.cpp \
    src/ui/icons/dicons.cpp \
    src/ui/icons/wiconselect.cpp \
    src/ui/icons/wiconbuttonbase.cpp \
    src/model/cthing.cpp \
    src/model/cthings.cpp \
    src/ui/forms/fthingedit.cpp \
    src/tools/images.cpp \
    src/model/ctransactionpool.cpp \
    src/model/ctransactionspools.cpp \
    src/model/ctransaction.cpp \
    src/model/ctransactions.cpp \
    src/ui/widgets/selector/wcontractoraccountselectbutton.cpp \
    src/ui/icons/wicon.cpp \
    src/ui/widgets/wstyledwidget.cpp \
    src/ui/widgets/selector/base/wselectorbutton.cpp \
    src/ui/widgets/selector/base/wselectorpopup.cpp \
    src/ui/widgets/selector/wcontractoraccountselectpopup.cpp \
    src/ui/widgets/selector/wthingselectbutton.cpp \
    src/ui/widgets/selector/wthingselectpopup.cpp \
    src/model/cenumeratedthingtype.cpp \
    src/model/cenumeratedthingtypes.cpp \
    src/ui/widgets/selector/wenumeratedthingtypebutton.cpp \
    src/ui/widgets/selector/wenumeratedthingtypepopup.cpp \
    src/ui/widgets/items/base/wheader.cpp \
    src/model/cmanufacturer.cpp \
    src/model/cmanufacturers.cpp \
    src/ui/forms/fmanufactureredit.cpp \
    src/ui/widgets/items/base/witemlabel.cpp \
    src/ui/widgets/selector/wmanufacturerselectbutton.cpp \
    src/ui/widgets/selector/wmanufacturerselectpopup.cpp \
    src/ui/forms/fthingenumeratedtypesedit.cpp \
    src/tools/resources.cpp \
    src/ui/widgets/wcontrollabel.cpp \
    src/model/ctag.cpp \
    src/model/ctags.cpp \
    src/ui/forms/ftagedit.cpp \
    src/model/ctagged.cpp \
    src/ui/widgets/wlabelbutton.cpp \
    src/ui/images/wimage.cpp \
    src/ui/widgets/wiconbutton.cpp \
    src/ui/tags/base/wtaglabel.cpp \
    src/ui/tags/base/wtagcontainer.cpp \
    src/ui/forms/fitemtagsedit.cpp \
    src/ui/tags/ttagcontainer.cpp \
    src/model/composite/ccontractoraccount.cpp \
    src/model/composite/ccontractoraccountsource.cpp \
    src/model/composite/ccontractoraccountdestination.cpp \
    src/ui/forms/titemtagsedit.cpp \
    src/ui/forms/fmdichild.cpp \
    src/ui/forms/tmdichild.cpp \
    src/ui/forms/doptions.cpp \
    src/ui/docks/dwcontainerbase.cpp \
    src/ui/docks/tdwcontainerbase.cpp \
    src/ui/widgets/items/wsimplecontractoraccountbase.cpp \
    src/ui/widgets/items/wsimplecontractoraccountcontainer.cpp \
    src/ui/widgets/items/wsimplecontractoraccountitem.cpp \
    src/ui/widgets/items/wsimpleenumeratedthingtypebase.cpp \
    src/ui/widgets/items/wsimpleenumeratedthingtypecontainer.cpp \
    src/ui/widgets/items/wsimpleenumeratedthingtypeitem.cpp \
    src/ui/widgets/items/wsimplemanufacturerbase.cpp \
    src/ui/widgets/items/wsimplemanufacturercontainer.cpp \
    src/ui/widgets/items/wsimplemanufactureritem.cpp \
    src/ui/widgets/items/wsimpletagbase.cpp \
    src/ui/widgets/items/wsimpletagcontainer.cpp \
    src/ui/widgets/items/wsimpletagitem.cpp \
    src/ui/widgets/items/wsimplethingbase.cpp \
    src/ui/widgets/items/wsimplethingcontainer.cpp \
    src/ui/widgets/items/wsimplethingitem.cpp \
    src/ui/widgets/items/wexpandedaccountbase.cpp \
    src/ui/widgets/items/wexpandedaccountcontainer.cpp \
    src/ui/widgets/items/wexpandedaccountitem.cpp \
    src/ui/widgets/items/wexpandedcontractorbase.cpp \
    src/ui/widgets/items/wexpandedcontractorcontainer.cpp \
    src/ui/widgets/items/wexpandedcontractoritem.cpp \
    src/ui/widgets/items/wexpandedmanufacturerbase.cpp \
    src/ui/widgets/items/wexpandedmanufacturercontainer.cpp \
    src/ui/widgets/items/wexpandedmanufactureritem.cpp \
    src/ui/widgets/items/wexpandedthingbase.cpp \
    src/ui/widgets/items/wexpandedthingcontainer.cpp \
    src/ui/widgets/items/wexpandedthingitem.cpp \
    src/ui/widgets/items/wexpandedtransactionpoolbase.cpp \
    src/ui/widgets/items/wexpandedtransactionpoolcontainer.cpp \
    src/ui/widgets/items/wexpandedtransactionpoolitem.cpp \
    src/ui/widgets/items/base/citemlabels.cpp \
    src/tools/font.cpp \
    src/tools/hacc_date.cpp \
    src/model/cvaluable.cpp \
    src/model/cvaluables.cpp \
    src/ui/widgets/items/wexpandedvaluablebase.cpp \
    src/ui/widgets/items/wexpandedvaluablecontainer.cpp \
    src/ui/widgets/items/wexpandedvaluableitem.cpp \
    src/ui/forms/ftransactionpoolthingedit.cpp \
    src/tools/cdbiconscache.cpp \
    src/tools/ciconscache.cpp \
    src/ui/forms/ftransactionmoneyedit.cpp \
    src/ui/widgets/items/wexpandedtransactionpoolthingitem.cpp \
    src/ui/widgets/items/wexpandedtransactionpoolmoneyitem.cpp \
    src/ui/widgets/selector/wvaluableselectbutton.cpp \
    src/ui/widgets/selector/wvaluableselectpopup.cpp \
    src/ui/widgets/items/wsimplevaluablebase.cpp \
    src/ui/widgets/items/wsimplevaluablecontainer.cpp \
    src/ui/widgets/items/wsimplevaluableitem.cpp \
    src/ui/forms/ftransactiongiftedit.cpp \
    src/ui/widgets/items/wsimplecontractorbase.cpp \
    src/ui/widgets/items/wsimplecontractorcontainer.cpp \
    src/ui/widgets/items/wsimplecontractoritem.cpp \
    src/ui/widgets/selector/wcontractorselectbutton.cpp \
    src/ui/widgets/selector/wcontractorselectpopup.cpp \
    src/model/cmovement.cpp \
    src/model/cmovements.cpp \
    src/model/composite/ccontractorsource.cpp \
    src/model/composite/ccontractordestination.cpp \
    src/ui/widgets/items/wsimplemovementbase.cpp \
    src/ui/widgets/items/wsimplemovementcontainer.cpp \
    src/ui/widgets/items/wsimplemovementitem.cpp \
    src/ui/forms/ftransactionbuythingedit.cpp \
    src/ui/forms/ftransactionsellthingedit.cpp \
    src/ui/widgets/witemdescription.cpp \
    src/tools/convert.cpp \
    src/ui/widgets/items/wexpandedtransactionthingbuyitem.cpp \
    src/ui/widgets/items/wexpandedtransactionthingbuycontainer.cpp \
    src/ui/widgets/items/wexpandedtransactionthingbuybase.cpp \
    src/ui/widgets/items/wexpandedtransactionthingsellitem.cpp \
    src/ui/widgets/items/wexpandedtransactionthingsellcontainer.cpp \
    src/ui/widgets/items/wexpandedtransactionthingsellbase.cpp \
    src/ui/widgets/items/wexpandedtransactionthingitem.cpp \
    src/model/ccurrency.cpp \
    src/model/ccurrencyes.cpp \
    src/ui/widgets/items/wsimplecurrencybase.cpp \
    src/ui/widgets/items/wsimplecurrencycontainer.cpp \
    src/ui/widgets/items/wsimplecurrencyitem.cpp \
    src/ui/widgets/selector/wcurrencyelectbutton.cpp \
    src/ui/widgets/selector/wcurrencyselectpopup.cpp \
    src/ui/forms/fcurrencyedit.cpp \
    src/ui/forms/dprogress.cpp

HEADERS += src/ui/fmainwindow.h \
    src/tools/db/cdatabase.h \
    src/st.h \
    src/csingletone.h \
    src/tools/coptions.h \
    src/capplication.h \
    src/hacc_types.h \
    src/model/caccounts.h \
    src/ui/forms/faccountedit.h \
    src/model/ciditem.h \
    src/tools/cfiledialogs.h \
    src/ui/ui_defines.h \
    src/model/ccontractors.h \
    src/ui/forms/fcontractoredit.h \
    src/tools/icons.h \
    src/model/base/cbases.h \
    src/ui/widgets/items/base/witem.h \
    src/ui/widgets/items/base/wcontainer.h \
    src/hacc_debug.h \
    src/model/base/cbase.h \
    src/model/ccontractor.h \
    src/tools/actions.h \
    src/ui/widgets/items/base/wbase.h \
    src/model/caccount.h \
    src/ui/widgets/wresizer.h \
    src/ui/icons/wiconscontainer.h \
    src/ui/layouts/lflowlayout.h \
    src/ui/widgets/wabstractscrollarea.h \
    src/ui/icons/wiconitem.h \
    src/ui/icons/dicons.h \
    src/ui/icons/wiconselect.h \
    src/ui/icons/wiconbuttonbase.h \
    src/model/cthing.h \
    src/model/cthings.h \
    src/ui/forms/fthingedit.h \
    src/tools/images.h \
    src/model/ctransactionpool.h \
    src/model/ctransactionspools.h \
    src/model/ctransaction.h \
    src/model/ctransactions.h \
    src/ui/widgets/selector/wcontractoraccountselectbutton.h \
    src/ui/icons/wicon.h \
    src/ui/widgets/wstyledwidget.h \
    src/ui/widgets/selector/base/wselectorbutton.h \
    src/ui/widgets/selector/base/wselectorpopup.h \
    src/ui/widgets/selector/wcontractoraccountselectpopup.h \
    src/ui/widgets/selector/wthingselectbutton.h \
    src/ui/widgets/selector/wthingselectpopup.h \
    src/model/cenumeratedthingtype.h \
    src/model/cenumeratedthingtypes.h \
    src/ui/widgets/selector/wenumeratedthingtypebutton.h \
    src/ui/widgets/selector/wenumeratedthingtypepopup.h \
    src/ui/widgets/items/base/wheader.h \
    src/model/cmanufacturer.h \
    src/model/cmanufacturers.h \
    src/ui/forms/fmanufactureredit.h \
    src/ui/widgets/items/base/witemlabel.h \
    src/ui/widgets/selector/wmanufacturerselectbutton.h \
    src/ui/widgets/selector/wmanufacturerselectpopup.h \
    src/ui/forms/fthingenumeratedtypesedit.h \
    src/tools/resources.h \
    src/ui/widgets/wcontrollabel.h \
    src/model/ctag.h \
    src/model/ctags.h \
    src/ui/forms/ftagedit.h \
    src/model/ctagged.h \
    src/ui/widgets/wlabelbutton.h \
    src/ui/images/wimage.h \
    src/ui/widgets/wiconbutton.h \
    src/ui/tags/base/wtaglabel.h \
    src/ui/tags/base/wtagcontainer.h \
    src/ui/forms/fitemtagsedit.h \
    src/ui/tags/ttagcontainer.h \
    src/model/composite/ccontractoraccount.h \
    src/model/composite/ccontractoraccountsource.h \
    src/model/composite/ccontractoraccountdestination.h \
    src/ui/forms/titemtagsedit.h \
    src/ui/forms/fmdichild.h \
    src/ui/forms/tmdichild.h \
    src/ui/forms/doptions.h \
    src/ui/docks/dwcontainerbase.h \
    src/ui/docks/tdwcontainerbase.h \
    src/ui/widgets/items/wsimplecontractoraccountbase.h \
    src/ui/widgets/items/wsimplecontractoraccountcontainer.h \
    src/ui/widgets/items/wsimplecontractoraccountitem.h \
    src/ui/widgets/items/wsimpleenumeratedthingtypebase.h \
    src/ui/widgets/items/wsimpleenumeratedthingtypecontainer.h \
    src/ui/widgets/items/wsimpleenumeratedthingtypeitem.h \
    src/ui/widgets/items/wsimplemanufacturerbase.h \
    src/ui/widgets/items/wsimplemanufacturercontainer.h \
    src/ui/widgets/items/wsimplemanufactureritem.h \
    src/ui/widgets/items/wsimpletagbase.h \
    src/ui/widgets/items/wsimpletagcontainer.h \
    src/ui/widgets/items/wsimpletagitem.h \
    src/ui/widgets/items/wsimplethingbase.h \
    src/ui/widgets/items/wsimplethingcontainer.h \
    src/ui/widgets/items/wsimplethingitem.h \
    src/ui/widgets/items/wexpandedaccountbase.h \
    src/ui/widgets/items/wexpandedaccountcontainer.h \
    src/ui/widgets/items/wexpandedaccountitem.h \
    src/ui/widgets/items/wexpandedcontractorbase.h \
    src/ui/widgets/items/wexpandedcontractorcontainer.h \
    src/ui/widgets/items/wexpandedcontractoritem.h \
    src/ui/widgets/items/wexpandedmanufacturerbase.h \
    src/ui/widgets/items/wexpandedmanufacturercontainer.h \
    src/ui/widgets/items/wexpandedmanufactureritem.h \
    src/ui/widgets/items/wexpandedthingbase.h \
    src/ui/widgets/items/wexpandedthingcontainer.h \
    src/ui/widgets/items/wexpandedthingitem.h \
    src/ui/widgets/items/wexpandedtransactionpoolbase.h \
    src/ui/widgets/items/wexpandedtransactionpoolcontainer.h \
    src/ui/widgets/items/wexpandedtransactionpoolitem.h \
    src/ui/widgets/items/base/citemlabels.h \
    src/tools/font.h \
    src/tools/hacc_date.h \
    src/model/cvaluable.h \
    src/model/cvaluables.h \
    src/ui/widgets/items/wexpandedvaluablebase.h \
    src/ui/widgets/items/wexpandedvaluablecontainer.h \
    src/ui/widgets/items/wexpandedvaluableitem.h \
    src/model/base/special_tags_types.h \
    src/ui/forms/ftransactionpoolthingedit.h \
    src/tools/cdbiconscache.h \
    src/tools/ciconscache.h \
    src/ui/forms/ftransactionmoneyedit.h \
    src/ui/widgets/items/wexpandedtransactionpoolthingitem.h \
    src/ui/widgets/items/wexpandedtransactionpoolmoneyitem.h \
    src/ui/widgets/selector/wvaluableselectbutton.h \
    src/ui/widgets/selector/wvaluableselectpopup.h \
    src/ui/widgets/items/wsimplevaluablebase.h \
    src/ui/widgets/items/wsimplevaluablecontainer.h \
    src/ui/widgets/items/wsimplevaluableitem.h \
    src/ui/forms/ftransactiongiftedit.h \
    src/ui/widgets/items/wsimplecontractorbase.h \
    src/ui/widgets/items/wsimplecontractorcontainer.h \
    src/ui/widgets/items/wsimplecontractoritem.h \
    src/ui/widgets/selector/wcontractorselectbutton.h \
    src/ui/widgets/selector/wcontractorselectpopup.h \
    src/model/cmovement.h \
    src/model/cmovements.h \
    src/model/composite/ccontractorsource.h \
    src/model/composite/ccontractordestination.h \
    src/ui/widgets/items/wsimplemovementbase.h \
    src/ui/widgets/items/wsimplemovementcontainer.h \
    src/ui/widgets/items/wsimplemovementitem.h \
    src/ui/forms/ftransactionbuythingedit.h \
    src/ui/forms/ftransactionsellthingedit.h \
    src/ui/widgets/witemdescription.h \
    src/tools/convert.h \
    src/ui/widgets/items/wexpandedtransactionthingbuyitem.h \
    src/ui/widgets/items/wexpandedtransactionthingbuycontainer.h \
    src/ui/widgets/items/wexpandedtransactionthingbuybase.h \
    src/ui/widgets/items/wexpandedtransactionthingsellitem.h \
    src/ui/widgets/items/wexpandedtransactionthingsellcontainer.h \
    src/ui/widgets/items/wexpandedtransactionthingsellbase.h \
    src/ui/widgets/items/wexpandedtransactionthingitem.h \
    src/tools/db/hacc_db_defines.h \
    src/model/ccurrency.h \
    src/model/ccurrencyes.h \
    src/ui/widgets/items/wsimplecurrencybase.h \
    src/ui/widgets/items/wsimplecurrencycontainer.h \
    src/ui/widgets/items/wsimplecurrencyitem.h \
    src/ui/widgets/selector/wcurrencyelectbutton.h \
    src/ui/widgets/selector/wcurrencyselectpopup.h \
    src/hacc_options.h \
    src/ui/forms/fcurrencyedit.h \
    src/ui/forms/dprogress.h

FORMS += src/ui/fmainwindow.ui \
    src/ui/forms/faccountedit.ui \
    src/ui/forms/fcontractoredit.ui \
    src/ui/icons/dicons.ui \
    src/ui/forms/fthingedit.ui \
    src/ui/forms/fmanufactureredit.ui \
    src/ui/forms/fthingenumeratedtypesedit.ui \
    src/ui/forms/ftagedit.ui \
    src/ui/forms/fitemtagsedit.ui \
    src/ui/forms/doptions.ui \
    src/ui/docks/dwcontainerbase.ui \
    src/ui/forms/ftransactionpoolthingedit.ui \
    src/ui/forms/ftransactionmoneyedit.ui \
    src/ui/forms/ftransactiongiftedit.ui \
    src/ui/forms/ftransactionbuythingedit.ui \
    src/ui/forms/ftransactionsellthingedit.ui \
    src/ui/forms/fcurrencyedit.ui \
    src/ui/forms/dprogress.ui

INCLUDEPATH += src \
    src/ui \
    src/ui/docks \
    src/ui/forms \
    src/ui/icons \
    src/ui/layouts \
    src/ui/images \
    src/ui/tags \
    src/ui/tags/base \
    src/ui/widgets \
    src/ui/widgets/items \
    src/ui/widgets/items/base \
    src/ui/widgets/selector \
    src/ui/widgets/selector/base \
    src/tools \
    src/tools/db \
    src/model \
    src/model/base \
    src/model/composite

RESOURCES += res/hacc.qrc

OTHER_FILES += \
    res/styles/application.qss \
    res/styles/item.qss \
    res/styles/taglabel.qss \
    res/lang/ru.ts \
    doc/Doxyfile
