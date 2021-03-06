#include "ofApp.h"
#include "parameter.h"

//--------------------------------------------------------------
void ofApp::setup(){
    system = Tikitaka();
    infoFont.load("Roboto-Light.ttf", 8);
    Shader = new ofShader();
    Shader->setupShaderFromFile(GL_FRAGMENT_SHADER, "shader.frag");
    Shader->linkProgram();
    posFboAtt.allocate(system.getPlayerAmountAtt(), 1, GL_RGB32F);
    posFboDef.allocate(system.getPlayerAmountDef(), 1, GL_RGB32F);
    renderImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update(){
    system.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(showShader){
        Shader->begin();
        passPositionsToShader();
        renderImage.resize(ofGetWidth(), ofGetHeight());
        renderImage.draw(0, 0);
        Shader->end();
        // infoFont.drawString(std::to_string(par2), ofGetWidth() - 100, ofGetHeight() - 20);
        // infoFont.drawString(std::to_string(par1), ofGetWidth() - 200, ofGetHeight() - 20);
    } else {
        ofFill();
        ofSetColor(200);
        infoFont.drawString(std::to_string(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
        system.Display();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int spacebar = 32;
    int arrow_up = 57357;
    int arrow_down = 57359;
    int arrow_left = 57356;
    int arrow_right = 57358;
    Parameter* parameter = system.getParameter();
    if(key == spacebar) showShader = !showShader;
    if(key == arrow_up) {
        if (showShader){
            par1 += 0.01;
        } else {
            parameter->SwitchParameter(1);
        }
    }
    if(key == arrow_down){
        if(showShader){
            par1 -= 0.01;
        } else {
            parameter->SwitchParameter(-1);
        }
    } 
    if(key == arrow_left){
        if(showShader){
            par2 -= 0.01;
        } else {
            parameter->SwitchParameterValue(-1);
        }
    } 
    if(key == arrow_right){
        if (showShader){
            par2 += 0.01;
        } else {
            parameter->SwitchParameterValue(1);
        }
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

void ofApp::passPositionsToShader(){
    Positions positions = system.getPositions();
    Shader->setUniform1i("amount", positions.attacking.size());
    Shader->setUniformTexture("tex0", renderImage.getTexture(), 0);
    BufferPositions();
    Shader->setUniformTexture("tex1", posFboAtt.getTexture(), 1);
    Shader->setUniformTexture("tex2", posFboDef.getTexture(), 2);
    Shader->setUniform2f("res", (float)ofGetWidth(), (float)ofGetHeight());
    Shader->setUniform2f("ball", positions.ball);   
    Shader->setUniform1f("v1", par1);
    Shader->setUniform1f("v2", par2);
}

void ofApp::BufferPositions(){
    Positions positions = system.getPositions();
    ofFloatPixels pixels;
    posFboAtt.readToPixels(pixels);
    for (unsigned int i = 0; i < positions.attacking.size(); i++){
        pixels[i * 3 + 0] = positions.attacking[i].x / ofGetWidth();
        pixels[i * 3 + 1] = positions.attacking[i].y / ofGetHeight();
    }
    posFboAtt.getTexture().loadData(pixels);
    posFboDef.readToPixels(pixels);
    for (unsigned int i = 0; i < positions.defending.size(); i++){
        pixels[i * 3 + 0] = positions.defending[i].x / ofGetWidth();
        pixels[i * 3 + 1] = positions.defending[i].y / ofGetHeight();
    }
    posFboDef.getTexture().loadData(pixels);
}