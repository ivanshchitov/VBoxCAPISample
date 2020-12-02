#include "framebuffer_6_1.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
void* vtable_v6_1[24] = { fbQueryInterface_v6_1, fbAddRef_v6_1, fbRelease_v6_1,
fbGetTypeInfoCount, fbGetTypeInfo, fbGetIDsOfNames, fbInvoke,
fbGetWidth_v6_1, fbGetHeight_v6_1,
fbGetBitsPerPixel_v6_1, fbGetBytesPerLine_v6_1, fbGetPixelFormat_v6_1, fbGetHeightReduction,
fbGetOverlay_v6_1, fbGetWinId, fbGetCapabilities_v6_1, fbNotifyUpdate,
fbNotifyUpdateImage_v6_1, fbNotifyChange_v6_1, fbVideoModeSupported,
fbGetVisibleRegion, fbSetVisibleRegion, fbProcessVHWACommand,
fbNotify3DEvent };
#else
void* vtable_v6_1[20] = { fbQueryInterface_v6_1, fbAddRef_v6_1, fbRelease_v6_1,
fbGetWidth_v6_1, fbGetHeight_v6_1,
fbGetBitsPerPixel_v6_1, fbGetBytesPerLine_v6_1, fbGetPixelFormat_v6_1, fbGetHeightReduction,
fbGetOverlay_v6_1, fbGetWinId, fbGetCapabilities_v6_1, fbNotifyUpdate,
fbNotifyUpdateImage_v6_1, fbNotifyChange_v6_1, fbVideoModeSupported,
fbGetVisibleRegion, fbSetVisibleRegion, fbProcessVHWACommand,
fbNotify3DEvent };
#endif

/*!
* \brief Creates the VBoxFramebuffer structure and initializes it's vtbl field with proper function pointers
* \param framebuffer VBoxFramebuffer instance pointer.
*/
VBoxFramebuffer* createFramebuffer_v6_1(IDisplay *display)
{
	VBoxFramebuffer* frameBuffer = (VBoxFramebuffer*)calloc(1, sizeof(VBoxFramebuffer));
	frameBuffer->vtbl = (struct IFramebufferVtbl *) vtable_v6_1;
	frameBuffer->vboxDisplay = display;
	frameBuffer->guestXRes = 480;
	frameBuffer->guestYRes = 640;
	frameBuffer->windowWidth = 0;
	frameBuffer->windowHeight = 0;
	setupOrigins_v6_1(frameBuffer, 0);
	fbAddRef_v6_1(frameBuffer);
# ifdef WIN32
	HRESULT rc = LoadTypeInfo(&IID_IFramebuffer, &frameBuffer->infoIFrameBuffer);
	if (FAILED(rc) || !frameBuffer->infoIFrameBuffer) {
		return NULL;
	}
# endif /* WIN32 */
	return frameBuffer;
}

#ifdef WIN32
static HRESULT LoadTypeInfo(REFIID riid, ITypeInfo **pTInfo)
{
	HRESULT rc;
	ITypeLib *pTypeLib;
	rc = LoadRegTypeLib(&LIBID_VirtualBox, 1 /* major */, 0 /* minor */, 0 /* lcid */, &pTypeLib);
	if (FAILED(rc))
		return rc;
	rc = ITypeLib_GetTypeInfoOfGuid(pTypeLib, riid, pTInfo);

	/* No longer need access to the type lib, release it. */
	ITypeLib_Release(pTypeLib);

	return rc;
}

HRESULT fbGetTypeInfoCount(VBoxFramebuffer *framebuffer, ES_PRUint32 *count) {
	UNUSED(framebuffer);
	if (!count) {
		return E_POINTER;
	}
	*count = 1;
	return S_OK;
}

HRESULT fbGetTypeInfo(VBoxFramebuffer *framebuffer, ES_PRUint32 iTInfo, LCID lcid, ITypeInfo **ppTInfo) {
	UNUSED(iTInfo);
	UNUSED(lcid);
	if (!ppTInfo) {
		return E_POINTER;
	}
	ITypeInfo_AddRef(framebuffer->infoIFrameBuffer);
	*ppTInfo = framebuffer->infoIFrameBuffer;
	return S_OK;
}

HRESULT fbGetIDsOfNames(VBoxFramebuffer *framebuffer, REFIID riid, LPOLESTR *rgszNames, UINT cNames,
	LCID lcid, DISPID *rgDispId) {
	UNUSED(riid);
	UNUSED(lcid);
	return ITypeInfo_GetIDsOfNames(framebuffer->infoIFrameBuffer, rgszNames, cNames, rgDispId);
}

HRESULT fbInvoke(VBoxFramebuffer *framebuffer, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
	DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr) {
	UNUSED(riid);
	UNUSED(lcid);
	return ITypeInfo_Invoke(framebuffer->infoIFrameBuffer, (IDispatch *)framebuffer,
		dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}
#endif

/*!
* \brief Sets up the frambuffer origin X and Y values.
* Origins values are retrieved using the IDisplay_GetScreenResolution() function.
* \param framebuffer VBoxFramebuffer instance pointer.
* \param screenId VBox screen id.
*/
void setupOrigins_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 screenId)
{
	ULONG dummy;
	LONG xOrigin, yOrigin;
	GuestMonitorStatus_T monitorStatus;
	IDisplay_GetScreenResolution(framebuffer->vboxDisplay, screenId, &dummy, &dummy, &dummy,
		&xOrigin, &yOrigin, &monitorStatus);
	framebuffer->originX = xOrigin;
	framebuffer->originY = yOrigin;
}

