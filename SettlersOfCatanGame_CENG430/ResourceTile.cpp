#include "ResourceTile.h"

ResourceTile::ResourceTile(GameBoard::Elements e, int value)
{
	element = e;
	rollValue = value;
	borderingNodes.reserve(6);
}
