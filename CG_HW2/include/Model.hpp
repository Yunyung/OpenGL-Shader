#define _CRT_SECURE_NO_WARNINGS
#include "glmMathematics\glm\glm.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include <iostream>
#include <stdarg.h>

std::vector<glm::vec3> positions;
std::vector<glm::vec2> texcoords;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> tangents;
std::vector<glm::vec3> bitangents;
GLMmodel *model;

void LoadObj(char* filename)
{
	model = glmReadOBJ(filename);
	
	for (int i = 0; i < model->numtriangles; ++i)
	{
		int vindex[3] = { model->triangles[i].vindices[0], model->triangles[i].vindices[1], model->triangles[i].vindices[2] };
		std::vector<glm::vec3> p;
		
		for (int j = 0; j < 3; ++j) {
			glm::vec3 pos = glm::vec3(model->vertices[vindex[j] * 3 + 0], model->vertices[vindex[j] * 3 + 1], model->vertices[vindex[j] * 3 + 2]);
			positions.push_back(pos);
			p.push_back(pos);
		}

		int nindex[3] = { model->triangles[i].nindices[0], model->triangles[i].nindices[1], model->triangles[i].nindices[2] };
		std::vector<glm::vec3> n;

		for (int j = 0; j < 3; ++j) {
			glm::vec3 nor = glm::vec3(model->normals[nindex[j] * 3 + 0], model->normals[nindex[j] * 3 + 1], model->normals[nindex[j] * 3 + 2]);
			normals.push_back(nor);
			n.push_back(nor);
		}

		int tindex[3] = { model->triangles[i].tindices[0], model->triangles[i].tindices[1], model->triangles[i].tindices[2] };
		std::vector<glm::vec2> t;

		for (int j = 0; j < 3; ++j) {
			glm::vec2 tex = glm::vec2(model->texcoords[tindex[j] * 2 + 0], model->texcoords[tindex[j] * 2 + 1]);
			texcoords.push_back(tex);
			t.push_back(tex);
		}

		glm::vec3 v0 = p[0];
		glm::vec3 v1 = p[1];
		glm::vec3 v2 = p[2];

		glm::vec2 uv0 = t[0];
		glm::vec2 uv1 = t[1];
		glm::vec2 uv2 = t[2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		for (int j = 0; j < 3; ++j) {
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}
	}

	return;
}
