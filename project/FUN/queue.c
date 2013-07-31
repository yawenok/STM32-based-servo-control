#include "STD.h"
#include "queue.h"



BOOL QueueInit(DATABUF *pDataBuf ,INT16 size) 
{
    int i = 0;
	pDataBuf->BufHead = 0;
	pDataBuf->BufLength = size;
	pDataBuf->Buftail = 0;
	pDataBuf->Datasize = 0;
	for(i = 0;i< pDataBuf->BufLength;i++)
	 ( pDataBuf->DataBuf )[i] = 0;
	return TRUE;
}
BOOL QueueAdd(DATABUF* pDataBuf,UINT8 data)
{
    if(pDataBuf->BufLength == pDataBuf->Datasize)
    {
     return FALSE ;
    }
	(pDataBuf->DataBuf )[pDataBuf->Buftail] = data;	
	pDataBuf->Buftail = (pDataBuf->Buftail + 1) % pDataBuf->BufLength;
	pDataBuf->Datasize ++;
	return TRUE;
}
BOOL QueueDel(DATABUF* pDataBuf ,INT16 DelNum)
{
  if( pDataBuf->Datasize >= DelNum)
  {
    pDataBuf->BufHead = (pDataBuf->BufHead + DelNum ) % pDataBuf->BufLength ;
	pDataBuf->Datasize -= DelNum ;
	return TRUE ;
  }
  return FALSE ;
}

BYTE QueueGet(DATABUF* pDataBuf,INT16 place)
{
	if(pDataBuf->Datasize > place)
	{
	  place = ( pDataBuf->BufHead + place ) % pDataBuf->BufLength;
	  return ( pDataBuf->DataBuf )[place];
	}
	return FALSE;	
}
int GetSize(DATABUF* pDataBuf)
{
	return pDataBuf->Datasize;
}



