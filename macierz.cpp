#include <iostream>
#include "macierz.h"

//konstruktor na bazie
//tablicy elementow
Macierz::Macierz(float** Values, int rows, int columns) :
m_Row_Size(rows), m_Col_Size(columns), m_nnz(0),
m_Value(new float[rows*columns]),
m_Row(new size_t[rows*columns]),
m_Col(new size_t[rows*columns])
{
	//czy udalo sie zadeklarowac pamiec
	if (m_Value != nullptr && m_Col != nullptr && m_Row != nullptr) {

		int _pom = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (Values[i][j] != 0) {
					m_Value[_pom] = Values[i][j];
					m_Row[_pom] = i;
					m_Col[_pom] = j;
					_pom++;
					m_nnz++;
				}
			}
		}
	}
	else
	{
		//po nieudanej probie zaalokowania
		//pamieci usuwamy wszystko aby 
		//uniknac wyciekow
		std::cout << "failed to allocate memory";
		delete[] m_Value;
		delete[] m_Col;
		delete[] m_Row;

		m_Row = nullptr;
		m_Value = nullptr;
		m_Col = nullptr;
	}
};


//konstruktor bez-elementowy
Macierz::Macierz(int rows, int columns) : m_Row_Size(rows), m_Col_Size(columns), m_nnz(0),
m_Value(new float[rows * columns]),
m_Row(new size_t[rows * columns]),
m_Col(new size_t[rows * columns]) {

	//czy udalo sie zadeklarowac pamiec
	if (m_Value == nullptr || m_Row == nullptr || m_Col == nullptr)
	{
		//po nieudanej probie zaalokowania
		//pamieci usuwamy wszystko aby 
		//uniknac wyciekow
		std::cout << "failed to allocate memory";
		delete[] m_Value;
		delete[] m_Col;
		delete[] m_Row;

		m_Row = nullptr;
		m_Value = nullptr;
		m_Col = nullptr;
	}
};


//konstruktor kopiujacy
Macierz::Macierz(Macierz& other) : m_Row_Size(other.m_Row_Size), m_Col_Size(other.m_Col_Size), m_nnz(other.m_nnz),
m_Value(new float[other.m_Row_Size * other.m_Col_Size]),
m_Row(new size_t[other.m_Row_Size * other.m_Col_Size]),
m_Col(new size_t[other.m_Row_Size * other.m_Col_Size])
{
	//czy udalo sie zadeklarowac pamiec
	if (m_Value != nullptr && m_Col != nullptr && m_Row != nullptr) {
		for (int i = 0; i < other.m_Row_Size * other.m_Col_Size; i++)
		{
			m_Value[i] = other.m_Value[i];
			m_Col[i] = other.m_Col[i];
			m_Row[i] = other.m_Row[i];
		}

	}
	else
	{
		//po nieudanej probie zaalokowania
		//pamieci usuwamy wszystko aby 
		//uniknac wyciekow
		std::cout << "failed to allocate memory\n";
		delete[] m_Value;
		delete[] m_Row;
		delete[] m_Col;

		m_Row = nullptr;
		m_Value = nullptr;
		m_Col = nullptr;
	}
}


//konstruktor przenoszacy
Macierz::Macierz(Macierz&& other) noexcept : m_Row_Size(other.m_Row_Size), m_Col_Size(other.m_Col_Size), m_nnz(other.m_nnz),
m_Value(new float[other.m_Row_Size * other.m_Col_Size]),
m_Row(new size_t[other.m_Row_Size * other.m_Col_Size]),
m_Col(new size_t[other.m_Row_Size * other.m_Col_Size]) 
{
	if (this != &other) {

		//czy udalo sie zadeklarowac pamiec
		if (m_Value != nullptr && m_Row != nullptr && m_Col != nullptr) {

			for (int i = 0; i < m_nnz; i++)
			{
				m_Value[i] = other.m_Value[i];
				m_Col[i] = other.m_Col[i];
				m_Row[i] = other.m_Row[i];
			}

			other.m_Col_Size = 0;
			other.m_nnz = 0;
			other.m_Row_Size = 0;

			delete[] other.m_Value;
			delete[] other.m_Row;
			delete[] other.m_Col;

			other.m_Value = nullptr;
			other.m_Col = nullptr;
			other.m_Row = nullptr;
		}
		else
		{
			//po nieudanej probie zaalokowania
			//pamieci usuwamy wszystko aby 
			//uniknac wyciekow
			std::cout << "failed to allocate memory\n";
			delete[] m_Row;
			delete[] m_Value;
			delete[] m_Col;

			m_Row == nullptr;
			m_Value == nullptr;
			m_Col == nullptr;
		}
	}

}


