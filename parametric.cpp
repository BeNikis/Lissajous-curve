

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <string>
#define MOUSER 10				
class ParametricShape : public sf::ConvexShape {
	std::function<sf::Vector2f(float)> XYf;
	float l , r;
	int steps;
	
	public:
	void plot() {
		setPointCount(steps);
		float step=(r-l)/(float)steps;
		const float increment=step;
		for (int i=0;i<steps;i++,step+=increment) {
			setPoint(i,XYf(step));
		};
	};
		
	
	
	int getSteps() const {return steps;};
	void setSteps(const int newsteps) {
		steps=newsteps;
		plot();
	};
	
	sf::Vector2f getInterval() const {return sf::Vector2f(l,r);};
	
	void setInterval(const sf::Vector2f& in) {
		l=in.x;
		r=in.y;
		plot();
	};
	
	void setInterval(const float lft,const float rht) {
		l=lft;
		r=rht;
		plot();
	};
	
	
	
		
	ParametricShape( std::function< sf::Vector2f(float) > xyf,int Steps=100,float interval_start=0,float interval_end=1) 
	:XYf(xyf), steps(Steps) , l(interval_start) , r(interval_end) 
		{
			setFillColor(sf::Color::Transparent);
			setOutlineColor(sf::Color::White);
			setOutlineThickness(1);
			
			plot();	
			
		};
		
	
};
		

					
					


int main(int argc, char** argv)
{
	
	sf::RenderWindow win(sf::VideoMode(800,600,32),"Closures and Lissajous curves");
	win.setFramerateLimit(10);
	sf::Event mainloop;
	
	
	std::srand(time(NULL));
	
	int steps=400;
	int a=1,b=1,mousereact=MOUSER;
	float aphase=0,bphase=0;
	sf::Text a_d("X: "+std::to_string(a)),b_d("Y: "+std::to_string(b));
	
	a_d.setPosition(0,0);
	b_d.setPosition(0,a_d.getLocalBounds().height);
	a_d.setColor(sf::Color::White);
	b_d.setColor(sf::Color::White);
	
	ParametricShape circle(([&a,&b,&bphase,&aphase](float x) {return sf::Vector2f(300*sin(a*x+3.14*aphase),300*cos(b*x+3.14*bphase));}),steps,0,6.28);
	//circle.scale(3,3);
	circle.move(400,300);
	
	
		
	
	
	while (win.isOpen()) {
		win.clear();
		while (win.pollEvent(mainloop)) {
			if (mainloop.type==sf::Event::Closed) win.close();
			if (mainloop.type==sf::Event::KeyPressed) {
				switch (mainloop.key.code) {
					case sf::Keyboard::Key::Left : {a--;circle.plot();a_d.setString("X: "+std::to_string(a));break;}
					case sf::Keyboard::Key::Right: {a++;circle.plot();a_d.setString("X: "+std::to_string(a));break;}
					case sf::Keyboard::Key::Down : {b--;circle.plot();b_d.setString("Y: "+std::to_string(b));break;}
					case sf::Keyboard::Key::Up   : {b++;circle.plot();b_d.setString("Y: "+std::to_string(b));break;}
					case sf::Keyboard::Key::Add  : {circle.setSteps(++steps);break;}
					case sf::Keyboard::Key::Subtract   : {if (steps>3) --steps;  circle.setSteps(steps);break;}
					default: break;
				};
			};
			
			if (mainloop.type==sf::Event::MouseMoved && --mousereact==0) {
				mousereact=MOUSER;
				aphase=(float)mainloop.mouseMove.x/800;
				bphase=(float)mainloop.mouseMove.y/600;
				circle.plot();
			};
			
				
			
		};
		
		
		
		
		win.draw(a_d);
		win.draw(b_d);
		win.draw(circle);
		
		//r=(r+3)%301;
		//circle.rotate((float)360/75);
		win.display();
		
		
		

		
			

		
		
	};
		
	return 0;
}
