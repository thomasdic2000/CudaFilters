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

#ifndef CUDATEXBOXBLURFILTER_H_
#define CUDATEXBOXBLURFILTER_H_

/** 
	\file CudaTexBoxBlurFilter.h
	CudaTexBoxBlurFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "SingleCudaTexFilter.h"

#include "texBoxBlur.h" // kernel definition

/**
	CUDA ve texture kullanarak GPU �zerinde g�r�nt�y� buland�ran filtre s�n�f�.
*/

class CudaTexBoxBlurFilter : public SingleCudaTexFilter
{

public:

	/**
		\ref deviceTexBoxBlurLaunch metod i�aret�isi ve "texBlur1" sembol ad� parametresi ile SingleCudaTexFilter yarat�c�s�n� �a��r�r.
	*/
	CudaTexBoxBlurFilter()
		: SingleCudaTexFilter(deviceTexBoxBlurLaunch, "texBlur1")
	{
	}

private:

	DISALLOW_COPY_AND_ASSIGN(CudaTexBoxBlurFilter);

};

#endif // CUDATEXBOXBLURFILTER_H_