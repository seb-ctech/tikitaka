#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    system = Tikitaka();
    system.init();
    Shader = ofShader();
    Shader.load("shader");
}

//--------------------------------------------------------------
void ofApp::update(){
    system.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(showShader){
        Shader.begin();
        passTikiTakaToShader();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        Shader.end();
    } else {
        system.display();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 32){
        showShader = !showShader;
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

void ofApp::passTikiTakaToShader(){
    Positions positions = system.getPlayerPositions();
    std::vector<glm::vec2> offense = positions.attacking;
    std::vector<glm::vec2> defense = positions.defending;
    glm::vec2 ballcarry = positions.ballcarry;
    Shader.setUniform1i("amount", offense.size());
    Shader.setUniform2f("res", (float)ofGetWidth(), (float)ofGetHeight());
    Shader.setUniform2fv("att", glm::value_ptr(offense[0]), offense.size()); // Pass the address of the first Vector entry
    Shader.setUniform2fv("def", glm::value_ptr(defense[0]), defense.size()); // Pass the address of the first Vector entry
    Shader.setUniform2f("ball", ballcarry);   
}