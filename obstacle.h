#include "material.h"
#include "col.h"

using namespace std;

class Obstacle {
	public:
		Obstacle(Material material, Rect rect);
		Material getMaterial();
		Rect getRect();
	private:
		Material material;
		Rect rect;
};
