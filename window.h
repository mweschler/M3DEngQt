#ifndef WINDOW_H
#define WINDOW_H

#include <QGLWidget>
#include "SceneManager.h"

class QOpenGLContext;
class QPainter;
class QOpenGLPaintDevice;

namespace M3D{


    class Window : public QGLWidget
    {
        Q_OBJECT
    public:
        Window(QWidget *parent = 0);
        ~Window();

        //void render();
        //void render(QPainter *painter);

        //void initialize();
        void setSceneManager(SceneManager *sceneManager);

        //void setAnimating(bool animating);

    public slots:
        //void renderLater();
        //void renderNow();

    protected:
        //bool event(QEvent *event);
        //void exposeEvent(QExposeEvent *event);
        //void resizeEvent(QResizeEvent *event);
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);


    private:
        //bool m_update_pending;
        //bool m_animating;

        SceneManager *sceneManager;
        //QOpenGLPaintDevice *m_device;
        //QOpenGLContext *m_context;
    };
}
#endif // WINDOW_H
