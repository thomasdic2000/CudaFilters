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

#ifndef IDENTITYFILTER_H_
#define IDENTITYFILTER_H_

#include "common.h"
#include "SingleImageFilter.h"

/**
	\file IdentityFilter.h
	IdentityFilter s�n�f�n�n tan�m�n� i�erir.
*/

/**
	Bu s�n�f SingleImageFilter s�n�f�n� bo� ger�ekleyerek g�r�nt�de hi� bir de�i�iklik yapmaz.
*/

class IdentityFilter : public SingleImageFilter
{
public:
	IdentityFilter()
	{
	}

	/** G�r�nt�de de�i�iklik yapmadan ��kar. */
	virtual void FilterImage(char* imageData)
	{
		return; // imaj� de�i�tirmeden d�n.
	}

private:
	DISALLOW_COPY_AND_ASSIGN(IdentityFilter);
};

#endif // IDENTITYFILTER_H_