#pragma once
#include <iostream>
#include <string>

#define SAFE_DELETE(p) {if(p) delete(p); p=NULL;}
#define SAFE_DELETE_ARRAY(p)	{ if(p) delete[](p); p = NULL;}
#define SAFE_DELETE_VOLUME(p, depth)	{ if(p) {for (int i=0;i<depth;i++)	if(p[i]) delete[](p[i]); } delete[] p; p=NULL;};

class CSeries;
template <typename T>
class CImage {
// version 1.1
// variable
public:
	CSeries* m_series;				// series

	std::string m_sImagePath;		// image file path
	std::string m_sImageName;		// image file name
	std::string m_sImageExtension;	// image file extension

	T* m_image;						// image
	int m_nWidth;					// image width
	int m_nHeight;					// image height
	int m_nChannel;					// image channel

	float m_fImagePositionX;		// image position X
	float m_fImagePositionY;		// image position Y
	float m_fImagePositionZ;		// image position Z

	float m_fImageOrientationRowX;	// image orientaiton row X
	float m_fImageOrientationRowY;	// image orientaiton row Y
	float m_fImageOrientationRowZ;	// image orientaiton row Z
	float m_fImageOrientationColX;	// image orientation col X
	float m_fImageOrientationColY;	// image orientation col Y
	float m_fImageOrientationColZ;	// image orientation col Z

	float m_fPixelSpacingX;			// pixel spacing
	float m_fPixelSpacingY;			// pixel spacing
	float m_fSliceThickness;		// slice thickness

	int m_nWL;						// window level
	int m_nWW;						// window width
	int m_nInstanceNumber;			// instance number

// function
public:
	CImage();
	~CImage();
	void init();
	void clear();
	CImage<T>* copy();
	template <typename T2>
	void copyOtherType(CImage<T2>* &pCiOtherTypeImage);

	CSeries* getSeries();
	void setSeries(CSeries* pCiSeries);

	// image path, name, extension
	std::string getImagePath();
	void setImagePath(std::string sImagePath);
	std::string getImageName();
	void setImageName(std::string sImageName);
	std::string getImageExtension();
	void setImageExtension(std::string sImageExtension);

	// image, width, height, channel, size
	T* getImage();
	bool setImage(CImage<T>* pCiImage);
	bool setImage(T* pImage, int nWidth, int nHeight, int nChannel=1);
	bool copyImage(T* &pImage, int& nWidth, int& nHeight);
	bool copyImage(T* &pImage, int& nWidth, int& nHeight, int& nChannel);
	
	int getWidth();
	int getHeight();
	int getChannel();
	int getSize();

	// image position
	void getImagePosition(float& fImagePositionX, float& fImagePositionY, float& fImagePositionZ);
	void setImagePosition(float fImagePositionX, float fImagePositionY, float fImagePositionZ);

	// image orientation
	void getImageOrientation(float& fImageOrientationRowX, float& fImageOrientationRowY, float& fImageOrientationRowZ, float& fImageOrientationColX, float& fImageOrientationColY, float& fImageOrientationColZ);
	void setImageOrientation(float fImageOrientationRowX, float fImageOrientationRowY, float fImageOrientationRowZ, float fImageOrientationColX, float fImageOrientationColY, float fImageOrientationColZ);

	// image pixel spacing
	void getPixelSpacing(float& fPixelSpacingX, float& fPixelSpacingY);
	void setPixelSpacing(float fPixelSpacingX, float fPixelSpacingY);

	// slice thickness
	float getSliceThickness();
	void setSliceThickness(float fSliceThickness);

	// window level, window width
	void getWLWW(int &nWL, int &nWW);
	void setWLWW(int nWL, int nWW);

	// instance number
	int getInstanceNumber();
	void setInstanceNumber(int nInstanceNumber);
};


// image.cpp (template�� �� ���Ͽ� �־ ó���ؾ� �Ѵٰ� ��)
template <typename T>
CImage<T>::CImage() {
	init();
}
template <typename T>
CImage<T>::~CImage() {
	clear();
}

