#pragma once

#include <QtWidgets>
#include <QGLViewer/qglviewer.h>
#include <qapplication.h>

#include <string>
#include <vector>
#include <algorithm>

#include "JaalHeaders.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;
using namespace boost;
using namespace qglviewer;
using namespace Jaal;

#include "EntityColor.hpp"
#include "FontsManager.hpp"
#include "Image.hpp"
#include "Lights.hpp"
#include "Material.hpp"
#include "Tube.hpp"
#include "QtWaitingSpinnerWidget.hpp"
#include "SceneFloor.hpp"

#define SpinBoxi(box, f) connect(box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), f)
#define SpinBoxd(box, f) connect(box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), f)
#define CheckBox(box, f) connect(box, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), f)
#define ComboBox(box, f) connect(box, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), f)
#define RadioButton(button, f) connect(button, static_cast<void(QRadioButton::*)(bool)>(&QRadioButton::toggled), f)
#define PushButton(button, f)  connect(button, &QPushButton::clicked, f)
#define LineEdit(line,f) connect(line, &QLineEdit::returnPressed, f)

enum class JViewDirection
{
    ANY_VIEW,
    RIGHT_VIEW,
    LEFT_VIEW,
    TOP_VIEW,
    BOTTOM_VIEW,
    FRONT_VIEW,
    BACK_VIEW,
    CUBE_POINT_0_VIEW,
    CUBE_POINT_1_VIEW,
    CUBE_POINT_2_VIEW,
    CUBE_POINT_3_VIEW,
    CUBE_POINT_4_VIEW,
    CUBE_POINT_5_VIEW,
    CUBE_POINT_6_VIEW,
    CUBE_POINT_7_VIEW
};

#include <QGLViewer/manipulatedCameraFrame.h>

/* Copyright (c) Mark J. Kilgard, 1996. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */

/* screendoor demonstrates "screen door" transparency using
   OpenGL's polygon stipple feature. */

/* Screen door transparency stipple patterns, originally generated by
   Tim Hall (tjh@world.std.com) based on the 4x4 dither matrix
   described in "Computer Graphics Principles and Practice, 2nd ed." in
   the "Halftone Approximation" section (13.1.2).  Each 4x4 pattern is
   replicated over OpenGL's 32x32 pixel stipple pattern.  mjk converted
   Tim's patterns to be expressed as GLubytes instead of unsigned ints
   to avoid byte ordering problems. */

#if 0  /* Comment containing C comments. */

Example usage:

/* Assumes default unpack pixel store settings; see glPixelStore */

glEnable(GL_POLYGON_STIPPLE);
glPolygonStipple(stippleMask[0]);  /* 0% opaqueness */
glPolygonStipple(stippleMask[8]);  /* 50% opaqueness */
glPolygonStipple(stippleMask[16]); /* 100% opaqueness */

#endif

const GLubyte stippleMask[17][128] = {
    /* NOTE: 0% opaqueness is faster to set and probably faster to render with:
    glDisable(GL_POLYGON_STIPPLE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },

    {
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },

    {
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00
    },

    {
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00
    },

    {
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00
    },

    {
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x00, 0x00, 0x00, 0x00
    },

    {
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x44, 0x44, 0x44, 0x44, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11
    },

    {
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x11, 0x11, 0x11, 0x11
    },

    {
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55
    },

    {
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55
    },

    {
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xee, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55
    },

    {
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xbb, 0xbb, 0xbb, 0xbb, 0x55, 0x55, 0x55, 0x55
    },

    {
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55
    },

    {
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55
    },

    {
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77
    },

    {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x77, 0x77, 0x77, 0x77
    },

    /* NOTE: 100% opaqueness is faster to set and probably faster to render with:
          glDisable(GL_POLYGON_STIPPLE); */
    {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    },
};

class JaalViewer;

inline
std::string StdString( const QString &qstr) {
    return qstr.toUtf8().constData();
}

class JViewComponent {
public:
    static void displayList(GLuint &dlistID);

    JViewComponent()
    {
        viewManager = nullptr;
        active  = 1;
    }

    virtual ~JViewComponent() {}

    void setName(const string &s)
    {
        name = s;
    }

    string getName() const
    {
        return name;
    }

