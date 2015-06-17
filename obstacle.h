#include "material.h"
#include "col.h"

using namespace std;

class Obstacle {
	public:
		Obstacle(Material material, Rect rect, bool bottom);
		Material getMaterial();
		Rect getRect();
		bool isBottom();
	private:
		Material material;
		Rect rect;
		bool bottom;
		
};
