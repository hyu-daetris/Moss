#include "ofMain.h"

#include "ofApp.hpp"
#include "Constant.hpp"

#include <iostream>

//========================================================================
int main( ){
    ofSetupOpenGL(Constant::WIDTH, Constant::HEIGHT, OF_WINDOW);            // <-------- setup the GL context

    std::string port;

    std::cout << "port name : ";
    std::cin >> port;

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp(port));

    return 0;
}
