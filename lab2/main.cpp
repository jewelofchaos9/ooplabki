#include <iostream>
#include "curve.hpp"

curves::Conchoid newConchoid(){
	std::cout << "Enter a and l for conchoid\n>";
	double a,l;
	std::cin >> a >> l;
	return curves::Conchoid(a,l);
}

[[noreturn]] void menu(){
	char menu[] = "\
          [1] get a\n\
          [2] get l\n\
          [3] set a\n\
          [4] set l\n\
          [5] y from x\n\
          [6] distance from center with angle\n\
          [7] radius of curvature\n\
          [8] loop area\n\
          [9] new conchoid\n>";
	curves::Conchoid conchoid = newConchoid();
	int choice;
	while(true){
		std::cout << menu;
		std::cin >> choice;
		switch(choice){
			case 1:
				std::cout << conchoid.getA();
				break;
			case 2:
				std::cout << conchoid.getL();
				break;
			case 3:
				double newA;
				std::cin >> newA;
				conchoid.setA(newA);
				break;
			case 4:
				double newL;
				std::cin >> newL;
				conchoid.setL(newL);
				break;
			case 5:
				double x;
				std::cin>>x;
				try{
					std::cout << conchoid.yFromX(x);
				}
				catch(...){
					std::cout << "Unlucky\n";
				}
				break;
			case 6:
				double phi;
				std::cin >> phi;
				try{
					std::cout << conchoid.distanceFromCenter(phi);
				}
				catch(...){
					std::cout << "Unlucky\n";
				}
				break;
			case 7:
				try{
					std::cout << conchoid.radiusOfCurvature();
				}
				catch(...){
					std::cout << "Unlucky\n";
				}
				break;
			case 8:
				try{
					std::cout << conchoid.loopArea();
				}
				catch(...){
					std::cout << "Unlucky\n";
				}
				break;
			case 9:
				conchoid = newConchoid();
				break;
		}
	}
}
int main(){
	menu();
	return 0;
}

