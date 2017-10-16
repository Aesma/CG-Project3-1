#include "scene_parser.h"
#include "image.h"
#include "group.h"
#include "hit.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char*argv[])
{
	char *input_file = NULL;
	int width = 100;
	int height = 100;
	char *output_file = NULL;
	float depth_min = 0;
	float depth_max = 1;
	char *depth_file = NULL;

	// sample command line:
	// raytracer -input scene1_1.txt -size 200 200 -output output1_1.tga -depth 9 10 depth1_1.tga

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-input")) {
			i++; assert(i < argc);
			input_file = argv[i];
		}
		else if (!strcmp(argv[i], "-size")) {
			i++; assert(i < argc);
			width = atoi(argv[i]);
			i++; assert(i < argc);
			height = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-output")) {
			i++; assert(i < argc);
			output_file = argv[i];
		}
		else if (!strcmp(argv[i], "-depth")) {
			i++; assert(i < argc);
			depth_min = atof(argv[i]);
			i++; assert(i < argc);
			depth_max = atof(argv[i]);
			i++; assert(i < argc);
			depth_file = argv[i];
		}
		else {
			printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	SceneParser *sp = new SceneParser(input_file);
	int num_materials = sp->getNumMaterials();
	Group *group = sp->getGroup();
	Camera *camera = sp->getCamera();
	Vec3f background_color = sp->getBackgroundColor();

	int square = width > height ? width : height;
	Image* image = new Image(square, square);
	image->SetAllPixels(background_color);
	Image* depth_image = new Image(square, square);
	depth_image->SetAllPixels(background_color);

	float precalc = depth_max - depth_min;
	if (precalc == 0)
	{
		precalc = 1.0f;
	}

	for (int i = 0; i < square; i++)
		for (int j = 0; j < square; j++)
		{
			float x = (float)i * 2 / square - 1;
			float y = (float)j * 2 / square - 1;
			Ray ray = camera->generateRay(Vec2f(x, y));
			Hit* hit = new Hit(INT_MAX, sp->getMaterial(0));
			float tmin = camera->getTMin();
			if (group->intersect(ray, *hit, tmin)){
				image->SetPixel(i, j, hit->getMaterial()->getDiffuseColor());

				float t = hit->getT();
				if (t < depth_min)
				{
					t = depth_min;
				}
				if (t > depth_max)
				{
					t = depth_max;
				}
				float volumn = (depth_max - t) / precalc;
				depth_image->SetPixel(i, j, Vec3f(volumn, volumn, volumn));
			}
		}

	image->SaveTGA(output_file);
	depth_image->SaveTGA(depth_file);

	return 0;
}