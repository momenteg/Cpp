#include <Eigen/Dense>
#include <iostream>
#include <string>

using Eigen::MatrixXd;

template <class T>

void print(std::string string_, T quantity){
	std::cout << string_  << std::endl;
	std::cout << quantity << std::endl;
}

int main(){

	MatrixXd m(4,2), c;
	m << 3, 2.5,
		1, 10,
		6, 9,
		5.7, 1.86;

  print< decltype(m)/*Eigen::MatrixXd*/>("first matrix  ", m);
	print< decltype(m.cols())>("number of cols", m.cols());
	print< decltype(m.prod())>("prod", m.prod());
	print< decltype(m.transpose()) >("Transpose matrix  ", m.transpose());
	print< decltype(m.array().sqrt()) >("apply sqrt to each elem of the matrix", m.array().sqrt());

	print< decltype(m.transpose()*m) >("Inner product matrix", m.transpose()*m);
	print< decltype((m.transpose()*m).transpose()) >("Transpose of the inner product matrix", (m.transpose()*m).transpose());

  return 0;
}

