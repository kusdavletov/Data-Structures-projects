// Constructor, create empty sparse matrix with (row, col)
template <class type>
Matrix<type>::Matrix(int Row, int col)
{
	nRow = Row;
	nCol = col;
	nElem = 0;

	int p = (Row < col) ? col : Row;

    headnode = new MatrixNodeType (true, 0);
    if (p == 0) return;

    MatrixNodeType **head = new MatrixNodeType *[p];

    for (int i = 0; i < p; ++i)
    {
        head[i] = new MatrixNodeType (true,0);
        head[i]->right = head[i]-> down = head[i];
    }

    for (int i = 0; i < p - 1; ++i)
        head[i]->next = head[i + 1];

    head[p - 1]->next = headnode;

    headnode -> next = head[0];
    delete[] head;
}

// Constructor from istream
template <class type>
Matrix<type>::Matrix(std::ifstream& is)
{
    Triple<type> s;
	is >> s.row >> s.col >> s.value;

	nRow = s.row;
	nCol = s.col;
	nElem = s.value;

	int p = (s.row < s.col) ? s.col : s.row;

	std::cout << "Row : " << s.row << ", Col : " << s.col << ", nElem : " << s.value << std::endl;

    headnode = new MatrixNodeType (true, 0);
    if (p == 0) return;

    MatrixNodeType **head = new MatrixNodeType *[p];

    for (int i = 0; i < p; ++i)
        head[i] = new MatrixNodeType (true, 0);

    MatrixNodeType *last = head[0];
    int row = 0;

    for (int i = 0; i < s.value; ++i)
    {
        Triple<type> t;
        is >> t.row >> t.col >> t.value;
        if (t.row > row)
        {
            last->right = head[row];
            row = t.row;
            last = head[row];
        }
        last->right = new MatrixNodeType (false, &t);
        last = last->right;
        head[t.col]->next->down = last;
        head[t.col]->next = last;
    }

    last->right = head[row];

    for (int i = 0; i < s.col; ++i)
        head[i]->next->down = head[i];

    for (int i = 0; i < p - 1; ++i)
        head[i]->next = head[i + 1];

    head[p - 1]->next = headnode;

    headnode -> next = head[0];
    delete[] head;
}

// Copy constructor
template <class type>
Matrix<type>::Matrix(const Matrix& a)
{
    nRow = a.nRow;
    nCol = a.nCol;
    nElem = a.nElem;

    int p = (nRow < nCol) ? nCol : nRow;

    headnode = new MatrixNodeType (true, 0);
    if (p == 0 || nElem == 0) return;

    MatrixNodeType **head = new MatrixNodeType *[p];

    for (int i = 0; i < p; ++i)
        head[i] = new MatrixNodeType (true, 0);

    MatrixNodeType *last = head[0];
    int row = 0;

    MatrixNodeType* curr = a.headnode->next;

    while(curr != a.headnode)
    {
        MatrixNodeType* Row = curr->right;
        while(Row != curr)
        {
            Triple<type> t;
            t = Row->triple;
            if (t.row > row)
            {
                last->right = head[row];
                row = t.row;
                last = head[row];
            }
            last->right = new MatrixNodeType (false, &t);
            last = last->right;
            head[t.col]->next->down = last;
            head[t.col]->next = last;
            Row = Row->right;
        }
        curr = curr->next;
    }

    last->right = head[row];

    for (int i = 0; i < nCol; ++i)
        head[i]->next->down = head[i];

    for (int i = 0; i < p - 1; ++i)
        head[i]->next = head[i + 1];

    head[p - 1]->next = headnode;

    headnode -> next = head[0];
    delete[] head;
}

// Assignment operator
template <class type>
Matrix<type>&
Matrix<type>::operator=(const Matrix& a)
{
    nRow = a.nRow;
    nCol = a.nCol;
    nElem = a.nElem;

    int p = (nRow < nCol) ? nCol : nRow;

    delete[] headnode;
    headnode = new MatrixNodeType (true, 0);
    if (p == 0 || nElem == 0) return *this;

    MatrixNodeType **head = new MatrixNodeType *[p];

    for (int i = 0; i < p; ++i)
        head[i] = new MatrixNodeType (true, 0);

    MatrixNodeType *last = head[0];
    int row = 0;

    MatrixNodeType* curr = a.headnode->next;

    while(curr != a.headnode)
    {
        MatrixNodeType* Row = curr->right;
        while(Row != curr)
        {
            Triple<type> t;
            t = Row->triple;
            if (t.row > row)
            {
                last->right = head[row];
                row = t.row;
                last = head[row];
            }
            last->right = new MatrixNodeType (false, &t);
            last = last->right;
            head[t.col]->next->down = last;
            head[t.col]->next = last;
            Row = Row->right;
        }
        curr = curr->next;
    }

    last->right = head[row];

    for (int i = 0; i < nCol; ++i)
        head[i]->next->down = head[i];

    for (int i = 0; i < p - 1; ++i)
        head[i]->next = head[i + 1];

    head[p - 1]->next = headnode;

    headnode -> next = head[0];
    delete[] head;
    return *this;
}