    virtual void animate() {};
    virtual void drawWithNames() {};
    virtual void fastDraw() {};
    virtual void draw() {};
    virtual void actionMouseEvent(int ) {};
    virtual void refreshDisplay() {};

    virtual void setActive( bool s )
    {
        active = s;
    }

    bool isActive() const
    {
        return active;
    }

    void setViewManager( JaalViewer *q)
    {
        viewManager  = q;
    }

    JaalViewer *getViewManager() const
    {
        return viewManager;
    }

protected:
    JaalViewer *viewManager;
    bool active;
    string name;
};

typedef boost::shared_ptr<JViewComponent> JViewComponentPtr;

///////////////////////////////////////////////////////////////////////////////
class JLights;
//////////////////////////////////////////////////////////////////////////////////////////////

struct JMagnifyingLens
{
    JMagnifyingLens();

    JaalViewer  *viewManager;
    bool active  = 1;
    bool deleted = 0;
    int  width, height;
    int  lensRadius, projRadius;
    int  center[2];
    int  shape;
    int  connection[4];
    int  borderWidth;
    GLuint  texID;

    JColor  borderColor;
    bool    filled;

    int  projWidth, projHeight;
    int  projCenter[2];

    void draw();
    void drawROI();
    void rectangleROI();
    void circleROI();
    void captureRegion();
    void drawCircle(int xs, int ys);
};

typedef boost::shared_ptr<JMagnifyingLens> JMagnifyingLensPtr;

class JaalViewer :  public QGLViewer {
    Q_OBJECT
public:
    typedef boost::shared_ptr<JaalViewer> shared_ptr;

    static const int ORTHOGRAPHIC_PROJECTION   = 0;
    static const int PERSPECTIVE_PROJECTION    = 1;
    static const int HYPERBOLIC_PROJECTION     = 2;

    static const int STATIONARY_LIGHTS         = 0;
    static const int MOVE_LIGHTS_WITH_CAMERA   = 1;
    static const int MOVE_LIGHTS_WITH_AXIS     = 2;

    static const int FREE_ROTATION  = 0;
    static const int XAXIS_ROTATION = 1;
    static const int YAXIS_ROTATION = 2;
    static const int ZAXIS_ROTATION = 3;
    static const int NO_ROTATION    = 4;

    static const int FREE_TRANSLATION  = 0;
    static const int XAXIS_TRANSLATION = 1;
    static const int YAXIS_TRANSLATION = 2;
    static const int ZAXIS_TRANSLATION = 3;
    static const int NO_TRANSLATION    = 4;

    static void  drawBox( const JBoundingBox *b);
    static void  drawBox( const JHexahedronPtr  &b);

    JaalViewer( QWidget *parent_ = nullptr);

    void setDimension( int d)
    {
        viewer_dim = d;
    }

    void resetView( const JViewDirection &v);

    void setProjection( int p )
    {
        projectionType = p;
        if( projectionType == ORTHOGRAPHIC_PROJECTION ) {
            camera()->setType(Camera::ORTHOGRAPHIC);
        } else
            camera()->setType(Camera::PERSPECTIVE);
        updateGL();
    }

    void setBackgroundColor(float *rgb)
    {
        backgroundColor[0] = rgb[0];
        backgroundColor[1] = rgb[1];
        backgroundColor[2] = rgb[2];
        updateGL();
    }

    JColor getBackgroundColor() const
    {
        JColor clr;
        clr[0] = backgroundColor[0];
        clr[1] = backgroundColor[1];
        clr[2] = backgroundColor[2];
        clr[3] = 1.0;
        return clr;
    }

    boost::shared_ptr<JLights> getLights() const {
        return lights;
    }

    boost::shared_ptr<JSceneFloor> getSceneFloor() const
    {
        return sceneFloor;
    }

    void setAxis( bool v )
    {
        displayAxis = v;
        updateGL();
    }

    void attach(const boost::shared_ptr<JViewComponent> &c)
    {
        string s = c->getName();
        if( s.empty() ) {
            cout << "Warning: unnamed component is not attached to the viewer " << endl;
            return;
        }
        if( getComponent(s) == nullptr ) components.push_back(c);
    }

