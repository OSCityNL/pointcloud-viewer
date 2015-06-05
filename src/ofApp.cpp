#include "ofApp.h"

const int MAX_POINTS = 5000000;
const int CHECK_NUM_POINTS = 10000;
const string FILENAME = "pc.txt"; // pc.txt

ofIndexType vi[MAX_POINTS];
ofVec3f v[MAX_POINTS];
ofFloatColor c[MAX_POINTS];

int NUM_POINTS = 0;


//--------------------------------------------------------------
void ofApp::setup(){

    // --- open file
    ofFile file;
    file.open(FILENAME); // open the XYZ file

    if(!file.exists()){
        cout << "geomLayer::loadXYZ => no such file found: " << FILENAME << endl;
        // TODO: handle the error
        ofExit();
    }

    if(!file.canRead())
    {
        cout << "geomLayer::loadXYZ => can't read file: " << FILENAME << endl;
        // TODO: handle the error
        ofExit();
    }

    // ---- main loop: read lines, save coordinates and track min/max

    int i = 0;
    int m = 0;
    float minX = 9999999;
    float maxX = -9999999;
    float minY = 9999999;
    float maxY = -9999999;

    string line;


    while(file.get() != EOF)
    {
        getline(file, line);

        vector<string> coords = ofSplitString(line, " ");

        float x = ofToFloat(coords[0]); // - 136881.84 - 2500.0 + 19250.0;
        float y = ofToFloat(coords[1]); //- 487500.0 - 2500.0 + 3500.0;
        float z = ofToFloat(coords[2]); // * 1.0;


        //cout << "x: " << setprecision(10) << x << " y: " << y << " z: " << z << endl;
        if (m == CHECK_NUM_POINTS){

            if (x < minX)
                minX = x;
            if (x > maxX)
                maxX = x;
            if (y < minY)
                minY = y;
            if (y > maxY)
                maxY = y;

            cout << ofToString(i) + "/" +  ofToString(MAX_POINTS) << endl;
            m = 0;
        }

        vi[i] = i; // indices

        // colors: from blue to yellow
        c[i].r = ofMap(z, -5.0, 20.0, 0.0, 1.0);
        c[i].g = ofMap(z, 10.0, 20.0, 0.0, 1.0);
        c[i].b = ofMap(z, -5.0, 20.0, 0.5, 0.1);;

        // coordinates
        v[i][0] = x;
        v[i][1] = y;
        v[i][2] = z;

        // iteration
        i++;
        m++;

        // reach max of points
        if (i >= MAX_POINTS){
            break;
        }

    }

    NUM_POINTS = i;

    // center cloud
    float centerX  = (maxX - minX)/2.0 + minX;
    float centerY  = (maxY - minY)/2.0 + minY ;

    cout << "x: [" << setprecision(10) << minX << "-" << maxX << "] y: [" << minY << "-" << maxY << "]" << endl;
    cout << "center: [ " << centerX << "," << centerY << endl;

    for (int p = 0; p < NUM_POINTS; p++)
    {
        v[p][0] -= centerX;
        v[p][1] -= centerY;
    }

    // ---

    vbo.setVertexData( &v[0], NUM_POINTS, GL_STATIC_DRAW );
    vbo.setColorData( &c[0], NUM_POINTS, GL_STATIC_DRAW );
    vbo.setIndexData( &vi[0], NUM_POINTS, GL_STATIC_DRAW );

    //glEnable(GL_DEPTH_TEST);
    ofEnableDepthTest();
    glPointSize(2.0);
    cam = ofEasyCam();
    ofSetVerticalSync(true);
    glEnable(GL_POINT_SMOOTH);

    ofBackground(0,0,0);
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();

    vbo.drawElements( GL_POINTS, NUM_POINTS);

    ofSetWindowTitle(ofToString(ofGetFrameRate()));

    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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




