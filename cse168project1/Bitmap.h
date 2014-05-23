////////////////////////////////////////
// Bitmap.h
////////////////////////////////////////

#ifndef CSE168_BITMAP_H
#define CSE168_BITMAP_H

#include "Core.h"

class Camera;

////////////////////////////////////////////////////////////////////////////////

class Bitmap {
    friend Camera;
    
public:
	Bitmap(int x,int y)						{XRes=x; YRes=y; Pixel=new int[XRes*YRes]{0};}
	~Bitmap()								{delete []Pixel;}

	bool SaveBMP(const char *filename);

	int GetXRes() const						{return XRes;}
	int GetYRes() const						{return YRes;}
	int &GetPixel(int x,int y)				{return Pixel[y*XRes+x];}
	void SetPixel(int x,int y,int pix)		{Pixel[y*XRes+x]=pix;}

private:
	int XRes;
	int YRes;
	int *Pixel;
};

////////////////////////////////////////////////////////////////////////////////

#endif