#ifdef WIN32
ES_HRESULT fbQueryInterface_v6_1(VBoxFramebuffer *framebuffer, const IID *iid, void **resultp)
{
	printf("fbQueryInterface_v6_1\n");
	if (!memcmp(iid, &IID_IFramebuffer, sizeof(IID))
		|| !memcmp(iid, &IID_IDispatch, sizeof(IID))
		|| !memcmp(iid, &IID_IUnknown, sizeof(IID))) {
		fbAddRef_v6_1(framebuffer);
		*resultp = (void *)framebuffer;
		return S_OK;
	}
	return E_NOINTERFACE;
}
#else
ES_HRESULT fbQueryInterface_v6_1(VBoxFramebuffer *framebuffer, const nsID *iid, void **resultp)
{
	printf("fbQueryInterface_v6_1\n");
	if (!resultp)
		return NS_ERROR_NULL_POINTER;
	*resultp = NULL;
	nsID framebufferIID = IFRAMEBUFFER_IID;
	if (memcmp(iid, &framebufferIID, sizeof(IID_IFramebuffer)))
		*resultp = (void *)framebuffer;
	if (!*resultp)
		return NS_ERROR_NO_INTERFACE;
	fbAddRef_v6_1(framebuffer);
	return NS_OK;
}
#endif

ES_HRESULT fbAddRef_v6_1(VBoxFramebuffer *framebuffer)
{
	printf("fbAddRef_v6_1\n");
	return ++framebuffer->refCount;
}

ES_HRESULT fbRelease_v6_1(VBoxFramebuffer *framebuffer)
{
	printf("fbRelease_v6_1\n");
	if (--framebuffer->refCount == 0) {
		free(framebuffer);
		return 0;
	}
	return framebuffer->refCount;
}

ES_HRESULT fbGetOverlay_v6_1(VBoxFramebuffer *framebuffer, IFramebufferOverlay **overlay)
{
	printf("fbGetOverlay_v6_1\n");
	UNUSED(framebuffer);
	UNUSED(overlay);
	return S_OK;
}

ES_HRESULT fbGetCapabilities_v6_1(VBoxFramebuffer *framebuffer, ComSafeArrayOut(ES_PRUint32, capabilities))
{
	printf("fbGetCapabilities_v6_1\n");
	UNUSED(framebuffer);
	static const FramebufferCapabilities_T caps[] = {
		FramebufferCapabilities_UpdateImage,
		FramebufferCapabilities_RenderCursor,
		FramebufferCapabilities_MoveCursor
	};

	SAFEARRAY *aCapabilities;
	aCapabilities = g_pVBoxFuncs->pfnSafeArrayCreateVector(VT_I4, 0, sizeof(caps) / sizeof(caps[0]));
	g_pVBoxFuncs->pfnSafeArrayCopyInParamHelper(aCapabilities, caps, sizeof(caps));

#ifdef WIN32
	*capabilities = aCapabilities;
#else
	*capabilitiesSize = aCapabilities->c;
	*capabilities = aCapabilities->pv;
#endif
	return S_OK;
}

#ifdef WIN32
ES_HRESULT fbNotifyUpdateImage_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 x, ES_PRUint32 y, ES_PRUint32 width,
	ES_PRUint32 height, SAFEARRAY* image) {
	printf("fbNotifyUpdateImage_v6_1\n");
	g_pVBoxFuncs->pfnSafeArrayDestroy(image);
	//framebuffer->handleImage(framebuffer->context, x, y, width, height, imageSize, image);
	return S_OK;
}
#else
ES_HRESULT fbNotifyUpdateImage_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 x, ES_PRUint32 y, ES_PRUint32 width,
	ES_PRUint32 height, ES_PRUint32 imageSize, ES_PRUint8 *image)
{
	//framebuffer->handleImage(framebuffer->context, x, y, width, height, imageSize, image);
	return S_OK;
}
#endif

ES_HRESULT fbNotifyChange_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 screenId, ES_PRUint32 xOrigin,
	ES_PRUint32 yOrigin, ES_PRUint32 width, ES_PRUint32 height)
{
	printf("fbNotifyChange_v6_1\n");
	UNUSED(xOrigin);
	UNUSED(yOrigin);
	framebuffer->guestXRes = width;
	framebuffer->guestYRes = height;
	setupOrigins_v6_1(framebuffer, screenId);
	IDisplay_InvalidateAndUpdateScreen(framebuffer->vboxDisplay, screenId);
	return S_OK;
}

ES_HRESULT fbGetWidth_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *width)
{
	if (!width) {
		return E_INVALIDARG;
	}
	*width = framebuffer->windowWidth;
	return S_OK;
}

ES_HRESULT fbGetHeight_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *height)
{
	if (!height) {
		return E_INVALIDARG;
	}
	*height = framebuffer->windowHeight;
	return S_OK;
}

ES_HRESULT fbGetBitsPerPixel_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *bitsPerPixel)
{
	if (!bitsPerPixel) {
		return E_INVALIDARG;
	}
	*bitsPerPixel = 32;
	return S_OK;
}

ES_HRESULT fbGetBytesPerLine_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *bytesPerLine)
{
	if (!bytesPerLine) {
		return E_INVALIDARG;
	}
	*bytesPerLine = framebuffer->windowWidth * 4;
	return S_OK;
}

ES_HRESULT fbGetPixelFormat_v6_1(VBoxFramebuffer *framebuffer, ES_PRUint32 *pixelFormat)
{
	if (!pixelFormat) {
		return E_INVALIDARG;
	}
	*pixelFormat = BitmapFormat_BGR;
	return S_OK;
}
