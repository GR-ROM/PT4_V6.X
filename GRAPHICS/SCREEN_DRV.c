/***************************************************************
 * SCREEN_DRV.c
 * 
 * 
 * Created on 18 Ноябрь 2015 г.
 ***************************************************************/
#include "Graphics.h"
#include "SCREEN_DRV.h"
#include "UC1601_DRV.h"
//#define ScrnBufSize  (SCREEN_HOR_SIZE * SCREEN_VER_SIZE)/8
//UINT8	ScrenBuf[ScrnBufSize];
UINT8	ScrenBuf[ScrnBufSize];
// Color
BYTE    _color;
// Clipping region control
SHORT _clipRgn;
// Clipping region borders
SHORT _clipLeft;
SHORT _clipTop;
SHORT _clipRight;
SHORT _clipBottom;

/////////////////////// LOCAL FUNCTIONS PROTOTYPES ////////////////////////////

void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch);
void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch);

/*********************************************************************
* Function:  void  DelayMs(WORD time)
* PreCondition: none
* Input: time - delay in ms
* Output: none
* Side Effects: none
* Overview: delays execution on time specified in ms
* Note: delay is defined for 16MIPS
********************************************************************/
#define DELAY_1MS 16000/9
void  DelayMs(WORD time){
unsigned delay;
	while(time--)
		for(delay=0; delay<DELAY_1MS; delay++);	
}
 
/*********************************************************************
* Function:  void ResetDevice()
* PreCondition: none
* Input: none
* Output: none
* Side Effects: none
* Overview: resets LCD, initializes PMP
* Note: none
********************************************************************/
void ResetDevice(void){
	Uc1601_Initialise();
}

/*********************************************************************
* Function: void PutPixel(SHORT x, SHORT y)
* PreCondition: none
* Input: x,y - pixel coordinates
* Output: none
* Side Effects: none
* Overview: puts pixel
* Note: none
********************************************************************/
void PutPixel(SHORT x, SHORT y){
	UINT8 *pSCRN;

	
	// check if point is in clipping region
    if(_clipRgn){
        if(x<_clipLeft)
            return;
        if(x>_clipRight)
            return;
        if(y<_clipTop)
            return;
        if(y>_clipBottom)
            return;
    }
	pSCRN=(UINT8 *)ScrenBuf;  //[SCREEN_HOR_SIZE*(y>>3)+x];
    pSCRN+=SCREEN_HOR_SIZE*(y>>3)+x;
		if(_color>0){
			*pSCRN|=1<<(y&7);
		}
		else {
			*pSCRN&=~(1<<(y&7));
		}
}

/*********************************************************************
* Function: BYTE GetPixel(SHORT x, SHORT y)
* PreCondition: none
* Input: x,y - pixel coordinates 
* Output: pixel color
* Side Effects: none
* Overview: return pixel color at x,y position
* Note: none
********************************************************************/
BYTE GetPixel(SHORT x, SHORT y){
	UINT8 *pSCRN;
	// check if point is in clipping region
    if(_clipRgn){
        if(x<_clipLeft)
            return 0;
        if(x>_clipRight)
            return 0;
        if(y<_clipTop)
            return 0;
        if(y>_clipBottom)
            return 0;
    }
	pSCRN=(UINT8 *)ScrenBuf;  //[SCREEN_HOR_SIZE*(y>>3)+x];
    pSCRN+=SCREEN_HOR_SIZE*(y>>3)+x;
	return (*pSCRN & (1<<(y&7)));
}

/*********************************************************************
* Function: void ClearDevice(void)
* PreCondition: none
* Input: none
* Output: none
* Side Effects: none
* Overview: clears screen with current color 
* Note: none
********************************************************************/
void ClearDevice(void){
	UINT8 *pSCRN;
	UINT16 i;
	pSCRN=ScrenBuf;
	for(i=0;i<ScrnBufSize;i++){
		*pSCRN++=_color;
	}
	//Update_Screen();
}


/******************************************************************
 * Function: void BarXor(SHORT left, SHORT top, SHORT right, SHORT bottom)
 * Overview: Ёта функци€ инвертирует содержимое области
 *           left, top and right,bottom
 * Input: left - x position of the left top corner.
 *		 top - y position of the left top corner.
 *		 right - x position of the right bottom corner.
 *		 bottom - y position of the right bottom corner.
 * Output: none
 * 
 ******************************************************************/
void BarXor(SHORT left, SHORT top, SHORT right, SHORT bottom){
SHORT x,y;
BYTE Temp_color;
    Temp_color=_color;
    for(y=top; y<bottom+1; y++){
        for(x=left; x<right+1; x++){
            if(GetPixel(x,y)){
                _color=WHITE;
            } else {
                _color=BLACK;
            }
            PutPixel(x,y);
        }
    }
    _color=Temp_color;
}
/****************************************************************
 * void BarFill(SHORT left, SHORT top, SHORT right, SHORT bottom);
 *
 *
 ****************************************************************/
