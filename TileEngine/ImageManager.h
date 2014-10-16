#pragma once

#include <vector>
#include <SFML\Graphics.hpp>

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	void addImage(sf::Image& image, int id);
	void setTileSize(int size);
	
	sf::Image& getImage(int id);
	sf::Image& operator[](int idx);

private:
	typedef std::vector<sf::Image> ImageList;
	ImageList _imageList;

	std::map<int, int> _imageIDs;

	int _tileSize;
};

