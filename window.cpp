#include "Window.h"


#include <GL/glew.h>
#include <QGLWidget>
#include <QDebug>


namespace M3D{
Window::Window(QWidget *parent):QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
    {
        sceneManager = NULL;
    }

    Window::~Window(){
    }

    /*
    void Window::render(QPainter *painter){
        Q_UNUSED(painter);
    }*/

    void Window::initializeGL(){
        GLenum status = glewInit();
        if(status != GLEW_OK)
            qDebug() << glewGetErrorString(status);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST); // enable depth-testing
        glDepthMask(GL_TRUE); // turn back on
        glDepthFunc(GL_LEQUAL);
        glDepthRange(0.0f, 1.0f);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void Window::paintGL(){
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        if(sceneManager != NULL)
            sceneManager->renderScene();
        this->swapBuffers();
    }

    void Window::resizeGL(int width, int height){
        qDebug() << "Setting viewport to "<<width<<" "<<height;
        glViewport(0, 0, width,height);
    }

    void Window::setSceneManager(SceneManager *sceneManager){
        this->sceneManager = sceneManager;
    }

    /*
    void Window::renderLater(){
        if (!m_update_pending)
        {
            m_update_pending = true;
            QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
        }
    }*/

    /*
    bool Window::event(QEvent *event){
        switch(event->type()){
        case QEvent::UpdateRequest:
            renderNow();
            return true;
        default:
            return QWindow::event(event);
        }

    }*/

    /*
    void Window::exposeEvent(QExposeEvent *event){
        Q_UNUSED(event);

        if(isExposed())
            renderNow();
    }*/

    /*
    void Window::resizeEvent(QResizeEvent *event){
        Q_UNUSED(event);

        if(isExposed())
            renderNow();

    }*/

    /*
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
    }*/

    /*
    void Window::setAnimating(bool animating){
        m_animating = animating;

        if(animating)
            renderLater();
    }*/


}
