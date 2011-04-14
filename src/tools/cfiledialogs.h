#ifndef CFILEDIALOGS_H
#define CFILEDIALOGS_H
#include <QFileDialog>

namespace tools
{
//! Базовые диалоги
namespace dialog
{

struct SFileDialogResult
{
    QStringList fileNames;
    bool dialogOk;
    SFileDialogResult()
    {
        fileNames = QStringList();
        dialogOk = false;
    }
};

class CFileDialogs
{
public:
    static SFileDialogResult getOpenFileName  (const QString &title, const QString &extentions);
    static SFileDialogResult getOpenFilesNames(const QString &title, const QString &extentions);
    static SFileDialogResult getNewFileName   (const QString &title, const QString &extentions, const QString &defaultExt);

    static SFileDialogResult getOpenImage(const QString &title);


private:
    static QFileDialog     * fileDialog       (const QString &title                      , const QString &extentions);
    static SFileDialogResult execFileDialog   (QFileDialog *dlg    , const QString &title, const QString &extentions);
};

}
}
#endif // CFILEDIALOGS_H
