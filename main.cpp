#include "ledmanager.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QGraphicsView>
#include <QTimer>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    //! [0]

    ledmanager lm {100};
    //! [1]
    QGraphicsScene scene;
    scene.setSceneRect(-1,-1, 900, 700);
    //! [1] //! [2]
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    //! [2]

    //! [3]
    for (int i = 0; i < lm.getLights1().count(); ++i)
    {
        scene.addItem(lm.getLights1()[i]);
        scene.addItem(lm.getLights2()[i]);
        scene.addItem(lm.getLights3()[i]);
        scene.addItem(lm.getLights4()[i]);
    }
    //! [3]

    //! [4]

    QTimer::singleShot(0, [&]()
    {
        lm.asyncInit();
    });

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    //! [4] //! [5]
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);
    //! [5] //! [6]
    view.resize(900, 700);
    view.show();
    QTimer updategui;
    QObject::connect(&updategui, SIGNAL(timeout()), &scene, SLOT(update()));
    updategui.setInterval(10);
    updategui.start();
    return app.exec();
}
