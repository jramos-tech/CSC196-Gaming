#pragma once
#include "Core/Core.h"
#include "Renderer.h"
#include <vector>

namespace M{
	class Model{
	public:
		Model() = default;
		Model(std::vector<V::vec2>& points) : m_points{points}{}
		void Draw(R::Render renderer);
	private:
		std::vector<V::vec2> m_points;
	};
}
