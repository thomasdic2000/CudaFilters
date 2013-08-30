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

#include "tileFlip.h"

/**
	\file tileFlip.cu
	CUDA tile flip kernelinin launcher metodunu ve kernelini tan�mlar.
*/

/** Kernel 1 griddeki blok boyutu ( BLOCK_SIZE x BLOCK_SIZE kare bloklar ). */
#define BLOCK_SIZE (32)

/** GPU zaman�n� �l�mek i�in 1 yap�n�z. */
#define ENABLE_TIMING_CODE 1

/**	
	G�r�nt�y� blok blok �eviren kernel.

	\param image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	
	Metod GPU �zerinde �al���r, ��kt�s�n� image parametresinin �zerine yazar.

	*/__global__
void gpuTileFlip(
	float* image,
	int width,
	int height
	)
{
	int row = blockIdx.y * BLOCK_SIZE + threadIdx.y; // sat�r No.

	int col = blockIdx.x * BLOCK_SIZE + threadIdx.x; // s�tun No.

	int cIdx = ( row * width + col ) * 3; // 3 ile �arp�m RGB i�in, linearIndex.

	/*
	       *( image + linearIndex ): Blue, in [0, 1]
		   *( image + linearIndex + 1 ): Green, in [0, 1]
		   *( image + linearIndex + 2 ): Red, in [0, 1]
	*/

	__shared__ float smBlockB[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ float smBlockG[BLOCK_SIZE][BLOCK_SIZE];
	__shared__ float smBlockR[BLOCK_SIZE][BLOCK_SIZE];

	smBlockB[threadIdx.x][threadIdx.y] = image[ cIdx ];
	smBlockG[threadIdx.x][threadIdx.y] = image[ cIdx + 1 ];
	smBlockR[threadIdx.x][threadIdx.y] = image[ cIdx + 2 ];

	__syncthreads();	
	
	image[ cIdx ]     =	smBlockB[threadIdx.y][threadIdx.x];
	image[ cIdx + 1 ] = smBlockG[threadIdx.y][threadIdx.x];
	image[ cIdx + 2 ] = smBlockR[threadIdx.y][threadIdx.x];
		
	
	//image[ cIdxRight + 2 ] = 0;

	/**( image + cIdx ) = abs((*( image + cIdx ) - *( image + cIdxRight )));
	*( image + cIdx + 1 ) = abs((*( image + cIdx + 1 ) - *( image + cIdxRight + 1 )));
	*( image + cIdx + 2 ) = abs((*( image + cIdx + 2 ) - *( image + cIdxRight + 2 )));*/
}

/**
	\ref ptKernelLauncher tipinde metod.

	\param d_Image [0, 1] aral���na normalize edilmi�, BGR kanal s�ral� g�r�nt�n�n GPU belle�indeki adresi.
	\param width G�r�nt�n�n piksel olarak geni�li�i
	\param height G�r�nt�n�n piksel olarak y�ksekli�i

	\ref gpuTileFlip kernelini Grid ve Block boyutlar�n� ayarlayarak �a��ran metod.
*/
void deviceTileFlipLaunch(
	float *d_Image,
	int width,
	int height
	)
{
	 // launch kernel
	dim3 dimBlock( BLOCK_SIZE, BLOCK_SIZE );
    dim3 dimGrid( width / dimBlock.x, height / dimBlock.y );

#if ENABLE_TIMING_CODE

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

#endif
	
    gpuTileFlip<<< dimGrid, dimBlock >>>( d_Image, width, height);
	
#if ENABLE_TIMING_CODE
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);

    // block until the device has completed
    cudaThreadSynchronize();
	
	printf("kernel time: %.3f ms\n", elapsedTime);
#endif

	cudaThreadSynchronize();

    // check if kernel execution generated an error
    // Check for any CUDA errors
    checkCUDAError("kernel invocation");
}
