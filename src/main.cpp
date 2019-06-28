#include "ofMain.h"

#include "ofApp.hpp"
#include "Constant.hpp"
#include "TopMost.hpp"

#include <iostream>

//========================================================================
int main( ){
    ofWindowMode mode = Constant::FULL_SCREEN ? OF_FULLSCREEN : OF_WINDOW;
    constexpr size_t width = Constant::ROTATE ? Constant::HEIGHT : Constant::WIDTH;
    constexpr size_t height = Constant::ROTATE ? Constant::WIDTH : Constant::HEIGHT;    
    ofSetupOpenGL(width, height, mode);

    std::string port;

    std::cout << "port name : ";
    std::cin >> port;

    std::unique_ptr<TopMost::MakeTop> topper;
    if (Constant::TOP_MOST) {
        topper = std::make_unique<TopMost::MakeTop>();
    }

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp(port));

    return 0;
}