template <typename T>
void CImage<T>::init() {
	m_series = NULL;

	m_sImagePath = "";
	m_sImageName = "";
	m_image = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nChannel = 0;

	m_fImagePositionX = 0;
	m_fImagePositionY = 0;
	m_fImagePositionZ = 0;

	m_fImageOrientationRowX = 0;
	m_fImageOrientationRowY = 0;
	m_fImageOrientationRowZ = 0;
	m_fImageOrientationColX = 0;
	m_fImageOrientationColY = 0;
	m_fImageOrientationColZ = 0;

	m_fPixelSpacingX = 0;
	m_fPixelSpacingY = 0;
	m_fSliceThickness = 0;

	m_nWL = 0;
	m_nWW = 0;
	m_nInstanceNumber = 0;
}
template <typename T>
void CImage<T>::clear() {
	SAFE_DELETE_ARRAY(m_image);
}
template <typename T>
CImage<T>* CImage<T>::copy() {
	CImage<T>* pCiImage = new CImage<T>();

	pCiImage->m_series = m_series;
	pCiImage->m_sImagePath = m_sImagePath;
	pCiImage->m_sImageName = m_sImageName;
	copyImage(pCiImage->m_image, pCiImage->m_nWidth, pCiImage->m_nHeight, pCiImage->m_nChannel);

	pCiImage->m_fImagePositionX = m_fImagePositionX;
	pCiImage->m_fImagePositionY = m_fImagePositionY;
	pCiImage->m_fImagePositionZ = m_fImagePositionZ;

	pCiImage->m_fImageOrientationRowX = m_fImageOrientationRowX;
	pCiImage->m_fImageOrientationRowY = m_fImageOrientationRowY;
	pCiImage->m_fImageOrientationRowZ = m_fImageOrientationRowZ;
	pCiImage->m_fImageOrientationColX = m_fImageOrientationColX;
	pCiImage->m_fImageOrientationColY = m_fImageOrientationColY;
	pCiImage->m_fImageOrientationColZ = m_fImageOrientationColZ;

	pCiImage->m_fPixelSpacingX = m_fPixelSpacingX;
	pCiImage->m_fPixelSpacingY = m_fPixelSpacingY;
	pCiImage->m_fSliceThickness = m_fSliceThickness;

	pCiImage->m_nWL = m_nWL;
	pCiImage->m_nWW = m_nWW;
	pCiImage->m_nInstanceNumber = m_nInstanceNumber;

	return pCiImage;
}
template <typename T> template <typename T2>
void CImage<T>::copyOtherType(CImage<T2>* &pCiOtherTypeImage) {
	if(pCiOtherTypeImage != NULL) {
		return;
	}
	pCiOtherTypeImage = new CImage<T2>();

	pCiOtherTypeImage->m_series = m_series;
	pCiOtherTypeImage->m_sImagePath = m_sImagePath;
	pCiOtherTypeImage->m_sImageName = m_sImageName;
	
	int nSize = m_nWidth * m_nHeight * m_nChannel;
	T2* image = new T2[nSize];
	for(int i=0, ni=nSize; i<ni; i++) {
		image[i] = (T2)m_image[i];
	}
	pCiOtherTypeImage->setImage(image, m_nWidth, m_nHeight, m_nChannel);
	SAFE_DELETE_ARRAY(image);

	pCiOtherTypeImage->m_fImagePositionX = m_fImagePositionX;
	pCiOtherTypeImage->m_fImagePositionY = m_fImagePositionY;
	pCiOtherTypeImage->m_fImagePositionZ = m_fImagePositionZ;

	pCiOtherTypeImage->m_fImageOrientationRowX = m_fImageOrientationRowX;
	pCiOtherTypeImage->m_fImageOrientationRowY = m_fImageOrientationRowY;
	pCiOtherTypeImage->m_fImageOrientationRowZ = m_fImageOrientationRowZ;
	pCiOtherTypeImage->m_fImageOrientationColX = m_fImageOrientationColX;
	pCiOtherTypeImage->m_fImageOrientationColY = m_fImageOrientationColY;
	pCiOtherTypeImage->m_fImageOrientationColZ = m_fImageOrientationColZ;

	pCiOtherTypeImage->m_fPixelSpacingX = m_fPixelSpacingX;
	pCiOtherTypeImage->m_fPixelSpacingY = m_fPixelSpacingY;
	pCiOtherTypeImage->m_fSliceThickness = m_fSliceThickness;

	pCiOtherTypeImage->m_nWL = m_nWL;
	pCiOtherTypeImage->m_nWW = m_nWW;
	pCiOtherTypeImage->m_nInstanceNumber = m_nInstanceNumber;
}

