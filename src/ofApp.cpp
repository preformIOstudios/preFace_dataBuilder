#include "ofApp.h"

ofxFaceTracker::Gesture gestureIds[] = {
    ofxFaceTracker::MOUTH_WIDTH,
    ofxFaceTracker::MOUTH_HEIGHT,
    ofxFaceTracker::LEFT_EYEBROW_HEIGHT,
    ofxFaceTracker::RIGHT_EYEBROW_HEIGHT,
    ofxFaceTracker::LEFT_EYE_OPENNESS,
    ofxFaceTracker::RIGHT_EYE_OPENNESS,
    ofxFaceTracker::JAW_OPENNESS,
    ofxFaceTracker::NOSTRIL_FLARE
};

string gestureNames[] = {
    "mouthWidth",
    "mouthHeight",
    "leftEyebrowHeight",
    "rightEyebrowHeight",
    "leftEyeOpenness",
    "rightEyeOpenness",
    "jawOpenness",
    "nostrilFlare"
};

int gestureCount = 8;

//--------------------------------------------------------------
void ofApp::setup(){
    cout << "Hello World!" << endl;
    
    imageDir = "images";
    imageNamePrefix = "christian_DSC_0176_";
    string videoFileName = imageNamePrefix + "480";
    video.loadMovie( videoFileName + ".mov");
    tracker.setup();
    tracker.setRescale(.9);
    tracker.setIterations(2);
    tracker.setClamp(30);
    tracker.setTolerance(5);
    tracker.setAttempts(1);
    imageIndex = 0;
    imageSnapshot = false;
    img.allocate(video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if(video.isFrameNew()) {
        tracker.update(toCv(video));
        
        // da È START
        if (trackedFrames.size()) trackedFrames[0] = tracker.getImageMesh();
        else trackedFrames.push_back(tracker.getImageMesh());
        // da È END
        
        vector<float> curGesture;
        for(int i = 0; i < gestureCount; i++) {
            curGesture.push_back(tracker.getGesture(gestureIds[i]));
        }
        // da È START
        if (trackedGestures.size()) trackedGestures[0] = curGesture;
        else trackedGestures.push_back(curGesture);
        // da È END
        
        video.nextFrame();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float scale = ofGetWidth() / video.getWidth();
    if ((ofGetHeight() / video.getHeight()) < scale) scale = ofGetHeight() / video.getHeight();
    ofScale(scale, scale);
    video.draw(0, 0);
    ofSetLineWidth(2);
    
    // save snapshot without debug lines
    if(imageSnapshot) {
        img.grabScreen(0, 0, video.getWidth() * scale, video.getHeight() * scale);
        string imgName = imageDir + "/" + imageNamePrefix + ofToString(imageIndex) + ".png";
        img.saveImage(imgName);
    }

    
    tracker.draw();
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    // save debug snapshot
    if(imageSnapshot) {
        img.grabScreen(0, 0, video.getWidth() * scale, video.getHeight() * scale);
        string imgName = imageDir + "/" + imageNamePrefix + ofToString(imageIndex) + "_d.png";
        img.saveImage(imgName);
        
        // reset snapshot flag for next update() call
        imageSnapshot = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        imageIndex ++;
        imageSnapshot = true;
        
        // parse the JSON
        bool parsingSuccessful = result.open("template.json");
        
        if (parsingSuccessful)
        {

//            ofFile out(imageDir + "/" + imageNamePrefix + ofToString(imageIndex) + ".json", ofFile::WriteOnly);

            for(int i = 0; i < trackedFrames.size(); i++) {
                for(int j = 0; j < gestureCount; j++) {
                    result[gestureNames[j]] = trackedGestures[i][j];
                }
                for(int j = 0; j < trackedFrames[i].getNumVertices(); j++) {
                    // result["vertices"][j] = ofVec2f(trackedFrames[i].getVertex(j));
                }
                result["scale"] = tracker.getScale();
                result["posX"] = tracker.getPosition().x;
                result["posY"] = tracker.getPosition().y;
            }

            ofLogNotice("ofApp::setup() -- JSON raw string =") << endl << result.getRawString() << endl;

            // now write pretty print
            if (!result.save(imageDir + "/" + imageNamePrefix + ofToString(imageIndex) + ".json", true))
            {
                ofLogNotice("ofApp::setup") << "example_output_pretty.json written unsuccessfully.";
            }
            else
            {
                ofLogNotice("ofApp::setup") << "example_output_pretty.json written successfully.";
            }
        }
        else
        {
            ofLogError("ofApp::setup")  << "Failed to parse JSON" << endl;
        }

    }
    if(key == 'f' || key == 'F') {
        ofToggleFullscreen();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
