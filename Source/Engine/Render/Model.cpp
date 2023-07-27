#include "Model.h"
#include <sstream>

namespace Sc{
	bool Model::Load(const std::string& filename){
		std::string buffer;
		F::readFile(filename, buffer);
		std::istringstream stream(buffer);
		//read color
		stream >> m_color;
		//read number of points
		std::string line;
		std::getline(stream, line);
		int numPoints = std::stoi(line);
		//read vector2 points
		for (int i = 0; i < numPoints; i++){
			V::vec2 point;
			stream >> point;
			m_points.push_back(point);
		}
		return true;
	}
	void Model::Draw(Sc::Render& renderer, const V::vec2& position, float rotation, float scale) {
		if (m_points.empty()) return;
		renderer.setColor(Color::ToInt(m_color.r), Color::ToInt(m_color.g), Color::ToInt(m_color.b), Color::ToInt(m_color.a));
		for (int i = 0; i < m_points.size() - 1; i++) {
			V::vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
			V::vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;
			renderer.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Model::Draw(Sc::Render& renderer, const T::Transform& transform){
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	float Model::GetRadius(){
		if (m_radius != 0) return m_radius;
		for (auto point : m_points) {
			float length = point.length();
			m_radius = MaUt::Max(m_radius, length);
		}
		return m_radius;
	}
}