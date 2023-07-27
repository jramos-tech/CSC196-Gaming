#pragma once
#include "Vector2.h"

namespace T {
	class Transform {
	public:
		V::vec2 position;
		float rotation = 0;
		float scale = 1;
	public:
		Transform() = default;
		Transform(const V::vec2& position, float rotation, float scale = 1):
			position{position},
			rotation {rotation},
			scale{scale}
		{}
	};
}