template <typename T>
CSeries* getSeries() {
	return m_series;
}
template<typename T>
void CImage<T>::setSeries(CSeries* pCiSeries) {
	m_series = pCiSeries;
}

template <typename T>
std::string CImage<T>::getImagePath() {
	return m_sImagePath;
}
template <typename T>
void CImage<T>::setImagePath(std::string sImagePath) {
	// filepath
	m_sImagePath = sImagePath;
}
template <typename T>
std::string CImage<T>::getImageName() {
	return m_sImageName;
}
template <typename T>
void CImage<T>::setImageName(std::string sImageName) {
	m_sImageName = sImageName;
}
template <typename T>
std::string CImage<T>::getImageExtension() {
	return m_sImageExtension;
}
template <typename T>
void CImage<T>::setImageExtension(std::string sImageExtension) {
	m_sImageExtension = sImageExtension;
}

template<typename T>
bool CImage<T>::setImage(CImage<T>* pCiImage) {
	// exception
	if(pCiImage == NULL) {
		return false;
	}

	if(pCiImage->m_image == NULL || pCiImage->m_nWidth <= 0 || pCiImage->m_nHeight <= 0 || pCiImage->m_nChannel <= 0) {
		return false;
	}

	m_nWidth = pCiImage->m_nWidth;
	m_nHeight = pCiImage->m_nHeight;
	m_nChannel = pCiImage->m_nChannel;
	int nSize = m_nWidth * m_nHeight* m_nChannel;

	if(m_image != NULL) {
		SAFE_DELETE_ARRAY(m_image);
	}
	m_image = new T[nSize];
	memcpy_s(m_image, sizeof(T)*nSize, pCiImage, sizeof(T)*nSize);
	
	for(int i=0; i< nSize; i++) {
		m_image[i] = pCiImage->m_image[i];
	}
	

	return true;
}
template <typename T>
bool CImage<T>::setImage(T* pImage, int nWidth, int nHeight, int nChannel=1) {
	// exception
	if(pImage == NULL || nWidth <= 0 || nHeight <= 0 || nChannel <= 0) {
		return false;
	}

	int nSize = nWidth * nHeight* nChannel;

	if(m_image != NULL) {
		SAFE_DELETE_ARRAY(m_image);
	}
	m_image = new T[nSize];
	memcpy_s(m_image, sizeof(T)*nSize, pImage, sizeof(T)*nSize);

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nChannel = nChannel;

	return true;
}
template <typename T>
T* CImage<T>::getImage() {
	return m_image;
}
template <typename T>
bool CImage<T>::copyImage(T* &pImage, int& nWidth, int& nHeight) {
	//
	if(pImage != NULL) {
		return false;
	}

	// 
	int nSize = m_nWidth * m_nHeight* m_nChannel;

	pImage = new T[nSize];
	memcpy_s(pImage, sizeof(T)*nSize, m_image, sizeof(T)*nSize);
	/*
	for(int i=0; i< nSize; i++) {
		pImage[i] = (T)m_image[i];
	}
	*/
	nWidth = m_nWidth;
	nHeight = m_nHeight;

	return true;
}
template <typename T>
bool CImage<T>::copyImage(T* &pImage, int& nWidth, int& nHeight, int& nChannel) {
	//
	if(pImage != NULL) {
		return false;
	}

	// 
	int nSize = m_nWidth * m_nHeight* m_nChannel;

	pImage = new T[nSize];
	memcpy_s(pImage, sizeof(T)*nSize, m_image, sizeof(T)*nSize);

	nWidth = m_nWidth;
	nHeight = m_nHeight;
	nChannel = m_nChannel;

	return true;
}
template <typename T>
int CImage<T>::getWidth() {
	return m_nWidth;
}
template <typename T>
int CImage<T>::getHeight() {
	return m_nHeight;
}
template <typename T>
int CImage<T>::getChannel() {
	return m_nChannel;
}
template <typename T>
int CImage<T>::getSize() {
	return m_nWidth * m_nHeight * m_nChannel;
}

