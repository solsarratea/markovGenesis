#include "particle.h"
int Particle::objectCount = 0;
//------------------------------------------------------------------
Particle::Particle(int totalParticles){
	vector <int> context(totalParticles, 0);
	Particle::objectCount += 1;
}

//------------------------------------------------------------------
void Particle::setParticles( vector<glm::vec3> * all ){
	trustedParticles = all;
}

//------------------------------------------------------------------
void Particle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);

	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
  pos.z = 0;

	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
  vel.z = 0;

	frc   = glm::vec3(0,0,0);

	scale = ofRandom(0.5, 1.0);
}

//------------------------------------------------------------------
void Particle::update(){

			//1 - find closest attractPoint
			glm::vec3 closestPt;
			int closest = -1;
			float closestDist = 9999999;

			for(unsigned int i = 0; i < trustedParticles->size(); i++){
				if (context[i] == 1){
					float lenSq = glm::length2( trustedParticles->at(i)-pos );
					if( lenSq < closestDist ){
						closestDist = lenSq;
						closest = i;
					}
				}
			}

			//2 - if we have a closest point - lets calcuate the force towards it
			if( closest != -1 ){
				closestPt =trustedParticles->at(closest);
				float dist = sqrt(closestDist);

				//in this case we don't normalize as we want to have the force proportional to distance
				frc = closestPt - pos;

				vel *= ofRandom(1.0);

				//lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
				if( dist < 300 && dist > 40 && !ofGetKeyPressed('f') ){
					vel += frc * 0.003;
				}else{
					//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
					frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
					frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
					vel += frc * 0.4;
				}

			}


	//2 - UPDATE OUR POSITION

	pos += vel;


	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}

}

//------------------------------------------------------------------
void Particle::draw(){
	ofSetColor(255, 63, 180);
	ofDrawCircle(pos.x, pos.y, scale * 4.0);
}

void Particle::handleNewState(Particle a, Particle b, int state){
    switch (state) {
      case 1:
        a.context[b.id] = 0;
        b.context[a.id] = 0;
        break;
        case 2:
        a.context[b.id] = 0;
        b.context[a.id] = 1;
        break;
      case 3:
        a.context[b.id] = 1;
        b.context[a.id] = 0;
        break;
      case 4:
        a.context[b.id] = 1;
        b.context[a.id] = 1;
        break;
    }
}
