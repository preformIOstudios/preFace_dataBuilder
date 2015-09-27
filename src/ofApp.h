#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "ofxJSON.h"

using namespace ofxCv;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofVideoPlayer video;
        ofxFaceTracker tracker;
        vector<ofMesh> trackedFrames;
        float trackedScale;
        ofVec2f trackedPos;
        vector<vector<float> > trackedGestures;
        ofxJSONElement result;
        int imageIndex;
        bool imageSnapshot;
        ofImage img;
        string imageNamePrefix;
        string imageDir;
		
};
