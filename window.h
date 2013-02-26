#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include "SceneManager.h"
class QOpenGLContext;
class QPainter;
class QOpenGLPaintDevice;

namespace M3D{


    class Window : public QWindow
    {
        Q_OBJECT
    public:
        explicit Window(QWindow *parent = 0);
        ~Window();

        virtual void render();
        virtual void render(QPainter *painter);

        virtual void initialize();
        void setSceneManager(SceneManager *sceneManager);

        void setAnimating(bool animating);

    public slots:
        void renderLater();
        void renderNow();

    protected:
        bool event(QEvent *event);
        void exposeEvent(QExposeEvent *event);
        void resizeEvent(QResizeEvent *event);

    private:
        bool m_update_pending;
        bool m_animating;

        SceneManager *sceneManager;
        QOpenGLPaintDevice *m_device;
        QOpenGLContext *m_context;
    };
}
#endif // WINDOW_H
