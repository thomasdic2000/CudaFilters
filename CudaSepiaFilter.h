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

#ifndef CUDASEPUAFILTER_H_
#define CUDASEPUAFILTER_H_

/** 
	\file CudaSepiaFilter.h
	CudaSepiaFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaFilter.h"

#include "sepia.h" // kernel definition.

/**
	CUDA kullanarak GPU �zerinde g�r�nt�n�n sepia tonlamas�n� d�nd�ren filtre s�n�f�.
*/

class CudaSepiaFilter : public SingleCudaFilter
{

public:

	/**
		\ref deviceSepiaLaunch metod i�aret�isi parametresi ile SingleCudaFilter yarat�c�s�n� �a��r�r.
	*/
	CudaSepiaFilter()
		: SingleCudaFilter(deviceSepiaLaunch)
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaSepiaFilter);

};

#endif // CUDASEPUAFILTER_H_