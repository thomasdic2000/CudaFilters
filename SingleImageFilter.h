// Copyright (c) 2011 Kerem KAT 
// 
// http://dissipatedheat.com/
// Do not hesisate to contact me about usage of the code or to make comments 
// about the code. Your feedback will be appreciated.
// keremkat<@>gmail<.>com
//
// Kodun kullan�m� hakk�nda veya yorum yapmak i�in benimle ileti�im kurmaktan
// �ekinmeyiniz. Geri bildirimleriniz de�erlendirilecektir.
// keremkat<@>gmail<.>com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to 
// deal in the Software without restriction, including without limitation the 
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
// sell copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#ifndef SINGLEIMAGEFILTER_H_
#define SINGLEIMAGEFILTER_H_

/** 
	\file SingleImageFilter.h
	SingleImageFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "ISingleImageFilter.h"

/**
	ISingleImageFilter aray�z�n� FilterImage metodu hari� ger�ekleyen abstract s�n�f.
*/
class SingleImageFilter : public ISingleImageFilter
{
private:
	DISALLOW_COPY_AND_ASSIGN(SingleImageFilter);
	
protected:
	bool isInited;
	bool isReleased;
	int height;
	int width;
	int rowStride; // byte width of a single row.

public:

	virtual ~SingleImageFilter()
	{
	}

	SingleImageFilter(void)
		: isInited(false), 
		isReleased(false), 
		height(0), 
		width(0)
	{
		
	}

	virtual void InitFilter(int width, int height, int rowStride)
	{
		this->width = width;
		this->height = height;
		this->rowStride = rowStride;
		this->isInited = true;
	}

	virtual void ReleaseFilter()
	{
		this->isReleased = true;
	}
};

#endif SINGLEIMAGEFILTER_H_