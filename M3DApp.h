#ifndef _M3DAPP_H_
#define _M3DAPP_H_

#include <QObject>
#include <QTime>
#include <QTimer>

#include "ResourceManager.h"
#include "SceneManager.h"
#include "RenderSystem.h"
#include "window.h"

class QApplication;

namespace M3D{
    class M3DApp:public QObject{
        Q_OBJECT
	public:
        M3DApp(QObject *parent =0);
		~M3DApp();
		bool initialize(int width, int height);
        int run(QApplication *qtApp);
    private slots:
        void update();
    signals:
        void renderNow();
	private:
		void render(double time);
		void shutdown();
		bool initialized;
		bool running;
		ResourceManager resourceManager;
		SceneManager sceneManager;
		RenderSystem renderSystem;
		int screenWidth;
		int screenHeight;
        Window window;
        QTime time;
        QTimer updateLoopTimer;
	};
}


#endif
