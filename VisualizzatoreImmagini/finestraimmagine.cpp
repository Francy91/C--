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
    mZoomList << 1.0 << 1.5 << 2.2 << 3.3 << 4.7 << 6.8;
    mZoomList << 10 << 15 << 22 << 33 << 47 << 68;
    mZoomList << 100 << 150 << 220 << 330 << 470 << 680;
    mZoomList << 1000 << 1500 << 2200;
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
        mIndexImage = 0;
        path = ":/icon/icon/Divieto generico.png";
    }
    else if(indexImage >= mFileInfoList.count())
    {
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

void FinestraImmagine::updateZoom(bool increment)
{
    ui->actionAdatta_Zoom->setChecked(false);
    float zoom = ui->graphicsView->transform().m11() * 100;
    if(increment)
        foreach (float z, mZoomList)
        {
           if((z-z/10) > zoom)
           {
               zoom = z;
               break;
           }
        }
    else
    {
        for(int ii = mZoomList.count(); ii > 0; ii--)
        {
            float z = mZoomList.at(ii-1);
            if((z+z/10) < zoom)
            {
                zoom = z;
                break;
            }
        }
    }
    ui->graphicsView->setTransform(QTransform::fromScale(zoom/100, zoom/100));

}
void FinestraImmagine::on_action_Apri_Cartella_triggered()
{
    //apre finestra per selezionare i file ritorna null in caso si "Annulla"
    QString path = QFileDialog::getExistingDirectory();
    if(path.isEmpty())
    {
        return;
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
    //qDebug() << __FUNCTION__ << mFileInfoList.count();
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
    viewImage(mIndexImage-1);
}

void FinestraImmagine::on_actionSuccessiva_triggered()
{
    viewImage(mIndexImage+1);
}

void FinestraImmagine::on_actionNussuna_Immagine_triggered()
{
    viewImage(0);
}

// Zoom ++
void FinestraImmagine::on_actionZoom_triggered()
{
    updateZoom(true);
}

//Zoom --
void FinestraImmagine::on_actionZoom_2_triggered()
{
    updateZoom(false);

}
