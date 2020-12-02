#include "types.h"

ES_HRESULT fbGetWidth(VBoxEmptyFb *framebuffer, ES_PRUint32 *width);
ES_HRESULT fbGetHeight(VBoxEmptyFb *framebuffer, ES_PRUint32 *height);
ES_HRESULT fbGetBitsPerPixel(VBoxEmptyFb *framebuffer, ES_PRUint32 *bitsPerPixel);
ES_HRESULT fbGetBytesPerLine(VBoxEmptyFb *framebuffer, ES_PRUint32 *bytesPerLine);
ES_HRESULT fbGetPixelFormat(VBoxEmptyFb *framebuffer, ES_PRUint32 *pixelFormat);
ES_HRESULT fbGetHeightReduction(VBoxEmptyFb *framebuffer, ES_PRUint32 *heightReduction);
ES_HRESULT fbGetWinId(VBoxEmptyFb *framebuffer, ES_PRInt64 *winId);
ES_HRESULT fbNotifyUpdate(VBoxEmptyFb *framebuffer, ES_PRUint32 x, ES_PRUint32 y, ES_PRUint32 width,
	ES_PRUint32 height);
ES_HRESULT fbVideoModeSupported(VBoxEmptyFb *framebuffer, ES_PRUint32 width, ES_PRUint32 height,
	ES_PRUint32 bpp, ES_PRBool *supported);
ES_HRESULT fbGetVisibleRegion(VBoxEmptyFb *framebuffer, ES_PRUint8 *rectangles, ES_PRUint32 count,
	ES_PRUint32 *countCopied);
ES_HRESULT fbSetVisibleRegion(VBoxEmptyFb *framebuffer, ES_PRUint8 *rectangles, ES_PRUint32 count);
ES_HRESULT fbProcessVHWACommand(VBoxEmptyFb *framebuffer, ES_PRUint8 *command, ES_PRUint32 enmCmd,
	ES_PRBool fromGuest);
ES_HRESULT fbNotify3DEvent(VBoxEmptyFb *framebuffer, ES_PRUint32 type, ES_PRUint32 dataSize, ES_PRUint8 *data);

