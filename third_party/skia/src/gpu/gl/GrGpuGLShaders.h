/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */



#ifndef GrGpuGLShaders_DEFINED
#define GrGpuGLShaders_DEFINED

#include "GrGpuGL.h"
#include "GrGLProgram.h"

class GrCustomStage;
class GrGpuGLProgram;

// Programmable OpenGL or OpenGL ES 2.0
class GrGpuGLShaders : public GrGpuGL {
public:
             GrGpuGLShaders(const GrGLContextInfo& ctxInfo);
    virtual ~GrGpuGLShaders();

    virtual void abandonResources();

    bool programUnitTest();

protected:
    // overrides from GrGpu
    virtual void onResetContext() SK_OVERRIDE;
    virtual bool flushGraphicsState(GrPrimitiveType type);
    virtual void setupGeometry(int* startVertex,
                               int* startIndex,
                               int vertexCount,
                               int indexCount);

private:

    // for readability of function impls
    typedef GrGLProgram::ProgramDesc ProgramDesc;
    typedef ProgramDesc::StageDesc   StageDesc;
    typedef GrGLProgram::CachedData  CachedData;

    class ProgramCache;

    // sets the texture matrix uniform for currently bound program
    void flushTextureMatrix(int stage);

    // sets the texture domain uniform for currently bound program
    void flushTextureDomain(int stage);

    // sets the color specified by GrDrawState::setColor()
    void flushColor(GrColor color);

    // sets the color specified by GrDrawState::setCoverage()
    void flushCoverage(GrColor color);

    // sets the MVP matrix uniform for currently bound program
    void flushViewMatrix();

    // flushes the parameters to two point radial gradient
    void flushRadial2(int stage);

    // flushes the parameters for convolution
    void flushConvolution(int stage);

    // flushes the normalized texel size
    void flushTexelSize(int stage);

    // flushes the color matrix
    void flushColorMatrix();

    static void DeleteProgram(const GrGLInterface* gl,
                              CachedData* programData);

    void buildProgram(GrPrimitiveType typeBlend,
                      BlendOptFlags blendOpts,
                      GrBlendCoeff dstCoeff,
                      GrCustomStage** customStages);

    ProgramCache*               fProgramCache;
    CachedData*                 fProgramData;
    GrGLuint                    fHWProgramID;
    GrGLProgram                 fCurrentProgram;
    // If we get rid of fixed function subclass this should move
    // to the GLCaps struct in parent class
    GrGLint                     fMaxVertexAttribs;

    typedef GrGpuGL INHERITED;
};

#endif

