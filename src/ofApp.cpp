#include "ofApp.h"
// Transition matrix: 4 states (u3, right, down, left)
// each state as the same probability (0.25)

void ofApp::setup(){
  ofSetVerticalSync(false);
	ofSetFrameRate(60);

  ofxMC::Matrix mat("transitionMatrix.txt");
  markov.setup(mat, 0);
  int num = 20;
	p.assign(num, Particle(num));
	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles(){
	trustedParticles.clear();
	for(int i = 0; i < 20; i++){
	trustedParticles.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}

	attractPointsWithMovement = trustedParticles;

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setParticles(&attractPointsWithMovement);
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update(){
  for( int i = 0; i < p.size(); i++){
	  for( int j = 0; j < i; j++){
        int stateI = p[i].context[p[j].id];
        int stateJ = p[j].context[p[i].id];
        ofxMC::Matrix m = markov.getTransitionMatrix();
        float prob = ofRandom(1.0);
        float min = 1;
        int newState = 0;


        if (stateI == 0 && stateJ == 0 ){
          vector<float> row =  m[0];
          for (int i = 0; i < row.size(); i++) {
            if(abs(row[i] - prob) < min){
                min = row[i];
                newState = i;
                Particle::handleNewState(p[i],p[j],newState);
            }
          }
        }
        else if (stateI == 1 && stateJ == 0 ){
          vector<float> row = m[1];
          for (int i = 0; i < row.size(); i++) {
            if(abs(row[i] - prob) < min){
                min = row[i];
                newState = i;
                Particle::handleNewState(p[i],p[j],newState);
            }
          }
        }
        else if (stateI == 0 && stateJ == 1 ){
          vector<float> row = m[2];
          for (int i = 0; i < row.size(); i++) {
            if(abs(row[i] - prob) < min){
                min = row[i];
                newState = i;
                Particle::handleNewState(p[i],p[j],newState);
            }
          }

        }
        else if (stateI == 0 && stateJ == 0 ){
          vector<float> row = m[3];
          for (int i = 0; i < row.size(); i++) {
            if(abs(row[i] - prob) < min){
                min = row[i];
                newState = i;
                Particle::handleNewState(p[i],p[j],newState);
            }
          }

        }

      }
   }

	// for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
	// 	attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
	// 	attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	// }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}

	ofSetColor(230);
	// ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-2 to change mode.", 10, 20);
}

  //--------------------------------------------------------------
  void ofApp::keyPressed(int key){
  	// if( key == '1'){
  	// 	currentMode = PARTICLE_MODE_START;
  	// 	currentModeStr = "1 - PARTICLE_MODE_START ";
  	// }
    // if( key == '2'){
  	// 	currentMode = PARTICLE_MODE_RANDOM;
  	// 	currentModeStr = "1 - PARTICLE_MODE_RANDOM : changes probability matrix";
  	// }
  	if( key == ' ' ){
  		resetParticles();
  	}
  }

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
