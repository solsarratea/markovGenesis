#pragma once
#include "ofMain.h"
#include "ofxMarkovChain.h"
#include "particle.h"

class ofApp : public ofBaseApp{

	ofxMC::MarkovChain markov;
	ofPolyline line;
	float w;
	vector <Particle> p;
	vector <glm::vec3> trustedParticles;
	vector <glm::vec3> attractPointsWithMovement;

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};
