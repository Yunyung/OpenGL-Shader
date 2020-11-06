#include <stdio.h>
#include "glm_helper.h"

void print_model_info(const GLMmodel* model) {
	const GLMmodel* m = model;
	printf("pathname: %s\n", m->pathname);
	printf("mtllibname: %s\n", m->mtllibname);
	printf("position: (%.3f, %.3f, %.3f)\n",
		m->position[0], m->position[1], m->position[2]);
	printf("\n");
	printf("numvertices: %d\n", m->numvertices); // float in vertices is 3 * numvertices
	printf("numnormals: %d\n", m->numnormals); // float in normals is 3 * numnormals
	printf("numtexcoords: %d\n", m->numtexcoords);// float in texcoords is 2 * numtexcoords
	printf("numfacetnorms: %d\n", m->numfacetnorms); // float in facetnorms is 3 * numfacetnorms
	printf("numtriangles: %d\n", m->numtriangles);
	printf("nummaterials: %d\n", m->nummaterials);
	for (int i = 0; i < m->nummaterials; ++i)
	{
		GLMmaterial mm = m->materials[i];
		printf("  material name: %s\n", mm.name);
		printf("  material map_Kd(texture) index in model: %u\n", mm.map_diffuse);
		printf("  material shininess: %.3f\n", mm.shininess);
		printf("\n");
	}

	printf("numgroups: %d\n", m->numgroups);
	
	GLMgroup *g = m->groups;
	while(g) {
		printf("  group name: %s\n", g->name);
		printf("  group numtriangles: %u\n", g->numtriangles);
		printf("  group material index: %u\n", g->material);
		printf("\n");
		g = g->next;
	}
#ifndef AVL
	printf("numtextures: %d\n", m->numtextures);
	for (int i = 0; i < m->numtextures; ++i)
	{
		GLMtexture t = m->textures[i];
		printf("  textures name: %s\n", t.name);
		printf("  texture index in OpenGL: %u\n", t.id);
		printf("\n");
	}
#endif
}