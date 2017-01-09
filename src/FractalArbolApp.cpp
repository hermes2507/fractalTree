#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FractalArbolApp : public AppNative {
public:
	void setup();
	void mouseMove(MouseEvent event);
	void update();
	void draw();
	void branch(float len, float angle, float ratio);
    
    
	float len;
	int angle;
    float base;
    float ratio;
    int mode;
    int rot;
    float hueLowLimit;
    float hueHiLimit;
     ci::Vec2f posMouse;
    
	int h;
	int w;
	ci::params::InterfaceGlRef mParam;
    
};

void FractalArbolApp::branch(float len, float angle, float ratio)
{
    
    
    
	//Tronco
	gl::color(Color( CM_HSV, lmap<float>(len, 20, 200, hueLowLimit, hueHiLimit), 1, 1 ));
    gl::lineWidth(2);
	gl::drawLine(ci::Vec2f(0, 0), ci::Vec2f(0, -len));
	gl::translate(ci::Vec2f(0, -len));
    
    
	if (len<20) {
		return;
	}
	else {
		//Rama izquierda
		gl::pushMatrices();
		gl::rotate(angle);
		branch(len*ratio, angle, ratio);
		gl::popMatrices();
        
        
		//Rama Derecha
		gl::pushMatrices();
		gl::rotate(-angle);
		branch(len*ratio, angle, ratio);
		gl::popMatrices();
        
	}
    
}

void FractalArbolApp::setup()
{
    
    
    
	mParam = ci::params::InterfaceGl::create(getWindow(), "Arbol Fractal", ci::Vec2i(200, 200));
	mParam->addParam("len", &len, "");
	mParam->addParam("angle", &angle, "");
    mParam->addParam("ratio", &ratio, "max= 0.9 step=0.01");
    mParam->addParam("rot", &rot, "max= 90 step=6");
    mParam->addParam("mode", &mode, "min=0; max= 2 step=1");
    mParam->addParam("hueLowLimit", &hueLowLimit, "min=0; max= 1 step=0.01");
    mParam->addParam("hueHiLimit", &hueHiLimit, "min=0; max= 1 step=0.01");
    
	h = 768;
	w = 1024;
    
	len = 100;
	angle = 20;
    ratio = 0.85;
    mode = 0;
    rot = 45;
    hueLowLimit = 0.7;
    hueHiLimit = 0.9;
   
    
    
	setWindowSize(w, h);
	setWindowPos(500, 200);
}

void FractalArbolApp::mouseMove(MouseEvent event)
{
    posMouse = event.getPos();
    
    
}

void FractalArbolApp::update()
{
    
}

void FractalArbolApp::draw()
{
    
	//gl::clear(Color(1,1,1));
    
	gl::enableAlphaBlending();
	gl::color(0, 0, 0, 0.05);
	gl::drawSolidRect(getWindowBounds());
    
	gl::pushMatrices();
    
    
    //Modes
    switch (mode) {
        case 0:
            gl::translate(ci::Vec2f(w / 2, h/2));
            for (int i = 0; i<360; i+=rot)
            {
                gl::pushMatrices();
                gl::rotate(i);
                branch(len, angle, ratio);
                gl::popMatrices();
            }
            break;
            
        case 1:
            gl::translate(ci::Vec2f(w / 2, h));
            branch(len, angle, ratio);
            break;
        default:
            break;
    }

	gl::popMatrices();
    
	mParam->draw();
    
    
    
    
}


CINDER_APP_NATIVE(FractalArbolApp, RendererGl)
