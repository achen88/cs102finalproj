#include "project_math.h"
#include "bmp_writer.h"

#define roughness 23

using namespace std;

int main() {
	ofstream fout;
	fout.open("earth.bmp", std::ios_base::out | std::ios_base::binary);
	write_bmp_header(fout, 512, 512);

	Color green = Color(0, 1, 0);
	Sphere s = Sphere(0, 0, 0, 150, green);

	for(int k = -256; k < 256; k++) {
		for(int i = -256; i < 256; i++) {
			Ray r;
			r.coord[0] = i;
			r.coord[1] = 512;
			r.coord[2] = k;
			r.vect = vector<double>(3, 0);
			r.vect[1] = -1;

			if(!collision(r, s)) {
				write_bmp_pixel(fout, Color(0, 0, 0));
			}
			else {
				//ambient
				double c_red = 0;
				double c_green = .1;
				double c_blue = 0;

				//diffuse
				vector<double> solutions = solve_collision(r, s);
				vector<double> point(3, 0);
				for(int n = 0; n < 3; n++) point[n] = r.coord[n] + solutions[0]*r.vect[n];

				vector<double> normal = normalize(point);
				vector<double> to_light(3, 1); 					//at inf
				to_light[1] = 2;
				to_light = normalize(to_light);

				double angle = get_angle(normal, to_light);

				c_green += .86*max(dot_product(normal, to_light), 0.0);

				//specular
				vector<double> reflect(3, 0);
				for(int n = 0; n < 3; n++) reflect[n] = -to_light[n] + 2 * (dot_product(normal, to_light)) * normal[n];
				reflect = normalize(reflect);

				double green_spec;
				c_red += .9*pow(max(0.0,-dot_product(reflect, r.vect)),roughness);
				c_green += .9*pow(max(0.0,-dot_product(reflect, r.vect)),roughness);
				c_blue += .9*pow(max(0.0,-dot_product(reflect, r.vect)),roughness);


				if(c_red > 1) c_red = 1;
				if(c_green > 1) c_green = 1;
				if(c_blue > 1) c_blue = 1;

				write_bmp_pixel(fout, Color(c_red, c_green, c_blue));
			}
		}
		write_bmp_padding(fout, 512, 512);
	}

	fout.close();
	return 0;
}