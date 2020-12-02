#ifndef FRAMEBUFFER_6_1_H
#define FRAMEBUFFER_6_1_H

#include <stdint.h>
#include <stdbool.h>

#include "VBoxCAPIGlue.h"

#include "framebuffer.h"

typedef struct
{
	struct IFramebufferVtbl *vtbl;
	IDisplay *vboxDisplay;
	int refCount;
	VBoxManagerContext context;
	int originX;
	int originY;
	uint32_t guestXRes;
	uint32_t guestYRes;
	uint32_t windowWidth;
	uint32_t windowHeight;
#ifdef WIN32
	ITypeInfo *infoIFrameBuffer;
#endif
	void(*handleImage)(VBoxManagerContext context, uint32_t x, uint32_t y, uint32_t width,
		uint32_t height, uint32_t imageSize, uint8_t *image);
} VBoxFramebuffer; // IFramebuffer

VBoxFramebuffer* createFramebuffer_v6_1(IDisplay *display);
void setupOrigins_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 screenId);

#ifdef WIN32
ES_HRESULT fbQueryInterface_v6_1(VBoxFramebuffer *framebuffer, const IID *iid, void **resultp);
#else
ES_HRESULT fbQueryInterface_v6_1(VBoxFramebuffer *framebuffer, const nsID *iid, void **resultp);
#endif

#ifdef WIN32
#define ComSafeArrayOut(aType, aArg)    SAFEARRAY **aArg
#else
#define ComSafeArrayOut(aType, aArg)        ES_PRUint32 *aArg##Size, aType **aArg
#endif

ES_HRESULT fbAddRef_v6_1(VBoxFramebuffer *framebuffer);
ES_HRESULT fbRelease_v6_1(VBoxFramebuffer *framebuffer);
ES_HRESULT fbGetOverlay_v6_1(VBoxFramebuffer *framebuffer, IFramebufferOverlay **overlay);
ES_HRESULT fbGetCapabilities_v6_1(VBoxFramebuffer *framebuffer, ComSafeArrayOut(ES_PRUint32, capabilities));
#ifdef WIN32
ES_HRESULT fbNotifyUpdateImage_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 x, ES_PRUint32 y, ES_PRUint32 width,
	ES_PRUint32 height, SAFEARRAY * image);
#else
ES_HRESULT fbNotifyUpdateImage_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 x, ES_PRUint32 y, ES_PRUint32 width,
	ES_PRUint32 height, ES_PRUint32 imageSize, ES_PRUint8 *image);
#endif


ES_HRESULT fbNotifyChange_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 screenId, ES_PRUint32 xOrigin,
	ES_PRUint32 yOrigin, ES_PRUint32 width, ES_PRUint32 height);
ES_HRESULT fbGetWidth_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *width);
ES_HRESULT fbGetHeight_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *height);
ES_HRESULT fbGetBitsPerPixel_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *bitsPerPixel);
ES_HRESULT fbGetBytesPerLine_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *bytesPerLine);
ES_HRESULT fbGetPixelFormat_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *pixelFormat);

#ifdef WIN32
static HRESULT LoadTypeInfo(REFIID riid, ITypeInfo **pTInfo);
HRESULT fbGetTypeInfoCount(VBoxFramebuffer *framebuffer, ES_PRUint32 *count);
HRESULT fbGetTypeInfo(VBoxFramebuffer *framebuffer, ES_PRUint32 iTInfo, LCID lcid, ITypeInfo **ppTInfo);
HRESULT fbGetIDsOfNames(VBoxFramebuffer *framebuffer, REFIID riid, LPOLESTR *rgszNames, UINT cNames,
	LCID lcid, DISPID *rgDispId);
HRESULT fbInvoke(VBoxFramebuffer *framebuffer, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
#endif

#endif // FRAMEBUFFER_6_1_H
