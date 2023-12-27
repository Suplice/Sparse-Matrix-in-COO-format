#ifndef FUNKCJE_H
#define FUNKCJE_H
// macierz.h

/**
 * @file
 * @brief Declaration of the Macierz class.
 */
class Macierz {
private:
	
	size_t m_nnz;  ///< Number of non-zero Values.
	size_t m_Row_Size; ///< Size of Rows on Matrix.
	size_t m_Col_Size; ///< Size of Columns in Matrix.

	float* m_Value; ///< array of Matrix non-zero Values.
	size_t* m_Row; ///< array of Row indexes at which Values are placed.
	size_t* m_Col; ///< array of Column indexes at wich Values are placed.


	/**
	* @brief Sorts Values, Rows and columns by Rows.
	* @param M_other Other entity of Macierz type.
	*/
	void sort_Row(Macierz& M_other);

	/**
	* @brief Sorts Values, Rows and columns by Columns.
	* @param M_other Other entity of Macierz type.
	*/
	void sort_Col(Macierz& M_other);

	/**
	* @brief Searches for first element in Row.
	* @param Row Row index to look for.
	* @return Returns index of found element.
	*/
	int Start_col_id(const int Row) const;

	/**
	* @brief Searches for first element in Column.
	* @param Row Row index to look for.
	* @param M_other Second multiplication Matrix.
	* @return Returns index of found element.
	*/
	int Start_row_id(const int Col, const Macierz& M_other) const;

	/**
	* @brief Searches for last element in Row.
	* @param Row Row index to look for.
	* @return Returns index of found element.
	*/
	int End_col_id(const int Row) const;

	/**
	* @brief Searches for last element in Column.
	* @param Row Row index to look for.
	* @param M_other Second multiplication Matrix.
	* @return Returns index of found element.
	*/
	int End_row_id(const int Col, const Macierz& M_other) const;

public:
	/**
	* @brief Base Constructor.
	*/
	Macierz() : m_Value(nullptr), m_Row(nullptr), m_Col(nullptr), m_Row_Size(0), m_Col_Size(0), m_nnz(0) {};

	/**
	* @brief Constructor based on a 2D array of values.
	* @param Values 2D array of values.
	* @param rows Number of rows in the array.
	* @param columns Number of columns in the array.
	*/
	Macierz(float** Values, int rows, int columns);

	/**
	* @brief Constructor based on ammount of rows and columns.
	* @param rows Number of rows in the array.
	* @param columns Number of columns in the array.
	*/
	Macierz(int rows, int columns);

	/**
	* @brief Copy Constructor.
	* @param other Other entity of Macierz type.
	*/
	Macierz(Macierz& other);

	/**
	* @brief Move Constructor.
	* @param other Other entity of Macierz type.
	*/
	Macierz(Macierz&& other) noexcept;

	/**
	* @brief Entity destructor
	*/
	~Macierz();
	

	/**
	* @brief Function that adds other matrix to base matrix.
	* @param M_other Other entity of Macierz type.
	* @return Matrix which is sum of base and other.
	*/
	Macierz dod(Macierz& M_other);

	/**
	* @brief Function that substracts other matrix from base matrix.
	* @param M_other Other entity of Macierz type.
	* @return Matrix which is diffrence of base and other.
	*/
	Macierz ode(Macierz& M_other);


	/**
	* @brief Function that multiplies base matrix with other matrix.
	* @param M_other Other entity of Macierz type.
	* @return Matrix which is product of base and other multiplication.
	*/
	Macierz mnoz(Macierz& M_other);

	/**
	* @brief Function transposes base matrix.
	* @return Transposed Matrix.
	*/
	Macierz Transpon();


	/**
	* @brief Operator assigns other entity values to base.
	* @param M_other Other entity of Macierz type.
	* @return Base Matrix after assignment.
	*/
	Macierz& operator=(const Macierz& M_other);


	/**
	* @brief Function writting out all non-zero Matrix values.
	*/
	void get_Values() const;

	/**
	* @brief Function that assigns Val on position Row and Col in Matrix.
	* @param Val Value to be assigned.
	* @param Row Row in which number will be assigned.
	* @param Col Col in which number will be assigned.
	*/
	void set_Value(const float Val, const int Row, const int Col);


};

#endif