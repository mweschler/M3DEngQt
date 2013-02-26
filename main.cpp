#include <stdlib.h>
#include <iostream>
#include "M3DApp.h"
#include <Qtgui/QGuiApplication>

int main(int argc, char *argv[]){
    QGuiApplication qtApp(argc, argv);
	M3D::M3DApp app;
	if(!app.initialize(1024, 768)){
		std::cout<<"Could not initilize, shutting down!\n";
		return EXIT_FAILURE;
	}

    return app.run(&qtApp);
}
