#include "framebuffer.h"
#include "framebuffer_6_1.h"
#include <stdio.h>

ES_HRESULT fbGetWidth(VBoxEmptyFb *framebuffer, ES_PRUint32 *width)
{
	printf("fbGetWidth\n");
	UNUSED(framebuffer);
	if (!width) {
		printf("E_INVALIDARG\n");
		return E_INVALIDARG;
	}
	*width = 0;
	return 0;
}

ES_HRESULT fbGetHeight(VBoxEmptyFb *framebuffer, ES_PRUint32 *height)
{
	printf("fbGetHeight\n");
	UNUSED(framebuffer);
	if (!height) {
		printf("E_INVALIDARG\n");
		return E_INVALIDARG;
	}
	*height = 0;
	return 0;
}

ES_HRESULT fbGetBitsPerPixel(VBoxEmptyFb *framebuffer, ES_PRUint32 *bitsPerPixel)
{
	UNUSED(framebuffer);
	if (!bitsPerPixel) {
		return E_INVALIDARG;
	}
	*bitsPerPixel = 32;
	return 0;
}

ES_HRESULT fbGetBytesPerLine(VBoxEmptyFb *framebuffer, ES_PRUint32 *bytesPerLine)
{
	UNUSED(framebuffer);
	if (!bytesPerLine) {
		return E_INVALIDARG;
	}
	*bytesPerLine = 0;
	return 0;
}

ES_HRESULT fbGetPixelFormat(VBoxEmptyFb *framebuffer, ES_PRUint32 *pixelFormat)
{
	UNUSED(framebuffer);
	if (!pixelFormat) {
		return E_INVALIDARG;
	}
	*pixelFormat = BitmapFormat_BGR;
	return 0;
}

ES_HRESULT fbGetHeightReduction(VBoxEmptyFb *framebuffer, ES_PRUint32 *heightReduction)
{
	UNUSED(framebuffer);
	UNUSED(heightReduction);
	return 0;
}

ES_HRESULT fbGetWinId(VBoxEmptyFb *framebuffer, ES_PRInt64 *winId)
{
	UNUSED(framebuffer);
	UNUSED(winId);
	return 0;
}

ES_HRESULT fbNotifyUpdate(VBoxEmptyFb *framebuffer, ES_PRUint32 x, ES_PRUint32 y, ES_PRUint32 width,
	ES_PRUint32 height)
{
	printf("fbNotifyUpdate\n");
	UNUSED(framebuffer);
	UNUSED(x);
	UNUSED(y);
	UNUSED(width);
	UNUSED(height);
	return 0;
}

ES_HRESULT fbVideoModeSupported(VBoxEmptyFb *framebuffer, ES_PRUint32 width, ES_PRUint32 height,
	ES_PRUint32 bpp, ES_PRBool *supported)
{
	UNUSED(framebuffer);
	UNUSED(width);
	UNUSED(height);
	UNUSED(bpp);
	UNUSED(supported);
	return 0;
}


ES_HRESULT fbGetVisibleRegion(VBoxEmptyFb *framebuffer, ES_PRUint8 *rectangles, ES_PRUint32 count,
	ES_PRUint32 *countCopied)
{
	UNUSED(framebuffer);
	UNUSED(rectangles);
	UNUSED(count);
	UNUSED(countCopied);
	return 0;
}

ES_HRESULT fbSetVisibleRegion(VBoxEmptyFb *framebuffer, ES_PRUint8 *rectangles, ES_PRUint32 count)
{
	UNUSED(framebuffer);
	UNUSED(rectangles);
	UNUSED(count);
	return 0;
}

ES_HRESULT fbProcessVHWACommand(VBoxEmptyFb *framebuffer, ES_PRUint8 *command, ES_PRUint32 enmCmd,
	ES_PRBool fromGuest)
{
	UNUSED(framebuffer);
	UNUSED(command);
	UNUSED(enmCmd);
	UNUSED(fromGuest);
	return 0;
}

ES_HRESULT fbNotify3DEvent(VBoxEmptyFb *framebuffer, ES_PRUint32 type, ES_PRUint32 dataSize, ES_PRUint8 *data)
{
	UNUSED(framebuffer);
	UNUSED(type);
	UNUSED(dataSize);
	UNUSED(data);
	return 0;
}
