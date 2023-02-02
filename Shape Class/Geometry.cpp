#include "Geometry.h"

// ============ Shape class =================
Shape::Shape(){

}
Shape::Shape(int d) {
	d=0;
	try{
		if(d<0)
			throw std::invalid_argument("Invalid argument.");
		depth=d;
	}
	catch(const std::invalid_argument& e ) {
    	cout<<"invalid argument exception occured."<<endl;
	}
}

bool Shape::setDepth(int d) {
	try{
		if(d<0)
			throw std::invalid_argument("Invalid argument.");
		depth=d;
	}
	catch(const std::invalid_argument& e ) {
    	cout<<"invalid argument exception occured."<<endl;
	}
}

// =============== Point class ================
Point::Point(){

}
Point::Point(float x, float y, int d){
	this->x=x;
	this->y=y;
	this->setDepth(d);
}

float Point::getX() const {
	return x;
}

float Point::getY() const {
	return y;
}

bool Point::setDepth(int d){
	return Shape::setDepth(d);
}

int Point::getDepth() const {
	return depth;
}

int Point::dim() const {
	return dimension;
}

void Point::translate(float x, float y) {
	this->x+=x;
	this->y+=y;
}

void Point::rotate() {
	//No effect
}

void Point::scale(float f){
	//No effect
}

bool Point::contains(const Point& p) const {
	return (p.x==x && p.y==y)? true : false;
}



// =========== LineSegment class ==============

LineSegment::LineSegment(const Point& p, const Point& q){
	try{
		if((p.x==q.x && p.y==q.y) || p.depth!=q.depth || p.x!=q.x || p.y!=q.y){
			throw std::invalid_argument("Invalid argument.");
		}	
		p1=p;
		p2=q;
		dimension=1;
	}
	catch( const std::invalid_argument& e ) {
    	cout<<"invalid argument exception occured."<<endl;
	}
}

bool LineSegment::setDepth(int d){
	return Shape::setDepth(d);
}

int LineSegment::getDepth() const{
	return depth;
}

int LineSegment::dim() const {
	return dimension;
}

void LineSegment::translate(float x, float y) {
	p1.translate(x,y);
	p2.translate(x,y);
}

void LineSegment::rotate() {
	//center point 
	Point p3;
	p3.x=(p1.x+p2.x)/2;
	p3.y=(p1.y+p2.y)/2;
	
	
	//move back to origin
	p1.translate(-p3.x,-p3.y);
	
	//rotate
	Point temp;
	temp.x=p1.x; temp.y=p1.y;
	p1.x=-temp.y; p2.y=temp.x;
	
	temp.x=p2.x; temp.y=p2.y;
	p2.x=-temp.y; p2.y=temp.x;
	
	//move to original position
	p1.x+=p3.x; p1.y+=p3.y;
	p2.x+=p3.x; p2.y+=p3.y;	
}

void LineSegment::scale(float f){
	try{
		if(f<=0)
			throw std::invalid_argument("Invalid argument.");
		float lenght;
		lenght=this->length();
		Point p3;
		float lenght2=lenght*f;
		lenght-=lenght2;
		lenght=lenght/2;
		if(p1.y==p2.y){
			p1.x=getXmin();
			p1.x-=lenght;
			p2.x=getXmax();
			p2.x+=lenght;
		}
		else if(p1.x==p2.x){
			p1.y=getXmin();
			p1.y-=lenght;
			p2.y=getXmax();
			p2.y+=lenght;
		}
	}
	catch( const std::invalid_argument& e ) {
    	cout<<"invalid argument exception occured."<<endl;
	}
}

bool LineSegment::contains(const Point& p) const {
	float lenght=this->length();
	float lenght1=sqrt(pow((p2.x-p.x),2)+pow((p2.y-p.y),2));
	float lenght2=sqrt(pow((p.x-p1.x),2)+pow((p.y-p1.y),2));
	return (lenght==lenght1+lenght2)? true : false;
}


float LineSegment::getXmin() const {
	if(p1.x<=p2.x)
		return p1.x;
	else
		return p2.x;
}

float LineSegment::getXmax() const {
	if(p1.x>=p2.x)
		return p1.x;
	else
		return p2.x;
}

float LineSegment::getYmin() const {
	if(p1.y<=p2.y)
		return p1.y;
	else
		return p2.y;
}

float LineSegment::getYmax() const {
	if(p1.y>=p2.y)
		return p1.y;
	else
		return p2.y;
}

float LineSegment::length() const {
	return (sqrt(pow((p2.x-p1.x),2))+pow((p2.y-p1.y),2));
}

// ============ TwoDShape class ================
TwoDShape::TwoDShape(){

}
TwoDShape::TwoDShape(int d) {
	this->setDepth(d);
}

// ============== Rectangle class ================

