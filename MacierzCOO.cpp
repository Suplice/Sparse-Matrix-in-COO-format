#include <iostream>
#include "macierz.h"
int main(int argc, char** argv)
{
	
	Macierz M_a(4, 2);
	Macierz M_b(5, 5);
	Macierz M_c(4, 2);

	M_a.set_Value(5.3, 1, 1);
	M_a.set_Value(2.12, 2, 1);
	M_a.set_Value(17, 2, 0);

	M_b.set_Value(1.2, 0, 0);
	M_b.set_Value(3.6, 1, 4);
	M_b.set_Value(4, 2, 3);
	
	M_c.set_Value(13.3, 3, 1);
	M_c.set_Value(5.2, 1, 1);
	M_c.set_Value(5.3, 3, 0);

	Macierz M_d = M_c.dod(M_a);

	std::cout << "Macierz M_a: \n";
	M_a.get_Values();
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Macierz M_C: \n";
	M_c.get_Values();
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << "Wynik dodawania macierzy (M_a + M_c): \n";
	M_d.get_Values();
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << "Wynik odejmowania macierzy (M_a - M_c): \n";
	M_d = M_a.ode(M_c);
	M_d.get_Values();

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Macierz M_b: \n";
	M_b.get_Values();
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << "Transponowanie macierzy M_b: \n";
	M_b = M_b.Transpon();
	M_b.get_Values();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;


	std::cout << "Transponowana Macierz M_c: \n";
	std::cout << std::endl;
	M_c = M_c.Transpon();
	M_c.get_Values();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "mnozenie Macierzy (M_a * Transpon(M_c)): \n";
	std::cout << std::endl;
	std::cout << std::endl;
	M_d = M_a.mnoz(M_c);
	M_d.get_Values();
	

} 