// Destructor
template <class type>
Matrix<type>::~Matrix()
{
    if (!headnode) return;
    MatrixNodeType *y;
    MatrixNodeType *x = headnode->next;
    while (x != headnode)
    {
        y = x->next;
        delete[] x;
        x = y;
    }
    delete[] x;
}

// Add Matrix b to *this
template <class type>
Matrix<type>
Matrix<type>::operator+(const Matrix& b)
{
    if (nCol != b.nCol || nRow != b.nRow)
    {
        std::cout << "DIMENSION	MISMATCH\n";
        return Matrix<type> (0, 0);
    }

	Matrix<type> m (*this);

    int p1 = (nCol > nRow ? nCol : nRow), p2 = (b.nCol > b.nRow ? b.nCol : b.nRow);
    MatrixNodeType *A;
    MatrixNodeType *B;
    MatrixNodeType *u = headnode->next;
    MatrixNodeType *v = b.headnode->next;

    for (int i = 0; i < nRow; ++i)
    {
        A = u->right;
        B = v->right;
        while (A != u && B != v)
        {
            Triple<type> x = A->triple, y = B->triple;
            if (x.col < y.col)
            {
                m.CreateElement (i, x.col, x.value);
                A = A->right;
            }
            else
                if (x.col > y.col)
                {
                    m.CreateElement (i, y.col, y.value);
                    B = B->right;
                }
                else
                {
                    m.CreateElement (i, x.col, x.value + y.value);
                    A = A->right;
                    B = B->right;
                }
        }
        while (A != u)
        {
            m.CreateElement (i, (A->triple).col, (A->triple).value);
            A = A->right;
        }
        while (B != v)
        {
            m.CreateElement (i, (B->triple).col, (B->triple).value);
            B = B->right;
        }
        u = u->next;
        v = v->next;
    }

	return m;
}

// Subtract Matrix b to *this
template <class type>
Matrix<type>
Matrix<type>::operator-(const Matrix& b)
{
    if (nCol != b.nCol || nRow != b.nRow)
    {
        std::cout << "DIMENSION	MISMATCH\n";
        return Matrix<type> (0, 0);
    }

	Matrix<type> m(*this);

    int p1 = (nCol > nRow ? nCol : nRow), p2 = (b.nCol > b.nRow ? b.nCol : b.nRow);
    MatrixNodeType *A;
    MatrixNodeType *B;
    MatrixNodeType *u = headnode->next;
    MatrixNodeType *v = b.headnode->next;

    for (int i = 0; i < nRow; ++i)
    {
        A = u->right;
        B = v->right;
        while (A != u && B != v)
        {
            Triple<type> x = A->triple, y = B->triple;
            if (x.col < y.col)
            {
                m.CreateElement (i, x.col, x.value);
                A = A->right;
            }
            else
                if (x.col > y.col)
                {
                    m.CreateElement (i, y.col, -y.value);
                    B = B->right;
                }
                else
                {
                    m.CreateElement (i, x.col, x.value - y.value);
                    A = A->right;
                    B = B->right;
                }
        }
        while (A != u)
        {
            m.CreateElement (i, (A->triple).col, (A->triple).value);
            A = A->right;
        }
        while (B != v)
        {
            m.CreateElement (i, (B->triple).col, -(B->triple).value);
            B = B->right;
        }
        u = u->next;
        v = v->next;
    }

	return m;
}

