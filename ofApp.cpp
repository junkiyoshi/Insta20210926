#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int base_len = 100;
	int number_of_satellite = 380;
	int number_of_log = 25;

	auto base_noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	auto base_location = glm::vec3(ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -250, 250), ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -250, 250), 0);

	ofPushMatrix();
	ofTranslate(base_location);
	ofRotateY(ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -360, 360));
	ofRotateX(ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -360, 360));

	ofFill();
	ofSetColor(39);
	ofDrawBox(glm::vec3(), base_len * 0.85);

	ofNoFill();
	ofSetColor(239);
	ofDrawBox(glm::vec3(), base_len * 0.85 + 0.1);

	ofPopMatrix();

	for (int i = 0; i < number_of_satellite; i++) {

		float noise_seed_x = ofRandom(1000);
		float noise_seed_y = ofRandom(1000);
		auto location = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		location = glm::normalize(location) * base_len * 1.25;
		auto prev_location = glm::vec3();

		for (int k = 0; k < number_of_log; k++) {

			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + k) * 0.001), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + k) * 0.001), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
			auto tmp_base_location = glm::vec3(ofMap(ofNoise(base_noise_seed.x, (ofGetFrameNum() + k) * 0.005), 0, 1, -250, 250), ofMap(ofNoise(base_noise_seed.y, (ofGetFrameNum() + k) * 0.005), 0, 1, -250, 250), 0);
			auto draw_location = tmp_base_location + glm::vec4(location, 0) * rotation_y * rotation_x;

			if (k > 0) {

				ofSetLineWidth(0.5);
				ofSetColor(ofColor(39, ofMap(k, 0, number_of_log, 32, 255)));
				ofDrawLine(prev_location, draw_location);
			}

			prev_location = draw_location;
		}

		ofPushMatrix();
		ofTranslate(prev_location);
		ofRotateY(ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -PI * 2 * RAD_TO_DEG, PI * 2 * RAD_TO_DEG));
		ofRotateX(ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -PI * 2 * RAD_TO_DEG, PI * 2 * RAD_TO_DEG));
		
		ofSetLineWidth(1.5);

		ofFill();
		ofSetColor(239);
		ofDrawBox(glm::vec3(), base_len * 0.15);

		ofNoFill();
		ofSetColor(39);
		ofDrawBox(glm::vec3(), base_len * 0.15 + 0.1);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}