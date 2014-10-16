#include "ImageManager.h"
#include "Assert.h"

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

void ImageManager::addImage(sf::Image& image, int id)
{
	_imageList.push_back(image);

	_imageIDs[id] = _imageList.size() - 1;
}

void ImageManager::setTileSize(int size)
{
	_tileSize = size;
}

sf::Image& ImageManager::getImage(int id)
{
	return _imageList[_imageIDs[id]];
}

sf::Image& ImageManager::operator[](int idx)
{
	ASSERT(idx < _imageList.size());
	return _imageList[idx];
}