//destruktor
Macierz::~Macierz() {
	delete[] m_Value;
	delete[] m_Row;
	delete[] m_Col;
}



//funkcja dodajaca inna
//macierz do naszej
Macierz Macierz::dod(Macierz &M_other)
{

	Macierz res(*this);
	//ilosc kolumn i wierszy musi byc taka sama
	if (m_Col_Size == M_other.m_Col_Size && m_Row_Size == M_other.m_Row_Size)
	{
		//jezeli druga macierz skonstruowana jest tylk o z zer
		if (M_other.m_nnz == 0)
			return *this;

		//pêtla poszukuj¹ca elementów na tych samych indeksach
		for (int i = 0; i < this->m_nnz; i++)
		{
			for (int j = 0; j < M_other.m_nnz; j++)
			{
				
				//poszukiwanie elementow ustawionych
				//w tym samym wierszu i kolumnie
				if (this->m_Row[i] == M_other.m_Row[j] && this->m_Col[i] == M_other.m_Col[j])
				{
					
					//sprawdzenie czy wartosc jest zerem
					if (this->m_Value[i] + M_other.m_Value[j] != 0)
					{
						res.m_Value[i] = this->m_Value[i] + M_other.m_Value[j];
						break;
					}
					else
					{
						res.m_Value[i] = res.m_Value[res.m_nnz - 1];
						res.m_Row[i] = res.m_Row[res.m_nnz - 1];
						res.m_Col[i] = res.m_Col[res.m_nnz - 1];
						res.m_Value[res.m_nnz - 1] = 0;
						res.m_Col[res.m_nnz - 1] = 0;
						res.m_Row[res.m_nnz - 1] = 0;
						i--;
						res.m_nnz--;
						break;

					}
					

				}
			}
		}
		
		//uzupelnie o elementy ktore
		//nie znalazly sie w pierwszej macierzy
		for (int i = 0; i < M_other.m_nnz; i++)
		{
			bool found = false;
			for (int j = 0; j < this->m_nnz; j++)
			{
				if(this->m_Row[j] == M_other.m_Row[i] && this->m_Col[j] == M_other.m_Col[i])
				{
					found = true;
				}
			}

			//jesli element nie zostal znaleziony
			//dodajemy go do macierzy wynikowej
			if (!found)
			{
				res.m_Value[res.m_nnz] = M_other.m_Value[i];
				res.m_Col[res.m_nnz] = M_other.m_Col[i];
				res.m_Row[res.m_nnz] = M_other.m_Row[i];
				res.m_nnz++;
			}
		}
		
		
		//sortujemy macierz wzgledem wierszy
		sort_Row(res);
		return res;
	}
	else
	{
		std::cout << "nie mozna dodac macierzy\n";
		return *this;
	}
	
	
}


