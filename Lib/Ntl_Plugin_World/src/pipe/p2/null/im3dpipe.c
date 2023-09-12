/*
 * Immediate mode rendering (platform-specific)
 *
 * Copyright (c) Criterion Software Limited
 */

/* The documentation in here is platform-specific versions of function-
 * descriptions for functions in baim3d.c
 */

/***************************************************************************
 *                                                                         *
 * Module  : im3dpipe.c                                                    *
 *                                                                         *
 * Purpose : Platform specific pipeline construction                       *
 *                                                                         *
 **************************************************************************/

/****************************************************************************
 Includes
 */

#include "batypes.h"

#include "bapipe.h"
#include "p2core.h"
#include "p2define.h"
#include "p2stdcls.h"
#include "bavector.h"
#include "bamatrix.h"

#include "im3dpipe.h"



 /**
 * \ingroup rwim3dnull
 * \page RwIm3DGetTransformPipelineplatform RwIm3DGetTransformPipeline (platform-specific)
 *
 * The Im3D transform pipeline for the NULL driver is shown below.
 * Note that the NULL driver is not meant to render anything, so this
 * pipeline is empty.
 *
 * \see RwIm3DEnd
 * \see RwIm3DRenderIndexedPrimitive
 * \see RwIm3DRenderLine
 * \see RwIm3DRenderPrimitive
 * \see RwIm3DRenderTriangle
 * \see RwIm3DTransform
 * \see RwIm3DGetRenderPipeline
 * \see \ref RwIm3DGetRenderPipelineplatform
 * \see RwIm3DGetTransformPipeline
 * \see RwIm3DSetRenderPipeline
 * \see RwIm3DSetTransformPipeline
 *
 */
RwBool
_rwIm3DCreatePlatformTransformPipeline(RxPipeline **globalPipe)
{
    RxPipeline        *pipe;

    RWFUNCTION(RWSTRING("_rwIm3DCreatePlatformTransformPipeline"));

    RWASSERT(globalPipe != NULL);

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxPipeline        *lpipe;

        pipe->pluginId = rwID_COREPLUGIN;
        lpipe = RxPipelineLock(pipe);
        if (lpipe)
        {
            pipe = RxLockedPipeUnlock(lpipe);
            RWASSERT(lpipe != NULL);
            RWASSERT(pipe != NULL);
            RWASSERT(pipe == lpipe);

            if (pipe != NULL)
            {
               *globalPipe = pipe;
                RwIm3DSetTransformPipeline(pipe);

                RWRETURN(TRUE);
            }
        }

        /* Failed to lock it */
        RxPipelineDestroy(pipe);
    }

    /* Failed to create it - ran out of memory? */
    RWRETURN(FALSE);
}

void
_rwIm3DDestroyPlatformTransformPipeline(RxPipeline **globalPipe)
{
    RWFUNCTION(RWSTRING("_rwIm3DDestroyPlatformTransformPipeline"));

    RWASSERT(globalPipe != NULL);

    /* Resinstate the generic transform pipe */
    RwIm3DSetTransformPipeline(NULL);
    if (NULL != *globalPipe)
    {
        RxPipelineDestroy(*globalPipe);
       *globalPipe = NULL;
    }

    RWRETURNVOID();
}

/**
 * \ingroup rwim3dnull
 * \page RwIm3DGetRenderPipelineplatform RwIm3DGetRenderPipeline (platform-specific)
 *
 * The Im3D render pipelines for the NULL driver are empty, as the NULL
 * driver is not meant to render anything. The same, empty pipeline is
 * used for all primitive types.
 *
 * \see RwIm3DEnd
 * \see RwIm3DRenderIndexedPrimitive
 * \see RwIm3DRenderLine
 * \see RwIm3DRenderPrimitive
 * \see RwIm3DRenderTriangle
 * \see RwIm3DTransform
 * \see RwIm3DGetRenderPipeline
 * \see RwIm3DGetTransformPipeline
 * \see \ref RwIm3DGetTransformPipelineplatform
 * \see RwIm3DSetRenderPipeline
 * \see RwIm3DSetTransformPipeline
 *
 */

void
_rwIm3DDestroyPlatformRenderPipelines(rwIm3DRenderPipelines *globalPipes)
{
    RWFUNCTION(RWSTRING("_rwIm3DDestroyPlatformRenderPipelines"));

    RWASSERT(globalPipes != NULL);

    /* Resinstate the generic lines pipes pipe */
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPETRILIST);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPETRIFAN);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPETRISTRIP);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPELINELIST);
    RwIm3DSetRenderPipeline(NULL, rwPRIMTYPEPOLYLINE);

    if (NULL != globalPipes->triList)
    {
        RxPipelineDestroy(globalPipes->triList);
    }
    globalPipes->triList  = NULL;
    globalPipes->triFan   = NULL;
    globalPipes->triStrip = NULL;
    globalPipes->lineList = NULL;
    globalPipes->polyLine = NULL;

    RWRETURNVOID();
}

RwBool
_rwIm3DCreatePlatformRenderPipelines(rwIm3DRenderPipelines *globalPipes)
{
    RxPipeline        *pipe;

    RWFUNCTION(RWSTRING("_rwIm3DCreatePlatformRenderPipelines"));

    RWASSERT(globalPipes != NULL);

    pipe = RxPipelineCreate();
    if (pipe)
    {
        RxLockedPipe       *lpipe;

        pipe->pluginId = rwID_COREPLUGIN;
        lpipe = RxPipelineLock(pipe);
        if (lpipe)
        {
            pipe = RxLockedPipeUnlock(lpipe);
            RWASSERT(pipe != NULL);
            RWASSERT(pipe == lpipe);

            if (NULL != pipe)
            {

                globalPipes->triList  = pipe;
                globalPipes->triFan   = pipe;
                globalPipes->triStrip = pipe;
                globalPipes->lineList = pipe;
                globalPipes->polyLine = pipe;
                /* Set our pipe as the default for all primitives... */
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPETRILIST);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPETRIFAN);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPETRISTRIP);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPELINELIST);
                RwIm3DSetRenderPipeline(pipe, rwPRIMTYPEPOLYLINE);

                RWRETURN(TRUE);
            }
        }

        /* Failed to lock the pipe */
        RxPipelineDestroy(pipe);
    }

    /* Failed to create the pipe - ran out of memory? */
    RWRETURN(FALSE);
}

