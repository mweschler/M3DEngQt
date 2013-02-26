
//#include <GL\glfw.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include <QTime>
#include <QDebug>

#include "M3DApp.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "RenderSystem.h"

class QOpenGLContext;

namespace M3D{
	const int UPDATES_PER_SECOND = 60;
	const double MS_PER_UPDATE = 1.0 / UPDATES_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

    float dir = 1;
    float scaleDir = 1;
    double lastTime = 0;
    float camDeg = 0;
    float boxDeg = 0;

    Entity land;
    Entity box1;
    Entity box2;
    Entity box3;
    Camera *camera = NULL;

	M3DApp::M3DApp(){
		initialized = false;
		running = false;
	}

	M3DApp::~M3DApp(){
	
	}

	bool M3DApp::initialize(int width, int height){
		using std::cout;

		if(initialized){
            qDebug()<<"Application already initilized!\n";
			return false;
		}

        qDebug()<<"Starting initialization.\n";
		screenWidth = width;
		screenHeight = height;
        /*
		if(glfwInit() == GL_FALSE){
			cout<<"Could not initialize GLFW!\n";
			return false;
		}

		cout<<"GLFW has been initialized.\n";

        */

        /*if(glfwOpenWindow(width, height,0 , 0, 0 ,0 ,16 ,0 ,GLFW_WINDOW) == GL_FALSE){
			cout<<"Could not create window!\n";
			glfwTerminate();
			return false;
        } */

        QSurfaceFormat format;
        format.setSamples(4);
        format.setMajorVersion(2);
        format.setMinorVersion(1);
        window.setFormat(format);
        window.resize(width, height);
        window.show();
        window.initialize();

        qDebug()<<"Window opened.\n";
        /*
        QOpenGLContext *context = window.m_context;
        context->makeCurrent(window);
        GLenum error = glewInit();
        if(error != GLEW_OK){
            cout<<"Could not initialize GLEW: "<<glewGetErrorString(error)<<std::endl;
            //glfwTerminate();
			return false;
		}

		cout<<"GLEW has been initialized\n";

		if(!GLEW_VERSION_2_1){
			cout<<"OpenGL version 2.1 must be supported!\n";
            //glfwTerminate();
			return false;
		}

		cout<<"OpenGL 2.1 is supported\n";
        */
		if(!resourceManager.initialize()){
			cout<<"ResourceManager initialization failed!\n";
            //glfwTerminate();
			return false;
		}

        qDebug()<<"ResourceManager initialized.\n";

		if(!renderSystem.initialize(screenWidth, screenHeight)){
			cout<<"RenderSystem initialization failed!\n";
            //glfwTerminate();
			return false;
		}

        qDebug()<<"RenderSystem initialized.\n";

		if(!sceneManager.initialize(&renderSystem)){
			cout<<"SceneManager initialization failed\n";
            //glfwTerminate();
			return false;
		}
        window.setSceneManager(&sceneManager);
        qDebug()<<"SceneManager initialized.\n";

        qDebug()<<"Initialization complete!\n";
		initialized = true;
		return true;
	}

