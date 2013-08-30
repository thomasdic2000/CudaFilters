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

#ifndef SINGLEIMAGEFILTERCHAIN_H_
#define SINGLEIMAGEFILTERCHAIN_H_

/** 
	\file SingleImageFilterChain.h
	SingleImageFilterChain s�n�f�n�n tan�m�n� i�eren ba�l�k dosyas�.
*/

#include <vector>

#include "common.h"

#include "SingleImageFilter.h"

/**
	Bir veya birden fazla filtrenin tek bir filtre gibi uygulanmas�n� sa�layan s�n�f.

	FilterImage metodu �a�r�ld���nda AppendFilter metodu ile eklenen filtreleri eklenme s�ras�na uygun olarak zincir gibi CPU veya GPU �zerinde �al��t�r�r.
	Eklenebilen filtrelerin tipi ISingleImageFilter tipindedir.
*/
class SingleImageFilterChain : public SingleImageFilter
{
private:
	std::vector<ISingleImageFilter*> vecFilters;

	DISALLOW_COPY_AND_ASSIGN(SingleImageFilterChain);

public:

	/**
		SingleImageFilterChain yarat�c�s�.	
	*/
	SingleImageFilterChain()		
	{		
	}

	/**
		Zincire filtre ekler.

		\param filter Eklenecek filtre.
	*/
	void AppendFilter(ISingleImageFilter* filter)
	{
		assert( filter && "AppendFilter: filter is invalid." );

		vecFilters.push_back( filter );

		if ( isInited )
		{
			filter->InitFilter( width, height, rowStride );
		}
	}

	/**
		Son eklenen filtreyi zincirden ��kart�r.

		��kart�lan filtrenin ReleaseFilter metodu �a�r�l�r.
	*/
	void RemoveLastFilter()
	{
		ISingleImageFilter* lastFilter = vecFilters.back();
		assert( lastFilter && "RemoveLastFilter: lastFilter is invalid." );

		lastFilter->ReleaseFilter();

		vecFilters.pop_back();
	}

	/**
		T�m filtreleri siler.

		��kart�lan filtrenin ReleaseFilter metodu �a�r�l�r.
	*/
	void RemoveAll()
	{
		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{			
			(*fi)->ReleaseFilter();
		}

		vecFilters.clear();
	}
	
	virtual void InitFilter(int width, int height, int rowStride)
	{
		SingleImageFilter::InitFilter(width, height, rowStride);	

		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{			
			(*fi)->InitFilter( width, height, rowStride );
		}
	}

	virtual void FilterImage(char* imageData)
	{
		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{
			(*fi)->FilterImage( imageData );
		}
	}

	virtual void ReleaseFilter()
	{
		if( this->isReleased )
			return;

		SingleImageFilter::ReleaseFilter();

		vector<ISingleImageFilter*>::const_iterator fi;
		vector<ISingleImageFilter*>::const_iterator fEnd;

		for (fi = vecFilters.begin(), fEnd = vecFilters.end(); fi != fEnd; fi++)
		{
			(*fi)->ReleaseFilter();
		}
	}

};

#endif SINGLEIMAGEFILTERCHAIN_H_