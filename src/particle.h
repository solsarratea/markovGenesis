#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_START,
	PARTICLE_MODE_RANDOM,
};

class Particle{

	public:
		Particle(int totalParticles);
		static int objectCount;

		void setParticles( vector<glm::vec3> * all);
		void reset();
		void update();
		void draw();

		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;

		float uniqueVal;
		float scale;
		int id;
		vector <glm::vec3> * trustedParticles;
		vector <int> context;
		static void handleNewState(Particle a, Particle b, int state);

};