// Multiply Matrix b to *this
template <class type>
Matrix<type>
Matrix<type>::operator*(const Matrix& b)
{
    if (nCol != b.nRow)
    {
        std::cout << "DIMENSION	MISMATCH\n";
        return Matrix<type> (0, 0);
    }

    Matrix<type> m (nRow, b.nCol);

    int p1 = (nCol > nRow ? nCol : nRow), p2 = (b.nCol > b.nRow ? b.nCol : b.nRow);
    MatrixNodeType **row = new MatrixNodeType *[p1];
    MatrixNodeType **col = new MatrixNodeType *[p2];
    MatrixNodeType *C;
    MatrixNodeType *R;

    row[0] = headnode->next;
    for (int i = 1; i < p1; ++i)
        row[i] = row[i - 1]->next;

    col[0] = b.headnode->next;
    for (int i = 1; i < p2; ++i)
        col[i] = col[i - 1]->next;

    for (int i = 0; i < nRow; ++i)
        for (int j = 0; j < b.nCol; ++j)
        {
            R = row[i]->right;
            C = col[j]->down;
            type res = type (0);

            while (R != row[i] && C != col[j])
            {
                Triple<type> x = R->triple, y = C->triple;
                if (x.col < y.row) R = R->right;
                else if (x.col > y.row) C = C->down;
                else
                {
                    if (x.value * y.value != type (0)) res += x.value * y.value;
                    C = C->down;
                    R = R->right;
                }
            }

            if (res != type (0)) m.CreateElement (i, j, res);
        }

    delete[] row, col, C, R;
	return m;
}

// Swap i-th row with j-th row
template <class type>
Matrix<type>&
Matrix<type>::SwapRow(int i, int j)
{
    if (i >= nRow || j >= nRow) return *this;

    Matrix<type> a (nRow, nCol);

    MatrixNodeType* curr = headnode->next;

    while(curr != headnode)
    {
        MatrixNodeType* row = curr->right;
        while(row != curr)
        {
            int x = (row->triple).row;
            if (x == i) x = j;
            else if (x == j) x = i;
            a.CreateElement (x, (row->triple).col, (row->triple).value);
            row = row->right;
        }
        curr = curr->next;
    }

    *this = a;

    return *this;
}

// Swap i-th col with j-th col
template <class type>
Matrix<type>&
Matrix<type>::SwapCol(int i, int j)
{
    if (i >= nCol || j >= nCol) return *this;

    Matrix<type> a (nRow, nCol);

    MatrixNodeType* curr = headnode->next;

    while(curr != headnode)
    {
        MatrixNodeType* col = curr->down;
        while(col != curr)
        {
            int y = (col->triple).col;
            if (y == i) y = j;
            else if (y == j) y = i;
            a.CreateElement ((col->triple).row, y, (col->triple).value);
            col = col->down;
        }
        curr = curr->next;
    }

    *this = a;

    return *this;
}

// Create single element in the matrix
template <class type>
Matrix<type>&
Matrix<type>::CreateElement(int i, int j, type val)
{
    if (i >= nRow || j >= nCol) return *this;
    ++nElem;

	MatrixNodeType *row = headnode;
	for (int k = 0; k <= i; ++k)
        row = row->next;

    MatrixNodeType *col = headnode;
	for (int k = 0; k <= j; ++k)
        col = col->next;

    MatrixNodeType *head = row;
    MatrixNodeType *tail = col;

    while (((head->right)->triple).col < j && (head->right) != row) head = head -> right;
    while (((tail->down)->triple).row < i && (tail->down) != col) tail = tail -> down;

    Triple<type> t;
    t.row = i; t.col = j; t.value = val;

    if (((head->right)->triple).col == j && (head->right) != row)
    {
        ((head->right)->triple) = t;
        return *this;
    }

    if (head->right == row)
    {
        MatrixNodeType *newNode = new MatrixNodeType (false, &t);
        newNode->right = row;
        head->right = newNode;
    }
    else
    {
        MatrixNodeType *newNode = new MatrixNodeType (false, &t);
        newNode->right = head->right;
        head->right = newNode;
    }

    if (tail->down == col)
    {
        MatrixNodeType *newNode = new MatrixNodeType (false, &t);
        newNode->down = col;
        tail->down = newNode;
    }
    else
    {
        MatrixNodeType *newNode = new MatrixNodeType (false, &t);
        newNode-> down = head->down;
        tail->down = newNode;
    }

	return *this;
}

// Transpose matrix
template <class type>
Matrix<type>&
Matrix<type>::Transpose()
{
    int p = (nCol > nRow ? nCol : nRow);
    Matrix<type> a (nCol, nRow);

    MatrixNodeType* curr = headnode->next;

    while(curr != headnode)
    {
        MatrixNodeType* row = curr->right;
        while(row != curr)
        {
            a.CreateElement ((row->triple).col, (row->triple).row, (row->triple).value);
            row = row->right;
        }
        curr = curr->next;
    }

    *this = a;

	return *this;
}