void BarFill(SHORT left, SHORT top, SHORT right, SHORT bottom){
SHORT x,y;
BYTE Temp_color;
    Temp_color=_color;
    _color=WHITE;
    for(y=top; y<bottom+1; y++){
        for(x=left; x<right+1; x++){
            PutPixel(x,y);
        }
    }
    _color=Temp_color;
}

/*********************************************************************
* Function: void PutImage(SHORT left, SHORT top, void* bitmap, BYTE stretch)
* PreCondition: none
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
* Output: none
* Side Effects: none
* Overview: outputs image starting from left,top coordinates
* Note: image must be located in flash
********************************************************************/

void PutImage(SHORT left, SHORT top, void* bitmap, BYTE stretch){
FLASH_BYTE* flashAddress;
BYTE colorTemp;

    //top = GetMaxY() - top; 

    // Save current color
    colorTemp = _color;

    switch(*((SHORT*)bitmap))
    {
#ifdef USE_BITMAP_FLASH
        case FLASH:
            // Image address
            flashAddress = ((BITMAP_FLASH*)bitmap)->address;
            PutImage1BPP(left, top, flashAddress, stretch);
            break;
#endif
#ifdef USE_BITMAP_EXTERNAL
        case EXTERNAL:
            // Get color depth
            ExternalMemoryCallback(bitmap, 1, 1, &colorDepth);
            // Draw picture
            PutImage1BPPExt(left, top, bitmap, stretch);
            break;
#endif
        default:
            break;
    }
	Update_Screen();
    // Restore current color
    _color = colorTemp;
}

#ifdef USE_BITMAP_FLASH
/*********************************************************************
* Function: void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
* PreCondition: none
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
* Output: none
* Side Effects: none
* Overview: outputs monochrome image starting from left,top coordinates
* Note: image must be located in flash
********************************************************************/
void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch){
register WORD_VAL address;
register FLASH_BYTE* flashAddress;

register BYTE pos, temp;

WORD sizeX, sizeY;
WORD x,y;
//BYTE stretchX,stretchY;
WORD pallete[2];

    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Set start address
    address.Val = (LINE_MEM_PITCH*left) + top;

    // Read image size
    sizeY = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    pallete[0] = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    pallete[1] = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;


	for (y=0; y<sizeY;y++) {
		for(x=0;x<sizeX;x+=8) {
	        temp = *flashAddress;
	        
			for(pos=x;pos<(8+x);pos++) {
				if (pos >= sizeX) {
					x = pos;
					break;
				}
				if ((temp&0x80) != 0)
	            	_color = 0;
	            else	
	            	_color = 1;
	            PutPixel(pos+left,y+top);
	            temp = temp << 1;	
	    	} 
	        flashAddress++;
		}
		//address.Val += 1; 
	}
}

#endif

#ifdef USE_BITMAP_EXTERNAL
/*********************************************************************
* Function: void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
* PreCondition: none
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
* Output: none
* Side Effects: none
* Overview: outputs monochrome image starting from left,top coordinates
* Note: image must be located in flash
********************************************************************/
void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch){
register DWORD_VAL  address;
register DWORD      memOffset;
BITMAP_HEADER       bmp;
WORD                pallete[2];
BYTE                lineBuffer[(SCREEN_HOR_SIZE/8)+1];
BYTE*               pData; 
SHORT               byteWidth;

BYTE                temp;
BYTE                mask;
WORD                sizeX, sizeY;
WORD                x,y;
BYTE                stretchX, stretchY;

    // Set start address
    address.Val = (long)LINE_MEM_PITCH*left+ top;

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (2 entries)
    ExternalMemoryCallback(bitmap, sizeof(BITMAP_HEADER), 2*sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 2*sizeof(WORD);

    // Line width in bytes
    byteWidth = bmp.width>>3;
    if(bmp.width&0x0007)
        byteWidth++;

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y=0; y<sizeY; y++){

        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;

        for(stretchY = 0; stretchY<stretch; stretchY++){
            pData = lineBuffer;
            SetAddress(address.v[2],address.v[1],address.v[0]);
            mask = 0;
            for(x=0; x<sizeX; x++){

                // Read 8 pixels from flash
                if(mask == 0){
                    temp = *pData++;
                    mask = 0x80;
                }
                
                // Set color
                if(mask&temp){
                    SetColor(pallete[1]);
                }else{
                    SetColor(pallete[0]);
                }

                // Write pixel to screen
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }

                // Shift to the next pixel
                mask >>= 1;
           }
           address.Val -= 1; 
        }
    }
}

#endif



