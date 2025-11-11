#include <kis_opengl.h>
#include <kis_debug.h>

KisOpenGL::OpenGLRenderer KisOpenGL::RendererConfig::rendererId() const
{
    KisOpenGL::OpenGLRenderer result = RendererAuto;

    if (format.renderableType() == QSurfaceFormat::OpenGLES &&
        angleRenderer == AngleRendererD3d11Warp) {

        result = RendererSoftware;

    } else if (format.renderableType() == QSurfaceFormat::OpenGLES) {
        // If D3D11, D3D9?, Default (which is after probing, if selected)
        // or the system specifies QT_OPENGL_ES_2
        result = RendererOpenGLES;
    } else if (format.renderableType() == QSurfaceFormat::OpenGL) {
        result = RendererDesktopGL;
    } else if (format.renderableType() == QSurfaceFormat::DefaultRenderableType &&
               angleRenderer == AngleRendererD3d11) {
        // noop
    } else {
        qWarning() << "WARNING: unsupported combination of OpenGL renderer" << ppVar(format.renderableType()) << ppVar(angleRenderer);
    }

    return result;
}