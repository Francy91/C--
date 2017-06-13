#ifndef FINESTRAIMMAGINE_H
#define FINESTRAIMMAGINE_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QFileInfoList>

namespace Ui {
class FinestraImmagine;
}

class FinestraImmagine : public QMainWindow
{
    Q_OBJECT

public:
    explicit FinestraImmagine(QWidget *parent = 0);
    ~FinestraImmagine();

private slots:
    void on_action_Apri_Cartella_triggered();

    void on_actionAdatta_Zoom_triggered();

    void on_actionPrecedente_triggered();

protected slots:
    void resizeEvent(QResizeEvent *event);
    void viewImage(int indexImage);

private:
    Ui::FinestraImmagine *ui;
    QGraphicsPixmapItem* mPixmapItem;
    QGraphicsScene mScene;
    QFileInfoList mFileInfoList;
    int mIndexImage;
};

#endif // FINESTRAIMMAGINE_H
