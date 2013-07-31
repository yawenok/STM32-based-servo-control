#ifndef _USE_QUEUE_H_
#define _USE_QUEUE_H_
#include "TypeAndMacro.h"
#ifndef MAX_SIZE
 #define MAX_SIZE 1024
#endif

typedef struct tagDataBuf
{
	
	int  BufLength;
	int  BufHead;
	int  Buftail;
	int  Datasize;
	BYTE DataBuf[ MAX_SIZE ];

} DATABUF,*pDATABUF;



extern BOOL QueueInit(DATABUF* pDataBuf,INT16 size);
extern BOOL QueueAdd(DATABUF* pDataBuf,UINT8 data);
extern BOOL QueueDel(DATABUF* pDataBuf,INT16 DelNum);
extern BYTE QueueGet(DATABUF* pDataBuf,INT16 place);
extern int  GetSize (DATABUF* DataBuf);


#endif



