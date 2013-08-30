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

#ifndef ISINGLEIMAGEFILTER_H_
#define ISINGLEIMAGEFILTER_H_

/**
	\file ISingleImageFilter.h
	ISingleImageFilter aray�z�n�n tan�m�n� i�erir.
*/

/**
	Resim filtreleme i�lemleri i�in ISingleImageFilter aray�z�.

	Aray�zdeki FilterImage metodunu ger�ekleyen s�n�flar g�r�nt� i�leme yapabilirler. 
	Filtreleme i�lemine ba�lamadan �nce bir kere InitFilter metodu �a�r�l�r, 
	filtreleme tekrar yap�lmayacaksa ReleaseFilter metodu �a�r�l�r.
*/

class ISingleImageFilter
{

public:

	/**
		G�r�nt� ile ilgili alloc ve benzeri i�lemlerin yap�lmas�n� sa�lar. 	

		\param width G�r�nt�n�n piksel geni�li�i.
		\param height G�r�nt�n�n piksel y�ksekli�i.
	*/
	virtual void InitFilter(int width, int height, int rowStride) = 0;

	/** 
		G�r�nt�n�n yerinde(in-place) i�lenmesi i�in �a�r�lan metod. 

		\param imageData G�r�nt�n�n BGR kanal s�ral� bellekteki adresi.
	*/
	virtual void FilterImage(char* imageData) = 0;

	/** G�r�nt� ile ilgili kaynaklar�n b�rak�lmas�n� sa�lar. */
	virtual void ReleaseFilter() = 0;

};

#endif // ISINGLEIMAGEFILTER_H_