//funkcja odejmujaca inna
//macierz od naszej
Macierz Macierz::ode(Macierz& M_other)
{

	Macierz res(*this);

	if (m_Col_Size == M_other.m_Col_Size && m_Row_Size == M_other.m_Row_Size)
	{
		//jezeli druga macierz skonstruowana jest tylk o z zer
		if (M_other.m_nnz == 0)
			return *this;

		//pêtla poszukuj¹ca elementów na tych samych indeksach
		for (int i = 0; i < this->m_nnz; i++)
		{
			for (int j = 0; j < M_other.m_nnz; j++)
			{

				//poszukiwanie elementow ustawionych
				//w tym samym wierszu i kolumnie
				if (this->m_Row[i] == M_other.m_Row[j] && this->m_Col[i] == M_other.m_Col[j])
				{
					//sprawdzenie czy wartosc jest zerem
					if (this->m_Value[i] + M_other.m_Value[i] != 0)
					{
						res.m_Value[i] = this->m_Value[i] - M_other.m_Value[j];
						break;
					}
					else
					{
						res.m_Value[i] = res.m_Value[res.m_nnz - 1];
						res.m_Row[i] = res.m_Row[res.m_nnz - 1];
						res.m_Col[i] = res.m_Col[res.m_nnz - 1];
						res.m_Value[res.m_nnz - 1] = 0;
						res.m_Col[res.m_nnz - 1] = 0;
						res.m_Row[res.m_nnz - 1] = 0;
						i--;
						res.m_nnz--;
						break;

					}
				}
			}
		}


			//uzupelnie o elementy ktore
			//nie znalazly sie w pierwszej macierzy
			for (int i = 0; i < M_other.m_nnz; i++)
			{
				bool found = false;
				for (int j = 0; j < this->m_nnz; j++)
				{
					if (this->m_Row[j] == M_other.m_Row[i] && this->m_Col[j] == M_other.m_Col[i])
					{
						found = true;
					}
				}


				//jesli element nie zostal znaleziony
				//dodajemy go do macierzy wynikowej
				if (!found)
				{
					res.m_Value[res.m_nnz] = -1 * M_other.m_Value[i];
					res.m_Col[res.m_nnz] = M_other.m_Col[i];
					res.m_Row[res.m_nnz] = M_other.m_Row[i];
					res.m_nnz++;
				}
			}



		

	//sortujemy macierz wzgledem wierszy
	sort_Row(res);
	return res;

	}
	else
	{
		std::cout << "nie mozna odjac macierzy\n";
		return *this;
	}
}





//funkcja transponujaca macierz
Macierz Macierz::Transpon() {
	
	Macierz res(*this);
	int buf = 0;
	//zamiana ilosci kolumn z rzedami
	buf = res.m_Col_Size;
	res.m_Col_Size = res.m_Row_Size;
	res.m_Row_Size = buf;
	
	//zamiana rzêdu z kolumn¹
	for (int i = 0; i < res.m_nnz; i++)
	{
		buf = res.m_Col[i];
		res.m_Col[i] = res.m_Row[i];
		res.m_Row[i] = buf;
	}
	return res;
}


//funkcja mnozaca inna
//macierz z nasza (this * M_Other)
Macierz Macierz::mnoz(Macierz& M_other) {

	
	//liczba wierszy musi byc rowna
	//liczbie kolumnd drugiej macierzy
	if (this->m_Row_Size == M_other.m_Col_Size)
	{
		//sortujemy macierze aby 
		//ulatwic obliczenia
		sort_Row(*this);
		sort_Col(M_other);

		Macierz res(m_Row_Size, M_other.m_Col_Size);

		int first_start_id = 0;
		int first_end_id = 0;
		int second_start_id = 0;
		int second_end_id = 0;



		for (int i = 0; i < m_Row_Size; i++)
		{
			for (int j = 0; j < M_other.m_Col_Size; j++)
			{
				float val = 0;

				//ustawiamy indeksy pokazujace
				//gdzie zaczynaja i koncza sie
				//elementy w aktualnym rzedzie
				//i kolumnie w obu macierzach
				first_start_id = Start_col_id(i);
				first_end_id = End_col_id(i);
				second_start_id = Start_row_id(j, M_other);
				second_end_id = End_row_id(j, M_other);

				//jesli rzad lub kolumna skonstruowana
				//jest tylko z zer pomijamy mnozenie
				if (first_start_id == -1 || second_start_id == -1)
					continue;

				//petla sprawdzajaca czy indeksy
				//nie doszly do konca
				while (first_start_id <= first_end_id && second_start_id <= second_end_id) {
					//jezeli indeks kolumny jest zgodny 
					//z indeksem wiersza drugiej macierzy
					//dokonujemy mnozenia
					if (m_Col[first_start_id] == M_other.m_Row[second_start_id])
					{
						val += m_Value[first_start_id] * M_other.m_Value[second_start_id];
						first_start_id++;
						second_start_id++;
					}
					//jezeli indeks jest mniejszy to
					//zwiekszamy go o jeden
					else if (m_Col[first_start_id] < M_other.m_Row[second_start_id])
					{
						first_start_id++;
					}
					//jezeli indeks jest mniejszy to
					//zmniejszamy go o jeden
					else 
					{
						second_start_id++;
					}
				}

				//sprawdzamy czy wynik 
				//jest rozny od zera
				if (val != 0) {
					res.m_Value[res.m_nnz] = val;
					res.m_Col[res.m_nnz] = j;
					res.m_Row[res.m_nnz] = i;
					res.m_nnz++;
				}
				
			}
		}

		
		sort_Row(res);
		return res;
	}
	std::cout << "nie mo¿na pomno¿yæ macierzy" << std::endl;
	return *this;


}

