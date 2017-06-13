#include "finestraimmagine.h"
#include "ui_finestraimmagine.h"
#include <QDebug>
#include <QFileDialog>

FinestraImmagine::FinestraImmagine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinestraImmagine)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&mScene);
    QImage image(":/icon/icon/Divieto generico.png");
    mPixmapItem = mScene.addPixmap(QPixmap::fromImage(image));
}

FinestraImmagine::~FinestraImmagine()
{
    delete ui;
}

void FinestraImmagine::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView ->fitInView(mPixmapItem,Qt::KeepAspectRatio);
    QWidget::resizeEvent(event);
}

void FinestraImmagine::viewImage(int indexImage)
{
    QString path;
    qDebug() << mFileInfoList.count();
    if(indexImage <= 0 || mFileInfoList.count() == 0)
    {
        qDebug() << "if";
        mIndexImage = 0;
        path = ":/icon/icon/Divieto generico.png";
    }
    else if(indexImage >= mFileInfoList.count())
    {
        qDebug() << "else";
        mIndexImage = mFileInfoList.count();
        path = mFileInfoList.last().absoluteFilePath();
    }
    else
    {
        mIndexImage = indexImage;
        path = mFileInfoList.at(indexImage-1).absoluteFilePath();
    }
    QImage image(path);
    if (image.isNull()) return;
    mPixmapItem->setPixmap(QPixmap::fromImage(image));
    mPixmapItem->setToolTip(path);
    if (ui->actionAdatta_Zoom->isChecked())
    {
        ui->graphicsView->fitInView(mPixmapItem, Qt::KeepAspectRatio);
    }
}
void FinestraImmagine::on_action_Apri_Cartella_triggered()
{
    //apre finestra per selezionare i file ritorna null in caso si "Annulla"
    QString path = QFileDialog::getExistingDirectory();
    if(path.isEmpty())
    {
        return;
        qDebug() << "dentro";
    }
    QDir dir(path);
    //filtra i file che non devono essere caricati e visibili nella finestra
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
    QStringList filters;
    //definisce i tipi accettati
    filters << "*.jpg" << "*.png" << "*.bmp";
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Name);
    mFileInfoList = dir.entryInfoList();
    viewImage(1);
    qDebug() << __FUNCTION__ << mFileInfoList.count();
}

void FinestraImmagine::on_actionAdatta_Zoom_triggered()
{
    if(ui->actionAdatta_Zoom->isCheckable())
    {
        ui->graphicsView->fitInView(mPixmapItem,Qt::KeepAspectRatio);
    }
}

void FinestraImmagine::on_actionPrecedente_triggered()
{

}
