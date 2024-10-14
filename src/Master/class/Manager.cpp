#include <exceptions>
#include <fstream>
#include <iostream>
#include "Master.class.hpp"

using namespace std;

Master::Master() {
	cout << "Init server" << std::endl;
}

Master::~Master() {
	cout << "Interrupt server" << std::endl;
}