//funkcja sortujaca macierz
//wzgledem wierszy
void Macierz::sort_Row(Macierz& M_other) {
	
	int buf = 0;
	float buf_Value = 0;
	for (int i = 0; i < M_other.m_nnz - 1; i++)
	{
		for (int j = 0; j < M_other.m_nnz - 1; j++)
		{
			if (M_other.m_Row[j] > M_other.m_Row[j + 1] || M_other.m_Row[j] == M_other.m_Row[j+1] && M_other.m_Col[j] > M_other.m_Col[j+1])
			{
				//swap value
				buf_Value = M_other.m_Value[j];
				M_other.m_Value[j] = M_other.m_Value[j + 1];
				M_other.m_Value[j + 1] = buf_Value;

				//swap Row
				buf = M_other.m_Row[j];
				M_other.m_Row[j] = M_other.m_Row[j + 1];
				M_other.m_Row[j + 1] = buf;

				//swap Col
				buf = M_other.m_Col[j];
				M_other.m_Col[j] = M_other.m_Col[j + 1];
				M_other.m_Col[j + 1] = buf;

			}
		}
	}

}

//funkcja sortujaca macierz
//wzgledem kolumn
void Macierz::sort_Col(Macierz& M_other) {

	int buf = 0;
	float buf_Value = 0;
	for (int i = 0; i < M_other.m_nnz - 1; i++)
	{
		for (int j = 0; j < M_other.m_nnz - 1; j++)
		{
			if (M_other.m_Col[j] > M_other.m_Col[j + 1] || M_other.m_Col[j] == M_other.m_Col[j + 1] && M_other.m_Row[j] > M_other.m_Row[j + 1])
			{
				//swap value
				buf_Value = M_other.m_Value[j];
				M_other.m_Value[j] = M_other.m_Value[j + 1];
				M_other.m_Value[j + 1] = buf_Value;

				//swap Row
				buf = M_other.m_Row[j];
				M_other.m_Row[j] = M_other.m_Row[j + 1];
				M_other.m_Row[j + 1] = buf;

				//swap Col
				buf = M_other.m_Col[j];
				M_other.m_Col[j] = M_other.m_Col[j + 1];
				M_other.m_Col[j + 1] = buf;

			}
		}
	}

}


