#include "curve.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace curves{

	Point::Point(double x, double y){
		_x = x;
		_y = y;
	}
	Point::~Point(){

	}
	void Point::setX(double x){
		this->_x = x;
	}

	void Point::setY(double y){
		this->_y = y;
	}

	double Point::getX(){
		return this->_x;
	}

	double Point::getY(){
		return this->_y;
	}

	double Point::distance(Point &point){
		return
				std::sqrt(
						std::pow((point.getX() - _x) * (point.getX() - _x),2) +
						std::pow((point.getY() - _y) * (point.getY() - _y),2)

				);
	}

	Point Conchoid::getCenter(){
		try{
			return Point(_a/2, yFromX(_a/2));
		}
		catch(...){
			throw "Cannot find center";
		}
	}

	double Conchoid::getA(){
		return this->_a;
	}

	double Conchoid::getL(){
		return this->_l;
	}

	void Conchoid::setA(double a){
		this->_a = a;
	}

	void Conchoid::setL(double l){
		this->_l = l;
	}

	Conchoid::Conchoid(double a, double l){
		this->_a = a;
		this->_l = l;
	}

	Conchoid::Conchoid(){
		Conchoid(0,0);
	}

	Conchoid::~Conchoid(){
	}

	double Conchoid::yFromX(double x){
		double y;
		try{
			y = -((_a - _l -x)*(_a + _l - x) * std::pow(x,2)/std::pow(_a-x,2));
			y = std::sqrt(y);
		}
		catch(...){
			throw "Negative squre";
		}
		return y;
	}

	double Conchoid::distanceFromCenter(double phi){
		try{
			double r = this->_a / std::cos(phi) + this->_l;
			Point pointFromAngle = Point(r * std::cos(phi), r * std::sin(phi));
			Point center = this->getCenter();
			return pointFromAngle.distance(center);
		}
		catch(...){
			throw "Cannot find distance from center to point";
		}
	}

	double Conchoid::radiusOfCurvature(){
		if( this->_l < this->_a){
			throw "Cannot find radius";
		}
		if( this->_l == this->_a){
			return 0;
		}
		return std::sqrt(
				std::abs(
						std::pow(_l,2) - std::pow(_a,2) +
						_a * _l - _a * _a - _l *_l +
						3/2 * std::pow(_a, 3/2) + 7/4 * std::pow(_l, 3/4)
				)
		);
	}

	double Conchoid::loopArea(){
		try{
			double radius = radiusOfCurvature();
			Point center = getCenter();
			return radius * std::sqrt(
					std::abs(
							std::pow(std::abs(center.getX()),3/2) +
							std::pow(std::abs(center.getY()),3/2) +
							2 * center.getX() * center.getY()
					)
			);
		}
		catch(...){
			throw "Cannot find loop area";
		}
	}
}

struct TestConchoid : testing::Test{
  curves::Conchoid *c;
  TestConchoid() {
    c = new curves::Conchoid(2,5);
  }
  ~TestConchoid() {
    delete c;
  }
};

TEST_F(TestConchoid, yFromX){
  EXPECT_DOUBLE_EQ(c->yFromX(1.3), 9.1942639616185904);
  EXPECT_DOUBLE_EQ(c->yFromX(2.3), 38.264271121301206);
  EXPECT_DOUBLE_EQ(c->yFromX(0.3), 0.82978714909473505);
}
TEST_F(TestConchoid, loopArea){
  EXPECT_DOUBLE_EQ(c->loopArea(), 8.8591586667976188);
}
TEST_F(TestConchoid, radiusOfCurvature){
  EXPECT_DOUBLE_EQ(c->radiusOfCurvature(), 2.2360679774997898);
}
TEST_F(TestConchoid, distanceFromCenter){
  EXPECT_DOUBLE_EQ(c->distanceFromCenter(1.5), 800.40175307819607);
}

