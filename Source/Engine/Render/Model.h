#pragma once
#include "Core/Core.h"
#include "Renderer.h"
#include <vector>

namespace Sc{
	class Model{
	public:
		Model() = default;
		Model(std::vector<V::vec2>& points) : m_points{points}{}
		bool Load(const std::string& filename);
		void Draw(Sc::Render& renderer,const V::vec2& position, float roation, float scale);
		void Draw(Sc::Render& renderer, const T::Transform& transform);
		float GetRadius();
	private:
		std::vector<V::vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}
