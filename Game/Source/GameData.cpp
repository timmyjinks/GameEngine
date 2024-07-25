#include "GameData.h"

namespace GameData {
	std::vector<Vector2> shipPoints{
		{ 5, 0 },
		{ -2, 7 },
		{ -3, 6 },
		{ 0, 3 },
		{ -2, 2 },
		{ -1, 1 },
		{ -2, 0 },
		{ -1, -1 },
		{ -2, -2 },
		{ 0, -3 },
		{ -3, -6 },
		{ -2, -7 },
		{ 5, 0 }
	};

	std::vector<Vector2> bulletPoints{
		{ 5, 0 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 0 }
	};

	std::vector<Vector2> enemyPoints{
		{ 5, -5 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 5 },
		{ 5, -5 }
	};

	std::vector<Vector2> pickupPoints{
		{ 5, -5 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 5 },
		{ 5, -5 }
	};

	std::vector<Vector2> bossPoints{
		{ 5, -5 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 5 },
		{ 5, 0 }
	};

	std::vector<Vector2> scorePoints{
		{ 5, -5 },
		{ -5, -5 },
		{ -5, 5 },
		{ 5, 5 },
		{ 5, 0 }
	};

}