    int M3DApp::run(QGuiApplication *qtApp){
		if(!initialized){
			std::cout<<"Application has not been initialized first!\n";
			return EXIT_FAILURE;
		}

		std::cout<<"Application starting.\n";

        std::cout<<"Starting QT app"<<std::endl;


        QTime time;
        time.start();

		
		running = true;
		//do stuff

		GLuint vert = resourceManager.loadShader(GL_VERTEX_SHADER, "lightSpec_120.vert");
		GLuint frag = resourceManager.loadShader(GL_FRAGMENT_SHADER, "lightSpec_120.frag");
		std::vector<GLuint> shaders;
		shaders.push_back(vert);
		shaders.push_back(frag);

		GLuint prog = resourceManager.createProgram(shaders);

		sceneManager.setGlobalLightDir(glm::vec3(1.0f));
		sceneManager.setGlobalLightIntensity(glm::vec4(1.0f));
		sceneManager.setAmbientLightIntensity(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

		
		Mesh* landMesh = resourceManager.loadObjFile("land.obj");
		Mesh* boxMesh = resourceManager.loadObjFile("decocube_nf4k.obj");
		if(landMesh == NULL || boxMesh == NULL) {
			std::cout<<"Mesh was Null, shuting down\n";
			shutdown();
		}
		boxMesh->setOriginOffset(glm::vec3(-0.5f, -0.5f, -0.5f));
		
		Material landMat;
		landMat.setProgram(prog);
		landMat.setDiffuseColor(glm::vec4(0.0f, 0.7f, 0.0f, 1.0f));
		landMat.setShininessFactor(2.0f);

		Material box1Mat;
		box1Mat.setProgram(prog);
		box1Mat.setDiffuseColor(glm::vec4(0.4f, 0.0f, 0.8f, 1.0f));
		box1Mat.setShininessFactor(2.0f);

		Material box2Mat;
		box2Mat.setProgram(prog);
		box2Mat.setDiffuseColor(glm::vec4(0.7f, 0.0f, 0.0f, 1.0f));
		box2Mat.setShininessFactor(70.0f);

		Material box3Mat;
		box3Mat.setProgram(prog);
		box3Mat.setDiffuseColor(glm::vec4(0.8f, 0.8f, 0.0f, 1.0f));
		box3Mat.setShininessFactor(7.0f);

		land.setMaterial(&landMat);
		land.setMesh(landMesh);
		land.setScale(glm::vec3(3.0f));
		land.setVisible(true);
		
		box1.setMaterial(&box1Mat);
		box1.setMesh(boxMesh);
		box1.setPosition(0.0f, 1.0f, 0.0f);
		box1.setVisible(true);

		box2.setMaterial(&box2Mat);
		box2.setMesh(boxMesh);
		box2.setPosition(-2.0f, 1.0f, 0.0f);
		box2.setVisible(true);

		box3.setMaterial(&box3Mat);
		box3.setMesh(boxMesh);
		box3.setPosition(2.0f, 1.0f, 0.0f);
		box3.setVisible(true);

		sceneManager.addEntity(&land);
		sceneManager.addEntity(&box1);
		sceneManager.addEntity(&box2);
		sceneManager.addEntity(&box3);
		
        camera = sceneManager.getMainCamera();
		camera->setPosition(glm::vec3(5.0f, 3.0f, 5.0f));
		camera->setTarget(glm::vec3(0.0f, 1.0f, 0.0f));

        lastTime = time.second() + (time.msec() / 1000.0);

		std::cout<<"Starting main loop. Updates per second: "<<UPDATES_PER_SECOND<<" Min MS per update "<< MS_PER_UPDATE<<" Framskip "<<MAX_FRAMESKIP<<std::endl;


        return qtApp->exec();
	}

	void M3DApp::update(double time){
        while(running){
            double currentTime = time;
            double elapsedTime = currentTime - lastTime;
            float interpolation;
            int loops = 0;


            while(currentTime >= lastTime && loops < MAX_FRAMESKIP){

                glm::vec3 pos = box3.getPosition();
                if(pos.y > 2 || pos.y < 0.75)
                    dir = -dir;

                pos.y += 0.01 * dir;
                box3.setPosition(pos);

                glm::vec3 scale = box1.getScale();
                if(scale.x > 1.5 || scale.x <0.5)
                    scaleDir = -scaleDir;

                scale.x += 0.01 * scaleDir;
                box1.setScale(scale);


                glm::vec3 camPos = camera->getPosition();
                camDeg += .001;
                if(camDeg >= 360)
                    camDeg = 0;
                camPos.x = cos(camDeg) * 5;
                camPos.z = sin(camDeg) * 5;
                camera->setPosition(camPos);

                glm::vec3 entityRot = box2.getRotation();
                boxDeg += 1;
                if(boxDeg >= 360)
                    boxDeg = 0;
                entityRot.y = boxDeg;
                entityRot.x = boxDeg;

                box2.setRotation(entityRot);

                lastTime += MS_PER_UPDATE;
            }

            interpolation = 0; //float( glfwGetTime() + MS_PER_UPDATE - lastTime) / float(MS_PER_UPDATE);

            render(interpolation);



            /*if(glfwGetKey( GLFW_KEY_ESC) || !glfwGetWindowParam( GLFW_OPENED )){
                delete landMesh;
                delete boxMesh;
                shutdown();
            }*/
        }
		
	}

	void M3DApp::render(double time){
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			sceneManager.renderScene();

            /*glfwSwapBuffers();*/
	}

	void M3DApp::shutdown(){
		std::cout<<"Shutting down application.\n";
		if(initialized){
            /*glfwTerminate();*/

			initialized = false;
		}

		running = false;
	}
}
