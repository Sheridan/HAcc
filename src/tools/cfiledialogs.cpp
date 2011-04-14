#include "cfiledialogs.h"
#include <QFileInfo>
#include <QCryptographicHash>
#include "st.h"
namespace tools
{
namespace dialog
{

#define HACC_FD_HASH QString(QCryptographicHash::hash(QString("%1%2").arg(title).arg(extentions).toUtf8(),QCryptographicHash::Md5).toHex());

QFileDialog *CFileDialogs::fileDialog(const QString &title, const QString &extentions)
{
    QString hash = HACC_FD_HASH;
    QString prevPath = HACC_OPTIONS->sectionValue("filedialogs", hash, "").toString();
    QFileDialog *dlg = new QFileDialog(HACC_WINDOW);
    dlg->setWindowTitle(title);
    dlg->setNameFilter(extentions);
    dlg->setDirectory(prevPath.isEmpty() ? QDir::homePath() : prevPath);
    return dlg;
}

SFileDialogResult CFileDialogs::execFileDialog(QFileDialog *dlg, const QString &title, const QString &extentions)
{
    SFileDialogResult result;
    if(dlg->exec())
    {
        result.fileNames = dlg->selectedFiles();
        result.dialogOk = true;
        QString hash = HACC_FD_HASH;
        HACC_OPTIONS->setSectionValue("filedialogs", hash, result.fileNames[0]);
    }
    delete dlg;
    return result;
}

SFileDialogResult CFileDialogs::getOpenFileName(const QString &title, const QString &extentions)
{
    QFileDialog *dlg = fileDialog(title, extentions);
    dlg->setFileMode(QFileDialog::ExistingFile);
    return execFileDialog(dlg, title, extentions);
}

SFileDialogResult CFileDialogs::getOpenFilesNames(const QString &title, const QString &extentions)
{
    QFileDialog *dlg = fileDialog(title, extentions);
    dlg->setFileMode(QFileDialog::ExistingFiles);
    return execFileDialog(dlg, title, extentions);
}

SFileDialogResult CFileDialogs::getNewFileName(const QString &title, const QString &extentions, const QString &defaultExt)
{
    QFileDialog *dlg = fileDialog(title, extentions);
    dlg->setDefaultSuffix(defaultExt);
    return execFileDialog(dlg, title, extentions);
}

SFileDialogResult CFileDialogs::getOpenImage(const QString &title)
{
    return getOpenFilesNames(title, QObject::tr("Images") + "(*.png *.xpm *.jpg *.jpeg *.bmp)");
}

}
}
