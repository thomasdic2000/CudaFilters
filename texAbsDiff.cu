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

#ifndef TEX_INVERT_CU
#define TEX_INVERT_CU

/**
	\file texAbsDiff.cu
	CUDA texture absolute difference kernelinin launcher metodunu ve kernelini tan�mlar.
*/

#include "texAbsDiff.h"

texture<float4, 2, cudaReadModeElementType> texAbsDiff1; /**< Kernelde kullan�lan texture sembol�. */

#define BLOCK_SIZE_X (32) /**< Yatay blok boyutu */
#define BLOCK_SIZE_Y (32) /**< D��ey blok boyutu */

/** GPU zaman�n� �l�mek i�in 1 yap�n�z. */
#define ENABLE_TIMING_CODE 1


/**
	Mutlak de�er metodu.

	\param a Mutlak de�eri al�nacak float4 de�eri.

	a parametresinin her bir eleman�n�n mutlak de�erini alarak yeni bir float4 d�nd�r�r.
*/
inline __host__ __device__ float4 abs( float4 a )
{	
	return make_float4( fabsf( a.x ), fabsf( a.y ), fabsf( a.z ), fabsf( a.w ) );
}

/**	
	Texture kullanarak g�r�nt�n�n kom�u pikseller ile mutlak fark�n� alan kernel.

	\param image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	
	Metod GPU �zerinde �al���r, ��kt�s�n� image parametresinin �zerine yazar.

	*/
__global__
void gpuTexAbsDiff(
	float* image,
	int width,
	int height
	)
{
	// threade ait sat�r ve s�tunu hesapla.
	int row = blockIdx.y * BLOCK_SIZE_Y + threadIdx.y;
	int col = blockIdx.x * BLOCK_SIZE_X + threadIdx.x;

	// global memorydeki imaj i�in indisi hesapla.
	int cIdx = ( row * width + col ) * 3; // 3 ile �arp�m RGB i�in, linearIndex.

	float tw = 1.0f / width; // Texture kordinatlar�nda 1 pixel geni�lik.
	float th = 1.0f / height; // Texture kordinatlar�nda 1 pixel y�kseklik.

	// merkez piksel kordinat�n normalize texel kordinatlar�n� hesapla.
	float tu = ( float )col * tw;
	float tv = ( float )row * th;

	/*tw *= 4;
	th *= 4;*/
	
	// row, col etraf�ndaki 4 ana y�ndeki texelden farklar�n� al.
	float4 texVal1 = tex2D( texAbsDiff1, tu, tv ) - tex2D( texAbsDiff1, tu + tw, tv + th );
	float4 texVal2 = tex2D( texAbsDiff1, tu, tv ) - tex2D( texAbsDiff1, tu - tw, tv - th );
	float4 texVal3 = tex2D( texAbsDiff1, tu, tv ) - tex2D( texAbsDiff1, tu + tw, tv - th );
	float4 texVal4 = tex2D( texAbsDiff1, tu, tv ) - tex2D( texAbsDiff1, tu - tw, tv + th );

	// 4 ana y�ndeki farklar�n mutlak de�erlerinin ortalamas�n� al.
	float4 texVal = 0.25f * ( abs( texVal1 ) + abs( texVal2 ) + abs( texVal3 ) + abs( texVal4 ) );

	// global memorydeki imaja hesaplanan de�erleri aktar.
	*( image + cIdx )     = texVal.x;
	*( image + cIdx + 1 ) = texVal.y;
	*( image + cIdx + 2 ) = texVal.z;
}

/**
	\ref ptKernelLauncher tipinde metod.

	\param d_Image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	\ref gpuTexAbsDiff kernelini Grid ve Block boyutlar�n� ayarlayarak �a��ran metod.
*/
void deviceTexAbsDiffLaunch(
	float *d_Image,
	int width,
	int height
	)
{
	 // launch kernel
	dim3 dimBlock( BLOCK_SIZE_X, BLOCK_SIZE_Y );
    dim3 dimGrid( width / dimBlock.x, height / dimBlock.y );

#if ENABLE_TIMING_CODE

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

#endif

    gpuTexAbsDiff<<< dimGrid, dimBlock >>>( d_Image, width, height);

#if ENABLE_TIMING_CODE
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);

    // block until the device has completed
    cudaThreadSynchronize();
	
	printf("gpuTexAbsDiff kernel time: %.3f ms\n", elapsedTime);
#endif

	cudaThreadSynchronize();

    // check if kernel execution generated an error
    // Check for any CUDA errors
    checkCUDAError("kernel invocation");
}


#endif