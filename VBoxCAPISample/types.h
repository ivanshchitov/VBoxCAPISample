#ifndef TYPES_H
#define TYPES_H

typedef int ES_PRBool;
typedef long ES_PRInt64;
typedef unsigned char ES_PRUint8;
typedef unsigned int ES_PRUint32;
#define ES_HRESULT ES_PRUint32

typedef void *VBoxClientHandle;
typedef void *VBoxManagerContext;
typedef struct { void *empty; } VBoxEmptyFb;

#define UNUSED(x) (void)(x)

#endif // TYPES_H
