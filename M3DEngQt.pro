CONFIG += console

SOURCES += \
    SceneManager.cpp \
    ResourceManager.cpp \
    RenderSystem.cpp \
    Mesh.cpp \
    Material.cpp \
    main.cpp \
    M3DApp.cpp \
    Entity.cpp \
    Camera.cpp \
    window.cpp

HEADERS += \
    SceneManager.h \
    ResourceManager.h \
    RenderSystem.h \
    Mesh.h \
    Material.h \
    M3DApp.h \
    Entity.h \
    Camera.h \
    window.h

OTHER_FILES += \
    lightSpec_120.vert \
    lightSpec_120.frag \
    light_120.vert \
    light_120.frag \
    basic.vert \
    basic.frag

INCLUDEPATH += 3rdparty/glm-0.9.4.1/include



QT += core widgets opengl

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rdparty/glew-1.9.0/lib/ -lglew32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rdparty/glew-1.9.0/lib/ -lglew32
else:unix: LIBS += -L$$PWD/3rdparty/glew-1.9.0/lib/ -lglew32

INCLUDEPATH += $$PWD/3rdparty/glew-1.9.0/include
DEPENDPATH += $$PWD/3rdparty/glew-1.9.0/include
