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

#ifndef SINGLECUDAFILTER_H_
#define SINGLECUDAFILTER_H_

/** 
	\file SingleCudaFilter.h
	SingleCudaFilter s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include "common.h"

#include "cudaCommon.h"

#include "SingleImageFilter.h"

/** G�r�nt� i�leme kernellerinin ihtiyac� olan g�r�nt�n�n GPU �zerindeki adresi, piksel geni�li�i ve piksel y�ksekli�ini parametre olarak alan metod i�aret�isi. */
typedef void (*ptKernelLauncher)(float*, int, int);

inline
unsigned char satchar(float val);

/**
	CUDA kullanarak GPU �zerinde g�r�nt� filtrelemek i�in kullan�lan s�n�f.
	
	SingleCudaFilter s�n�f�n�n g�revi, FilterImage metoduna g�nderilen g�r�nt�y� normalize ederek GPU belle�ine aktarmak ve bu belle�i y�netmektir.
*/

class SingleCudaFilter : public SingleImageFilter
{
protected:
	float* h_Image; /**< Normalize edilmi� g�r�nt�n�n CPU bellek adresi. */
	float* d_Image; /**< Normalize edilmi� g�r�nt�n�n GPU bellek adresi. */

	ptKernelLauncher kernelLauncher;

	DISALLOW_COPY_AND_ASSIGN(SingleCudaFilter);

public:

	/**
		kernelLauncher metod i�aret�isini alan yarat�c�.

		\param kernelLauncher \ref kernelLauncher tipinde metod i�aret�isi alan yarat�c�.
	*/
	explicit SingleCudaFilter( ptKernelLauncher kernelLauncher )
		: kernelLauncher(kernelLauncher)
	{
	}

	/**
		CPU ve GPU �zerinde normalize edilmi� g�r�nt�ler i�in bellek ay�r�r.
	*/
	virtual void InitFilter(int width, int height, int rowStride)
	{
		SingleImageFilter::InitFilter(width, height, rowStride);

		/*
		allocate device memory
		*/

		cudaMalloc( (void**) &d_Image, 3 * sizeof(float) * width * height );
		checkCUDAError("malloc device image");


		/*
		allocate host memory
		*/

		cudaMallocHost( (void**) &h_Image, 3 * sizeof(float) * width * height );
		checkCUDAError("malloc host image");
	}

	/**
		Yarat�c�da al�nan kerneli �a��r�r.

		\param imageData G�r�nt�n�n BGR kanal s�ral� bellekteki adresi.


		G�r�nt�y� normalize ederek kernelLauncher i�aret�isinin g�sterdi�i metodu �a��r�r ard�ndan g�r�nt�y� denormalize eder( [0, 255] aral���na ).
		Kernelde i�lenen g�r�nt�den sonu� olarak [0, 1] aral��� d���nda bir de�er d�nerse o kanal�n de�eri [0, 255] aral���ndan d��ar�da olabilir. Bu durumda de�er yak�n oldu�u s�n�ra indirgenir.
	*/
	virtual void FilterImage(char* imageData)
	{
		// imageData de�i�kenindeki g�r�nt� verisi normalize edilerek h_Image de�i�kenine aktar�l�r.
		for(int i=0; i<3*width*height; i++)
		{
			*(h_Image + i) = (unsigned char)*(imageData + i) / 255.0f; // normalize and copy image
		}

		/*
			G�r�nt� GPU belle�ine kopyalan�r.
		*/

		cudaMemcpy( d_Image, h_Image, 3 * sizeof(float) * width * height, cudaMemcpyHostToDevice );
		checkCUDAError("FilterImage: memcpy");

		/*
			Constructorda verilen kernel �al��t�r�l�r.
		*/
		kernelLauncher( d_Image, width, height );
	
		/*
			Sonu�lar CPU belle�ine kopyalan�r.
		*/
		cudaMemcpy( h_Image, d_Image, 3 * sizeof(float) * width * height, cudaMemcpyDeviceToHost);
		checkCUDAError("FilterImage: memcpy2");

		/*
			h_Image de�i�kenindeki normalize edilmi� g�r�nt� verisi [0, 255] aral���na �ekilir.
		*/
		for(int i=0; i<3*width*height; i++)
		{
			*(imageData + i) = satchar(*(h_Image + i) * 255);
		}
	}

	/**
		CPU ve GPU �zerinde normalize edilmi� g�r�nt�ler i�in ayr�lm�� belle�i serbest b�rak�r.
	*/
	virtual void ReleaseFilter()
	{
		if( this->isReleased )
			return;

		SingleImageFilter::ReleaseFilter();

		cudaFree( d_Image );
		checkCUDAError("free device image");
	
		cudaFreeHost( h_Image );
		checkCUDAError("free host image");
	}

};

/**
	val parametresini [0, 255] aral���na indirger.

	\param val �ndirgenecek parametre.
*/
inline
unsigned char satchar(float val)
{
	if(val<=0)
		return (unsigned char)0;
	if(val>=255)
		return (unsigned char)255;

	return (unsigned char)val;
}


#endif // SINGLECUDAFILTER_H_