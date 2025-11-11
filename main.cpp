#include <QApplication>
#include <QMessageBox>

#include <QSurfaceFormat>

#include <kis_debug.h>
#include <kis_opengl.h>
#include <KisOpenGLModeProber.h>
#include <KisSurfaceColorSpaceWrapper.h>

#include <QOpenGLContext>

inline QDebug operator<<(QDebug dbg, QOpenGLContext::OpenGLModuleType moduleType)
{
    QDebugStateSaver saver(dbg);
    dbg.nospace();

    switch (moduleType) {
    case QOpenGLContext::LibGL:
        dbg << "LibGL";
        break;
    case QOpenGLContext::LibGLES:
        dbg << "LibGLES";
        break;
    default:
        dbg << "Unknown";
        break;
    }

    return dbg;
}


void tryOpenGLFormat(const QOpenGLContext::OpenGLModuleType openGLModuleType,
                     const QSurfaceFormat::RenderableType renderableType,
                     const int bitDepth,
                     const bool useCompatibilityProfile)
{
    QSurfaceFormat format;

    switch (openGLModuleType) {
    case QOpenGLContext::LibGL:
        format.setVersion(3, 3);

        if (useCompatibilityProfile) {
            format.setProfile(QSurfaceFormat::CompatibilityProfile);
        }

        break;
    case QOpenGLContext::LibGLES:
        format.setVersion(3, 0);
        format.setProfile(QSurfaceFormat::NoProfile);
        break;
    }

    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    KisOpenGLModeProber::initSurfaceFormatFromConfig({KisSurfaceColorSpaceWrapper(), bitDepth}, &format);

    format.setRenderableType(renderableType);

    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(0); // Disable vertical refresh syncing

    KisOpenGL::RendererConfig config;
    config.format = format;
    config.angleRenderer = KisOpenGL::AngleRendererDefault;

    qDebug() << "===";
    qDebug() << "Probing module:" << openGLModuleType << "renderable:" << renderableType << ppVar(useCompatibilityProfile);
    qDebug() << "   request fmt:" << format;


    auto info = KisOpenGLModeProber::instance()->probeFormat(config);

    if (!info) {
        qDebug() << "   FAILED!";
    } else {
        qDebug() << "   SUCCESS!";
        qDebug() << "      " << "result fmt:" << info->format();
        qDebug() << "      " << "renderable:" << info->format().renderableType();
    }
}


int main(int argc, char *argv[])
{

    tryOpenGLFormat(QOpenGLContext::LibGL, QSurfaceFormat::DefaultRenderableType, 8, true);
    tryOpenGLFormat(QOpenGLContext::LibGL, QSurfaceFormat::OpenGL, 8, true);
    tryOpenGLFormat(QOpenGLContext::LibGLES, QSurfaceFormat::OpenGLES, 8, false);

    tryOpenGLFormat(QOpenGLContext::LibGL, QSurfaceFormat::OpenGL, 10, true);
    tryOpenGLFormat(QOpenGLContext::LibGLES, QSurfaceFormat::OpenGLES, 10, false);

    tryOpenGLFormat(QOpenGLContext::LibGL, QSurfaceFormat::OpenGL, 16, true);
    tryOpenGLFormat(QOpenGLContext::LibGLES, QSurfaceFormat::OpenGLES, 16, false);


    QApplication app(argc, argv);

    QMessageBox::information(nullptr, "Hello", "Hello world!");

    return 0;
}
