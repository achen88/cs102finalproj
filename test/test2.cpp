#include "..\\include\\project_math.h"
#include "..\\include\\bmp_writer.h"
#include "..\\include\\texture_loader.h"
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
	//******************** initialization ********************
	ofstream fout;
	Vect to_light(0, 0, 0);
	//******************** read config ********************
	string junk;
	int earth_roughness;
	int moon_roughness;
	double dcamera;
	double l_ambient;
	double l_diffuse;
	double l_specular;
	double moon_coeff;
	double milkyway_coeff;
	double moon_ro;
	double ro;
	double light_frames_per_cycle;
	double moon_frames_per_cycle;
	double moon_rotate_frames_per_cycle;
	double earth_rotate_frames_per_cycle;

	ifstream config;
	config.open(argv[1]);
	config >> junk >> earth_roughness
			>> junk >> moon_roughness
			>> junk >> dcamera
			>> junk >> l_ambient
			>> junk >> l_diffuse
			>> junk >> l_specular
			>> junk >> moon_coeff
			>> junk >> milkyway_coeff
			>> junk >> moon_ro
			>> junk >> ro
			>> junk >> light_frames_per_cycle
			>> junk >> moon_frames_per_cycle
			>> junk >> moon_rotate_frames_per_cycle
			>> junk >> earth_rotate_frames_per_cycle;

	//******************** error logging ********************
	ofstream errr;
	errr.open("err.txt");

	//******************** load milkyway texture ********************
	ifstream fin_milkyway;
	fin_milkyway.open("textures\\milkyway_small.bmp", std::ios_base::in | std::ios_base::binary);
	unsigned int milkyway_x_size = 0, milkyway_y_size = 0;
	junk_header(fin_milkyway, milkyway_x_size, milkyway_y_size);

	Sphere milkyway = Sphere(0, 0, 0, 0, 0, 0);

	milkyway.texture = new Color*[milkyway_y_size];
	for(int i = 0; i < milkyway_y_size; i++) {
		milkyway.texture[i] = new Color[milkyway_x_size];
		for(int j = 0; j < milkyway_x_size; j++) read_pixel(fin_milkyway, milkyway.texture[i][j]);
	}

	//******************** load earth texture ********************
	ifstream fin_earth;
	fin_earth.open("textures\\earth_small.bmp", std::ios_base::in | std::ios_base::binary);
	unsigned int earth_x_size = 0, earth_y_size = 0;
	junk_header(fin_earth, earth_x_size, earth_y_size);

	Sphere earth = Sphere(0, 0, 0, 180, 0, 0.408);

	earth.texture = new Color*[earth_y_size];
	for(int i = 0; i < earth_y_size; i++) {
		earth.texture[i] = new Color[earth_x_size];
		for(int j = 0; j < earth_x_size; j++) read_pixel(fin_earth, earth.texture[i][j]);
	}

	//******************** load moon texture ********************
	ifstream fin_moon;
	fin_moon.open("textures\\moon.bmp", std::ios_base::in | std::ios_base::binary);
	unsigned int moon_x_size = 0, moon_y_size = 0;
	junk_header(fin_moon, moon_x_size, moon_y_size);

	Sphere moon = Sphere(0, 0, 0, 30, 0, 0);

	moon.texture = new Color*[moon_y_size];
	for(int i = 0; i < moon_y_size; i++) {
		moon.texture[i] = new Color[moon_x_size];
		for(int j = 0; j < moon_x_size; j++) read_pixel(fin_moon, moon.texture[i][j]);
	}

	//******************** generate pictures ********************
	for(int time = 0; time < 1500; time++) {
		//********* open file *********
		stringstream ss;
		ss << "results\\";
		ss << setfill('0') << setw(4);
		ss << time;
		ss << ".bmp";
		string file;
		ss >> file;
		cout << file << endl;
		fout.open(file.c_str(), std::ios_base::out | std::ios_base::binary);
		write_bmp_header(fout, 512, 512);

		//********* calculate rotation + orbit positions *********
		earth.setTheta(-time/earth_rotate_frames_per_cycle*2*M_PI);

		double moon_x = -300*cos(moon_ro)*cos(-time/moon_frames_per_cycle*2*M_PI)+1;
		double moon_y = -300*sin(-time/moon_frames_per_cycle*2*M_PI);
		double moon_z = 300*sin(moon_ro)*cos(-time/moon_frames_per_cycle*2*M_PI)+1;
		moon.setX(moon_x);
		moon.setY(moon_y);
		moon.setZ(moon_z);
		moon.setTheta(time/moon_rotate_frames_per_cycle*2*M_PI);


		double new_x = cos(ro)*sin(time/light_frames_per_cycle*2*M_PI);
		double new_y = cos(time/light_frames_per_cycle*2*M_PI);
		double new_z = -sin(ro)*sin(time/light_frames_per_cycle*2*M_PI);
		to_light = Vect(new_x, new_y, new_z);
		to_light.normalize();

		//********* ray trace *********
		for(int s = -256; s < 256; s++) {
			for(int t = -256; t < 256; t++) {
				Ray r = Ray(0, 512, 0, Vect(0,0,0));
				Vect ve(t*dcamera,-1, s*dcamera);
				ve.normalize();
				r.setU(ve);
				//********* collision detection + follow-up *********
				bool earth_collision = collision(r, earth);
				bool moon_collision = collision(r, moon);
				if(!earth_collision && !moon_collision) {
					Color galaxy = milkyway.texture[(int)((s+256)*milkyway_y_size/512.0)][(int)((t+256)*milkyway_x_size/512.0)];
					galaxy.scale(milkyway_coeff);
					write_bmp_pixel(fout, galaxy);
				}
				else if(!earth_collision && moon_collision) {
					vector<double> solutions = solve_collision(r, moon);
					Vect point(r.getX() + solutions[0]*r.getU().getX(), r.getY() + solutions[0]*r.getU().getY(), r.getZ() + solutions[0]*r.getU().getZ());
					Color ambient = moon.uv_map(point, (int) moon_x_size, (int) moon_y_size, errr);
					ambient.scale(l_ambient);
					Color diffuse = moon.uv_map(point, (int) moon_x_size, (int) moon_y_size, errr);
					point.normalize();
					diffuse.scale(moon_coeff*l_diffuse*max(to_light.dot_product(point), 0.0));
					Color specular = moon.uv_map(point, (int) moon_x_size, (int) moon_y_size, errr);
					Vect reflect(-to_light.getX() + 2*point.dot_product(to_light)*point.getX(),
								 -to_light.getY() + 2*point.dot_product(to_light)*point.getY(),
								 -to_light.getZ() + 2*point.dot_product(to_light)*point.getZ());
					reflect.normalize();
					specular.scale(l_specular*pow(max(-reflect.dot_product(r.getU()), 0.0), moon_roughness));
					write_bmp_pixel(fout, Color(ambient.getR() + diffuse.getR() + specular.getR(), ambient.getG() + diffuse.getG() + specular.getG(), ambient.getB() + diffuse.getB() + specular.getB()));
				}
				else if(earth_collision && !moon_collision) {
					vector<double> solutions = solve_collision(r, earth);
					Vect point(r.getX() + solutions[0]*r.getU().getX(), r.getY() + solutions[0]*r.getU().getY(), r.getZ() + solutions[0]*r.getU().getZ());
					Color ambient = earth.uv_map(point, (int) earth_x_size, (int) earth_y_size, errr), diffuse = Color(), specular = Color();
					ambient.scale(l_ambient);
					if(!collision(Ray(point,to_light), moon) || (solve_collision(Ray(point,to_light), moon)[0] < 0)) {
						diffuse = earth.uv_map(point, (int) earth_x_size, (int) earth_y_size, errr);
						point.normalize();
						diffuse.scale(l_diffuse*max(to_light.dot_product(point), 0.0));
						specular = earth.uv_map(point, (int) earth_x_size, (int) earth_y_size, errr);
						Vect reflect(-to_light.getX() + 2*point.dot_product(to_light)*point.getX(),
									 -to_light.getY() + 2*point.dot_product(to_light)*point.getY(),
									 -to_light.getZ() + 2*point.dot_product(to_light)*point.getZ());
						reflect.normalize();
						specular.scale(l_specular*pow(max(-reflect.dot_product(r.getU()), 0.0), earth_roughness));
					}
					write_bmp_pixel(fout, Color(ambient.getR() + diffuse.getR() + specular.getR(), ambient.getG() + diffuse.getG() + specular.getG(), ambient.getB() + diffuse.getB() + specular.getB()));
				}
				else {
					vector<double> earth_solutions = solve_collision(r, earth);
					vector<double> moon_solutions = solve_collision(r, moon);
					if(earth_solutions[0] < moon_solutions[0]) {
						vector<double> solutions = earth_solutions;
						Vect point(r.getX() + solutions[0]*r.getU().getX(), r.getY() + solutions[0]*r.getU().getY(), r.getZ() + solutions[0]*r.getU().getZ());
						Color ambient = earth.uv_map(point, (int) earth_x_size, (int) earth_y_size, errr), diffuse = Color(), specular = Color();
						ambient.scale(l_ambient);
						if(!collision(Ray(point,to_light), moon) || (solve_collision(Ray(point,to_light), moon)[0] < 0)) {
							diffuse = earth.uv_map(point, (int) earth_x_size, (int) earth_y_size, errr);
							point.normalize();
							diffuse.scale(l_diffuse*max(to_light.dot_product(point), 0.0));
							specular = earth.uv_map(point, (int) earth_x_size, (int) earth_y_size, errr);
							Vect reflect(-to_light.getX() + 2*point.dot_product(to_light)*point.getX(),
										 -to_light.getY() + 2*point.dot_product(to_light)*point.getY(),
										 -to_light.getZ() + 2*point.dot_product(to_light)*point.getZ());
							reflect.normalize();
							specular.scale(l_specular*pow(max(-reflect.dot_product(r.getU()), 0.0), earth_roughness));
						}
						write_bmp_pixel(fout, Color(ambient.getR() + diffuse.getR() + specular.getR(), ambient.getG() + diffuse.getG() + specular.getG(), ambient.getB() + diffuse.getB() + specular.getB()));
					}
					else {
						vector<double> solutions = moon_solutions;
						Vect point(r.getX() + solutions[0]*r.getU().getX(), r.getY() + solutions[0]*r.getU().getY(), r.getZ() + solutions[0]*r.getU().getZ());
						Color ambient = moon.uv_map(point, (int) moon_x_size, (int) moon_y_size, errr);
						ambient.scale(l_ambient);
						Color diffuse = moon.uv_map(point, (int) moon_x_size, (int) moon_y_size, errr);
						point.normalize();
						diffuse.scale(moon_coeff*l_diffuse*max(to_light.dot_product(point), 0.0));
						Color specular = moon.uv_map(point, (int) moon_x_size, (int) moon_y_size, errr);
						Vect reflect(-to_light.getX() + 2*point.dot_product(to_light)*point.getX(),
									 -to_light.getY() + 2*point.dot_product(to_light)*point.getY(),
									 -to_light.getZ() + 2*point.dot_product(to_light)*point.getZ());
						reflect.normalize();
						specular.scale(l_specular*pow(max(-reflect.dot_product(r.getU()), 0.0), moon_roughness));
						write_bmp_pixel(fout, Color(ambient.getR() + diffuse.getR() + specular.getR(), ambient.getG() + diffuse.getG() + specular.getG(), ambient.getB() + diffuse.getB() + specular.getB()));
					}
				}
			}
			write_bmp_padding(fout, 512, 512);
		}

		fout.close();
	}

	errr.close();
	return 0;
}