//operator przypisania
Macierz& Macierz::operator=(const Macierz& M_other) {
	//sprawdzenie czy inny element
	//nie jest naszym pierwotnym
	if (this == &M_other)
	{
		return *this;
	}

	//usuwamy istniejaca pamiec
	//aby uniknac wyciekow
	delete[] m_Value;
	delete[] m_Col;
	delete[] m_Row;


	//przypisujemy pamiec
	m_nnz = M_other.m_nnz;
	m_Row_Size = M_other.m_Row_Size;
	m_Col_Size = M_other.m_Col_Size;

	m_Value = new float[m_Row_Size * m_Col_Size];
	m_Col = new size_t[m_Row_Size * m_Col_Size];
	m_Row = new size_t[m_Row_Size * m_Col_Size];

	//jezeli udalo sie zadeklarowac
	//przypisujemy pamiec
	if (m_Value != NULL && m_Row != NULL && m_Col != NULL) {
		for (int i = 0; i < m_nnz; i++)
		{
			m_Value[i] = M_other.m_Value[i];
			m_Row[i] = M_other.m_Row[i];
			m_Col[i] = M_other.m_Col[i];
		}
	}
	else
	{
		std::cout << "nie udalo sie zadeklarowac pamieci\n";
		delete[] m_Value;
		delete[] m_Col;
		delete[] m_Row;

		m_Value = nullptr;
		m_Col = nullptr;
		m_Row = nullptr;
	}

	return *this;
}

//funkcja zwracajaca numer
//pierwszego niezerowego
//elementu w danym rzedzie
int Macierz::Start_col_id(const int Row) const {

	for (int i = 0; i < m_nnz; i++)
	{
		if (m_Row[i] == Row)
			return i;
	}
	return -1;

}


//funkcja zwracajaca numer
//ostatniego niezerowego
//elementu w danym rzedzie
int Macierz::End_col_id(const int Row) const {

	for (int i = m_nnz - 1; i >= 0; i--)
	{
		if (m_Row[i] == Row)
			return i;
	}
	return -1;

}

//funkcja zwracajaca numer
//pierwszego niezerowego
//elementu w danej kolumnie
int Macierz::Start_row_id(const int Col, const Macierz& M_other ) const {

	for (int i = 0; i < M_other.m_nnz; i++)
	{
		if (M_other.m_Col[i] == Col)
			return i;
	}
	return -1;

}

//funkcja zwracajaca numer
//ostatniego niezerowego
//elementu w danej kolumnie
int Macierz::End_row_id(const int Col,const Macierz& M_other) const {

	for (int i = M_other.m_nnz - 1; i >= 0; i--)
	{
		if (M_other.m_Col[i] == Col)
			return i;
	}
	return -1;

}

//funkcja ustawiajaca wartosci
//na podanym miejscu
void Macierz::set_Value(const float Val, const int Row, const int Col) {

	//sprawdzenie czy indeksy
	//znajduja sie w naszych przedzialach
	if (Row < m_Row_Size && Col < m_Col_Size) {

		//sprawdzenie czy wartosc jest rowna zeru
		if (Val != 0) {
			bool found = false;
			//przeszukiwanie macierzy w 
			//poszukiwaniu elementu
			for (int i = 0; i < m_nnz; i++)
			{
				if (m_Row[i] == Row && m_Col[i] == Col) {
					m_Value[i] = Val;
					found = true;
				}
			}

			//jezeli element nie istnieje
			//to dodajemy go do macierzy
			if (!found) {
				m_Value[m_nnz] = Val;
				m_Col[m_nnz] = Col;
				m_Row[m_nnz] = Row;
				m_nnz++;
				sort_Row(*this);
			}
		}

		//jezeli wartosc jest rowna 0
		//to usuwamy dany element
		else if (Val == 0) {
			for (int i = 0; i < m_nnz; i++) {
				if (m_Row[i] == Row && m_Col[i] == Col) {
					m_Value[i] = m_Value[m_nnz - 1];
					m_Col[i] = m_Col[m_nnz - 1];
					m_Row[i] = m_Row[m_nnz - 1];
					m_nnz--;

					sort_Row(*this);
				}
			}

		}
	}
}

//funkcja wypisujaca wszystkie
//wartosci naszej macierzy
void Macierz::get_Values() const {
	for (int i = 0; i < m_nnz; i++)
	{
		std::cout << m_Value[i] << " ";
		std::cout << m_Row[i] << " ";
		std::cout << m_Col[i] << " ";
		std::cout << std::endl;
	}
}
