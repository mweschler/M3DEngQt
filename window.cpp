#include "Window.h"



#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QDebug>


namespace M3D{
    Window::Window(QWindow *parent):QWindow(parent),
        m_update_pending(false),
        m_animating(false),
        m_context(0),
        m_device(0)
    {
        setSurfaceType(QWindow::OpenGLSurface);
        sceneManager = NULL;
    }

    Window::~Window(){
        delete m_device;
    }

    void Window::render(QPainter *painter){
        Q_UNUSED(painter);
    }

    void Window::initialize(){
        if(!m_context){
            m_context = new QOpenGLContext(this);
            m_context->setFormat(requestedFormat());
            m_context->create();
            if(!m_context->isValid())
                qDebug() << "Context was not valid";
            else
                qDebug() << "Context OK!";
        }

        if(m_context->makeCurrent(this))
            qDebug() << "Contex made current";
        else
            qDebug() << "Could not make current";

    }

    void Window::render(){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(sceneManager != NULL)
            sceneManager->renderScene();
    }

    void Window::renderLater(){
        if (!m_update_pending)
        {
            m_update_pending = true;
            QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
        }
    }

    bool Window::event(QEvent *event){
        switch(event->type()){
        case QEvent::UpdateRequest:
            renderNow();
            return true;
        default:
            return QWindow::event(event);
        }

    }

    void Window::exposeEvent(QExposeEvent *event){
        Q_UNUSED(event);

        if(isExposed())
            renderNow();
    }

    void Window::resizeEvent(QResizeEvent *event){
        Q_UNUSED(event);

        if(isExposed())
            renderNow();

    }

    void Window::renderNow(){

        if(!isExposed())
            return;

        m_update_pending = false;

        bool needsInitialize = false;

        if(!m_context){
            m_context = new QOpenGLContext(this);
            m_context->setFormat(requestedFormat());
            m_context->create();

            needsInitialize = true;
        }

        m_context->makeCurrent(this);

        if(needsInitialize){
            //initializeOpenGLFunctions();
            initialize();
        }

        render();

        m_context->swapBuffers(this);

        if(m_animating)
            renderLater();
    }

    void Window::setAnimating(bool animating){
        m_animating = animating;

        if(animating)
            renderLater();
    }

    void Window::setSceneManager(SceneManager *sceneManager){
        this->sceneManager = sceneManager;
    }
}