Rectangle::Rectangle(const Point& p, const Point& q) {
	try{
		if((p.x==q.x && p.y==q.y) || (p.x==q.x && p.y!=q.y) || (p.y==q.y && p.x!=q.x) || p.depth!=q.depth){
			throw std::invalid_argument("Invalid argument.");
		}	
		p1=p;
		p2=q;
		p3.x=p2.x; p3.y=p1.y;
		p4.x=p1.x; p4.y=p2.y;
		dimension=2;
	}
	catch( const std::invalid_argument& e ) {
    	cout<<"invalid argument exception occured."<<endl;
	}
}

float Rectangle::area() const{
	float lenght=sqrt(pow((p2.x-p3.x),2)+pow((p2.y-p3.y),2));
	float width=sqrt(pow((p2.x-p4.x),2)+pow((p2.y-p4.y),2));
	return (lenght*width);
}
	

float Rectangle::getXmin() const {
	if(p1.x<=p2.x)
		return p1.x;
	else
		return p2.x;
}

float Rectangle::getYmin() const {
	if(p1.y<=p2.y)
		return p1.y;
	else
		return p2.y;
}

float Rectangle::getXmax() const {
	if(p1.x>=p2.x)
		return p1.x;
	else
		return p2.x;
}

float Rectangle::getYmax() const {
	if(p1.y>=p2.y)
		return p1.y;
	else
		return p2.y;
}

bool Rectangle::setDepth(int d){
	return Shape::setDepth(d);
}

int Rectangle::getDepth() const{
	return depth;
}

int Rectangle::dim() const {
	return dimension;
}

void Rectangle::translate(float x, float y) {
	p1.translate(x,y);
	p2.translate(x,y);
	p3.translate(x,y);
	p4.translate(x,y);
}

void Rectangle::rotate() {
	
	float lenght;
	
	//center point 
	Point c;
	c.x=(p1.x+p2.x)/2;
	c.y=(p1.y+p2.y)/2;
	lenght=sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2));
	lenght=lenght/2;
	
	//move to origin
	p1.x=0-c.x; p1.y=0-c.y;
	p2.x=0+c.x; p2.y=0+c.y;
	p3.x=0+c.x; p3.y=0-c.y;
	p4.x=0-c.x; p4.y=0+c.y;
	
	//rotating
	float temp=p1.x;
	p1.x=p1.y; p1.y=-temp;
	temp=p2.x;
	p2.x=p2.y; p2.y=-temp;
	temp=p3.x;
	p3.x=p3.y; p3.y=-temp;
	temp=p4.x;
	p4.x=p4.y; p4.y=-temp;
	
	//move back to original position
		//remaining
}

void Rectangle::scale(float f){
		LineSegment l1(p1,p3);
		LineSegment l2(p1,p4);
		LineSegment l3(p2,p3);
		LineSegment l4(p2,p4);
		l1.scale(f);
		l2.scale(f);
		l3.scale(f);
		l4.scale(f);
}

bool Rectangle::contains(const Point& p) const {
	return (p.x>p1.x && p.x<p2.x && p.y>p1.y && p.y<p2.y)? true : false;
}

// ================== Circle class ===================

Circle::Circle(const Point& c, float r) {
	try{
		if(r<=0){
			throw std::invalid_argument("Invalid argument.");
		}	
		p1=c;
		radius=r;
		dimension=2;
	}
	catch( const std::invalid_argument& e ) {
    	cout<<"invalid argument exception occured."<<endl;
	}
}

float Circle::area() const{
	return (radius*3.1415926);
}

float Circle::getX() const {
	return p1.x;
}

float Circle::getY() const {
	return p1.y;
}

float Circle::getR() const {
	return radius;
}

bool Circle::setDepth(int d){
	return Shape::setDepth(d);
}

int Circle::getDepth() const{
	return depth;
}

int Circle::dim() const {
	return dimension;
}

void Circle::scale(float f){
	try{
		if(f<=0)
			throw std::invalid_argument("Invalid argument.");
		radius*f;
	}
	catch( const std::invalid_argument& e ) {
		cout<<"invalid argument exception occured."<<endl;
	}
}

bool Circle::contains(const Point& p) const {
	LineSegment l1(p1,p);
	float lenght;
	lenght=l1.length();
	return (lenght<radius)? true : false;	
}


void Circle::translate(float x, float y) {
	p1.translate(x,y);
}

void Circle::rotate() {
	//NULL
}

// ================= Scene class ===================

Scene::Scene() {
}

void Scene::addObject(shared_ptr<Shape> ptr) {
	//scene.push_back(make_shared<Shape> ptr); 
}

void Scene::setDrawDepth(int depth) {
	// IMPLEMENT ME
}

ostream& operator<<(ostream& out, const Scene& s) {
	cout << "Hello Peter"<<endl;
	return out;
}