    void detach( const boost::shared_ptr<JViewComponent> &c )
    {
        boost::remove_erase( components, c);
        /*
                vector<JViewComponent* > ::iterator cend = remove(components.begin(), components.end(), c);
                components.erase(cend, components.end());
        */
    }

    void activateComponents()
    {
        for(auto vc: components)
            vc->setActive(1);
    }
    void deactivateComponents()
    {
        for(auto vc : components)
            vc->setActive(0);
    }

    JViewComponentPtr getComponent(const string &s)
    {
        for(auto vc: components)
            if( vc->getName() == s) return vc;
        return nullptr;
    }

    JViewComponentPtr getComponent(size_t id)
    {
        if( components.empty() ) return nullptr;
        if( id < components.size() )
            return components[id];
        return nullptr;
    }

    int  getNumComponents() const
    {
        return components.size();
    }

    void attach(QObject *obj)
    {
        bool found = 0;
        for( size_t i = 0; i < listeners.size(); i++)
            if( listeners[i] == obj) found = 1;
        if( !found) listeners.push_back(obj);
    }

    void detach( QObject *obj )
    {
        vector<QObject*>::iterator cend = remove(listeners.begin(), listeners.end(), obj);
        listeners.erase(cend, listeners.end());
    }

    void refreshDisplay()
    {
        updateGL();
    }

    void setRotationAxis(int p);
    void setTranslationAxis(int p);

    void setFloor( bool v);

    void  freezeView( bool f );

    void addObject(const JMagnifyingLensPtr &p) {
        zoomLens.push_back(p);
    }

    void removeAllLens() {
        zoomLens.clear();
    }

// Screen Position of Mouse
    const Point2I &getMouseStartPixelPosition() const
    {
        return mouseStartPixelPos;
    }
    const Point2I &getMouseEndPixelPosition() const
    {
        return mouseEndPixelPos;
    }
    const Point2I &getMouseCurrentPixelPosition() const
    {
        return mouseCurrPixelPos;
    }

    int getPixelPosition( const Point2I &pixelPos, Point3D &xyz) const;

    // World Position of Mouse
    int getMouseStartXYZPosition( Point3D &xyz) const
    {
        int err = getPixelPosition( mouseStartPixelPos, xyz);
        return err;
    }
    int getMouseEndXYZPosition( Point3D &xyz) const
    {
        int err = getPixelPosition( mouseEndPixelPos, xyz);
        return err;
    }
    int getMouseCurrentXYZPosition( Point3D &xyz) const
    {
        int err = getPixelPosition( mouseCurrPixelPos, xyz);
        return err;
    }

    void setSceneRadius(double r)
    {
        scene_radius = r;
    }

    virtual void initializeGL();

    void addBox( const JBoundingBox &b)
    {
        box.setUnion(b);
//      resetView( JViewDirection::ANY_VIEW);
    }

    void setBoundingBox( bool v)
    {
        displayBox = v;
    }
    void setScale( double s ) {
        scaleFactor = s;
    }

    void setCenter( const Point3D &v)
    {
        qglviewer::Vec c;
        c[0] = v[0];
        c[1] = v[1];
        c[2] = v[2];
        this->camera()->setSceneCenter(c);
    }

    void setGlobalCenter();

    const vector<size_t>  &getPickedEntities() const {
        return picked_entities;
    }

    void resetSceneBox();
    void drawScene();

    boost::shared_ptr<QtWaitingSpinner> qtWaitSpinner;

protected:
    virtual void fastDraw();
    virtual void draw();
    virtual void animate();
    virtual void drawWithNames();
    virtual void init();
    virtual void postDraw();