template <typename T>
void CImage<T>::getImagePosition(float& fImagePositionX, float& fImagePositionY, float& fImagePositionZ) {
	fImagePositionX = m_fImagePositionX;
	fImagePositionY = m_fImagePositionY;
	fImagePositionZ = m_fImagePositionZ;
}
template <typename T>
void CImage<T>::setImagePosition(float fImagePositionX, float fImagePositionY, float fImagePositionZ) {
	m_fImagePositionX = fImagePositionX;
	m_fImagePositionY = fImagePositionY;
	m_fImagePositionZ = fImagePositionZ;
}

template <typename T>
void CImage<T>::getImageOrientation(float& fImageOrientationRowX, float& fImageOrientationRowY, float& fImageOrientationRowZ, float& fImageOrientationColX, float& fImageOrientationColY, float& fImageOrientationColZ) {
	fImageOrientationRowX = m_fImageOrientationRowX;
	fImageOrientationRowY = m_fImageOrientationRowY;
	fImageOrientationRowZ = m_fImageOrientationRowZ;
	fImageOrientationColX = m_fImageOrientationColX;
	fImageOrientationColY = m_fImageOrientationColY;
	fImageOrientationColZ = m_fImageOrientationColZ;
}
template <typename T>
void CImage<T>::setImageOrientation(float fImageOrientationRowX, float fImageOrientationRowY, float fImageOrientationRowZ, float fImageOrientationColX, float fImageOrientationColY, float fImageOrientationColZ) {
	m_fImageOrientationRowX = fImageOrientationRowX;
	m_fImageOrientationRowY = fImageOrientationRowY;
	m_fImageOrientationRowZ = fImageOrientationRowZ;
	m_fImageOrientationColX = fImageOrientationColX;
	m_fImageOrientationColY = fImageOrientationColY;
	m_fImageOrientationColZ = fImageOrientationColZ;
}

template <typename T>
void CImage<T>::getPixelSpacing(float& fPixelSpacingX, float& fPixelSpacingY) {
	fPixelSpacingX = m_fPixelSpacingX;
	fPixelSpacingY = m_fPixelSpacingY;
}
template <typename T>
void CImage<T>::setPixelSpacing(float fPixelSpacingX, float fPixelSpacingY) {
	m_fPixelSpacingX = fPixelSpacingX;
	m_fPixelSpacingY = fPixelSpacingY;
}

template <typename T>
float CImage<T>::getSliceThickness() {
	return m_fSliceThickness;
}
template <typename T>
void CImage<T>::setSliceThickness(float fSliceThickness) {
	m_fSliceThickness = fSliceThickness;
}

template <typename T>
void CImage<T>::getWLWW(int &nWL, int &nWW) {
	nWL = m_nWL;
	nWW = m_nWW;
}
template <typename T>
void CImage<T>::setWLWW(int nWL, int nWW) {
	m_nWL = nWL;
	m_nWW = nWW;
}

template <typename T>
int CImage<T>::getInstanceNumber() {
	return m_nInstanceNumber;
}
template <typename T>
void CImage<T>::setInstanceNumber(int nInstanceNumber) {
	m_nInstanceNumber = nInstanceNumber;
}