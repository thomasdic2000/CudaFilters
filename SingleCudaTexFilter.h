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

#ifndef SINGLECUDATEXFILTER_H_
#define SINGLECUDATEXFILTER_H_

/** 
	\file SingleCudaTexFilter.h
	SingleCudaTexFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "cudaCommon.h"

#include "SingleCudaFilter.h"

/**
	CUDA ve texture kullanarak GPU �zerinde g�r�nt� filtrelemek i�in kullan�lan s�n�f.
	
	SingleCudaTexFilter s�n�f�n�n g�revi, SingleCudaFilter s�n�f�na ek olarak CUDA �zerinde texture kullanan kernelleri �a��rabilmek i�in texture y�klemesi ve texture y�netimi yapmakt�r.
*/

class SingleCudaTexFilter : public SingleCudaFilter
{

private:
	cudaArray* cu_array;
	cudaChannelFormatDesc channelDesc;
	const char* textureSymbolName;

	const textureReference* constTexRefPtr;
	textureReference* texRefPtr;

	DISALLOW_COPY_AND_ASSIGN(SingleCudaTexFilter);

public:
	
	/**
		kernelLauncher ve texture ad�n� alan SingleCudaTexFilter yarat�c�s�.

		\param kernelLauncher Kerneli �a��rmak i�in kullan�lan metod i�aret�isi.
		\param textureSymbolName Kernelde kullan�lan texture'�n sembol ad�.
		
		ptKernelLauncher tipinde metod i�aret�isi ve texture sembol�n�n kerneldeki ad�n� alan SingleCudaTexFilter yarat�c�s�.
	*/
	explicit SingleCudaTexFilter( ptKernelLauncher kernelLauncher, const char* textureSymbolName )
		: SingleCudaFilter(kernelLauncher), 
		textureSymbolName(textureSymbolName),
		constTexRefPtr(NULL),
		texRefPtr(NULL)
	{
	}

	virtual void InitFilter(int width, int height, int rowStride);
	virtual void FilterImage(char* imageData);
	virtual void ReleaseFilter();
};

#endif SINGLECUDATEXFILTER_H_