    virtual bool notify( QObject *recv, QEvent *e);
    virtual void mousePressEvent( QMouseEvent *e);
    virtual void mouseReleaseEvent( QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void endSelection(const QPoint &p);
    virtual void showEvent( QShowEvent *e);
    virtual void paintEvent(QPaintEvent *);
    virtual void wheelEvent(QWheelEvent *);

private:
    QWidget *parent;
    vector<boost::shared_ptr<JViewComponent>> components;
    vector<QObject*>        listeners;

    double scene_radius;
    bool   mousetracking;
    bool   frozenView;

    bool  displayAxis;
    bool  displayBox;
    bool  displayFloor;

    bool  saveAnimation;
    int   numAnimFrames, currAnimFrame;

    int  viewer_dim;
    int  perspective_view;
    int  projectionType;
    int  faceCulling;
    double scaleFactor;

    vector<JMagnifyingLensPtr> zoomLens;
    boost::shared_ptr<JLights> lights;
    boost::shared_ptr<JSceneFloor> sceneFloor;

    JColor  backgroundColor;
    AxisPlaneConstraint  *worldConstraint;

    JBoundingBox  box;

    Point2I  mouseStartPixelPos, mouseEndPixelPos, mouseCurrPixelPos;

    void notifyMouseEvent(int id)
    {
        for( size_t i = 0; i < components.size(); i++)
            components[i]->actionMouseEvent(id);
    }
    vector<size_t> picked_entities;
    void drawAxis();
};
////////////////////////////////////////////////////////////////////////////////
class JWaitCursor
{
public:
    JWaitCursor()
    {
        isSpinning = false;
    }

    ~JWaitCursor()
    {
        if( isSpinning ) stop();
    }

    void start() {
        QApplication::setOverrideCursor( QCursor(Qt::WaitCursor));
        isSpinning = 1;
    }

    void stop() {
        QApplication::restoreOverrideCursor();
        isSpinning = 0;
    }
private:
    bool isSpinning;
};

////////////////////////////////////////////////////////////////////////////////

/*
class LaplaceMatrixViewer : public JViewComponent {
public:
    static const int  PRIMAL_GRAPH = 0;
    static const int  DUAL_GRAPH   = 1;

    LaplaceMatrixViewer()
    {
        mesh = nullptr;
        bound_anchors = 0;
        graphType = 0;
        disk = gluNewQuadric();
        gluQuadricDrawStyle( disk, GLU_FILL );
        matrix_grid = 0;
        fontsScale = 1.0;
        stepLabels = 1;
        pointSize  = 1.0;
        glyph      = 1;
        name       = "MatrixViewer";
    }

    // Set the primal mesh...
    void setMesh( JMeshPtr m )
    {
        mesh = m;
    }

    // What kind of mesh it is: Primal or Dual graph. Default value
    // is PRIMAL_MESH.
    void setGraphType( int t )
    {
        graphType = t;
    }

    // In the Dual mesh, do you wish to include boundary anchors. Remember
    // that all internal simplicies have at the most 2 lower entities as
    // neighbours. Since entities near the boundary may have only one
    // neighbour, so in many applications, we can dual edge from the
    // boundary simplex to the simplex on the boundary ( which we
    // call "Anchor" as they act like constrains when there are
    // geometric transformations ( for example: Laplacian smoothing).
    //
    // Default: No anchors.
    void setBoundaryAnchors( bool b )
    {
        bound_anchors = b;
    }

    // Do you wish to create a grid on the Matrix viewer. Sometimes
    // useful for small graphs.
    // Default: No grid...
    void setMatrixGrid( bool f )
    {
        matrix_grid = f;
    }

    // Set the font scale, to display the nodes iD on the top and
    // to the right of the matrix..
    // Default: 1.0
    void setFontsScale( double fs )
    {
        fontsScale = fs;
    }

    // For large graphs, displaying all the node Ids on the
    // top and to the rights is not essentials and may be
    // inefficient. We can skip nodes to display the IDs.
    // For example display:1, 10, 20, 30 .... ).
    // Default : 1.
    // Acceptable value : Any n >= 1.
    void setStepLabels(int  n)
    {
        stepLabels = n;
    }

    void setGlyph( int g )
    {
        glyph = g;
    }

    void setPointSize( double s)
    {
        pointSize = s;
    }

    // Virtual function: Draw the matrix.
    void draw();

private:
    JMeshPtr mesh;
    GLUquadricObj *disk;
    int    glyph;
    bool   matrix_grid;
    double dl, fontsScale;
    double pointSize;

    bool  bound_anchors;  // In a dual graph, we can put anchors on the boundary entities.
    int   graphType;  // 0: Primary mesh  1: Dual Mesh.
    int   stepLabels;

    void  draw_primal();
    void  draw_dual();
    void  draw_edge(JEdgePtr e, int t);
    void  fill_ij(double px, double py, int t);
    void  gridmatrix();
    void  fillmatrix();
    void  drawids();
};
*/

