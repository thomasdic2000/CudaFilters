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

/** 
	\file FilterFactory.h
	CudaFilters projesindeki filtreler i�in factory metodlar�n� i�eren ba�l�k dosyas�.
*/

#ifndef FILTERFACTORY_H_
#define FILTERFACTORY_H_

#include "ISingleImageFilter.h"

#if defined(FILTERAPI_EXPORT)
#   define FILTERAPI   __declspec(dllexport)
#else
#   define FILTERAPI   __declspec(dllimport)
#endif

#define FILTERENTRY __stdcall

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCpuInvertFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCpuCCLFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCpuMovingAverageFilter( int framesToAverage );

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCudaInvertFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCudaSepiaFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCudaTexBoxBlurFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCudaTexInvertFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetCudaTileFlipFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetIdentityFilter();

extern "C" FILTERAPI ISingleImageFilter* FILTERENTRY GetThresholdFilter( unsigned char threshold );

extern "C" FILTERAPI void FILTERENTRY ReleaseCUDAThread();

#endif // FILTERFACTORY_H_