#include "Model.h"

namespace M{
	void Model::Draw(R::Render renderer){
		for (int i = 0; i < m_points.size() - 1; i++){
			V::vec2 p1 = m_points[i];
			V::vec2 p2 = m_points[i + 1];
			renderer.drawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

}