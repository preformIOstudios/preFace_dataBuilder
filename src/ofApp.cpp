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
    
    imageNamePrefix = "video_";
    string videoFileName = imageNamePrefix + "480";
    video.loadMovie( videoFileName + ".mov");
    tracker.setup();
    tracker.setRescale(.25);
    tracker.setIterations(100);
    tracker.setClamp(10);
    tracker.setTolerance(.5);
    tracker.setAttempts(4);
    imageIndex = 0;
    imageSnapshot = false;
    img.allocate(video.getWidth(), video.getHeight(), OF_IMAGE_COLOR);
    
    // parse the JSON
    bool parsingSuccessful = result.open("template.json");
    
    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup() -- JSON raw string =") << endl << result.getRawString() << endl;
        // now write pretty print
        if (!result.save("example_output_pretty.json", true))
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
    tracker.draw();
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
    
    if(imageSnapshot) {
        //        img.grabScreen(0, video img.getWidth(), img.getHeight());
        img.grabScreen(0, 0, video.getWidth() * scale, video.getHeight() * scale);
        //        img.grabScreen(0, 0, 640, 480);
        string imgName = imageDir + imageNamePrefix + ofToString(imageIndex) + ".png";
        img.saveImage(imgName);
        imageSnapshot = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
