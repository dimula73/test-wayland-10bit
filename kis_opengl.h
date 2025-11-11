/*
 *  SPDX-FileCopyrightText: 2007 Adrian Page <adrian@pagenet.plus.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef KIS_OPENGL_H_
#define KIS_OPENGL_H_

/** @file */

#include <QtGlobal>
#include <QFlags>

#include <QSurfaceFormat>
#include <QStringList>

#define KRITAUI_EXPORT

class QOpenGLContext;
class QString;
class QSurfaceFormat;

/**
 * This class manages a shared OpenGL context and provides utility
 * functions for checking capabilities and error reporting.
 */
class KRITAUI_EXPORT KisOpenGL
{
public:
    enum FilterMode {
        NearestFilterMode,  // nearest
        BilinearFilterMode, // linear, no mipmap
        TrilinearFilterMode, // LINEAR_MIPMAP_LINEAR
        HighQualityFiltering // Mipmaps + custom shader
    };

    enum OpenGLRenderer {
        RendererNone = 0x00,
        RendererAuto = 0x01,
        RendererDesktopGL = 0x02,
        RendererOpenGLES = 0x04,
        RendererSoftware = 0x08
    };
    Q_DECLARE_FLAGS(OpenGLRenderers, OpenGLRenderer)

    enum AngleRenderer {
        AngleRendererDefault    = 0x0000,
        AngleRendererD3d11      = 0x0002,
        AngleRendererD3d9       = 0x0004,
        AngleRendererD3d11Warp  = 0x0008, // "Windows Advanced Rasterization Platform"
    };

    struct KRITAUI_EXPORT RendererConfig {
        QSurfaceFormat format;
        AngleRenderer angleRenderer = AngleRendererDefault;

        OpenGLRenderer rendererId() const;
    };

};

#endif // KIS_OPENGL_H_
