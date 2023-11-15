#include "ledmanager.h"

#include <QGraphicsScene>
#include <QApplication>
#include <QGraphicsView>
#include <QTimer>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    //! [0]

    ledmanager lm {100, 64, 10, 10};
    //! [1]
    QGraphicsScene scene;
    scene.setSceneRect(0,0, 1200, 700);
    //! [1] //! [2]
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    //! [2]

    //! [3]
    //!
    //!
    for (int i = 0; i < 64; ++i) {
        for(int j=0; j < lm.getLedAt(i).count(); j++) {
            ledlight* ll = lm.getLedAt(i)[j];
            scene.addItem(ll);
        }
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
    view.resize(400, 300);
    view.show();
    QTimer updategui;
    QObject::connect(&updategui, SIGNAL(timeout()), &scene, SLOT(update()));
    updategui.setInterval(10);
    updategui.start();
    return app.exec();
}
