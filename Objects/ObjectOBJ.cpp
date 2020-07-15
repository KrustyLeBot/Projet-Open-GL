#include "ObjectOBJ.h"
#include "../glm/vec3.hpp"

ObjectOBJ::ObjectOBJ(const char* filename, GLint hex_col, GLboolean frameOnly)
	: Object::Object(frameOnly)
{
	m_mode = GL_TRIANGLES;

	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return;
	}
	std::vector< glm::vec3 > temp_vertices;
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return;
			}
			glm::vec3 temp_vect = temp_vertices[vertexIndex[0]-1];
			m_vertices.push_back(temp_vect.x);
			m_vertices.push_back(temp_vect.y);
			m_vertices.push_back(temp_vect.z);

			temp_vect = temp_vertices[vertexIndex[1] - 1];
			m_vertices.push_back(temp_vect.x);
			m_vertices.push_back(temp_vect.y);
			m_vertices.push_back(temp_vect.z);

			temp_vect = temp_vertices[vertexIndex[2] - 1];
			m_vertices.push_back(temp_vect.x);
			m_vertices.push_back(temp_vect.y);
			m_vertices.push_back(temp_vect.z);
		}
	}

	for (int i = 0; i < m_vertices.size()/3; i++)
	{
		m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
		m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
		m_colors.push_back(((hex_col) & 0xFF) / 255.0);
	}
}
