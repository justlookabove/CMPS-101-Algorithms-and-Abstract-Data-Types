/* ************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase@ucsc.edu                   *
*                                                                         *
*                              CMPS 101: PA1                              *
*                                                                         *
*                             November 5, 2017                            *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                Matrix.java                              *
*                                                                         *
**************************************************************************/

// package thisoneguy;

public class Matrix {
    private class Entry {
        int column;
        double value;

        // Constructor
        Entry(int column, double value) {
            this.column = column;
            this.value = value;
        }

        public boolean equals(Object O) {
            if (O == null || !(O instanceof Entry)) {
                return false;
            }
            Entry v = (Entry) O;
            return this.column == v.column && this.value == v.value;
        }

        public String toString() {
            return "(" + column + ", " + value + ")";
        }
    }

    // Matrix Fields
    private List[] rows;
    private int nZ;

    // Constructor
    // Makes a new n x n zero Matrix.  pre: n>=1
    Matrix(int n) {
        if (n < 1) {
            throw new IllegalArgumentException("ERROR: Matrix() called " +
                "with count less than 1.");
        }

        rows = new List[n];

        for (int i = 0; i < n; i++) {
            rows[i] = new List();
        }
    }

/* ************************************************************************
*                                                                         *
*                            Access functions                             *
*                                                                         *
**************************************************************************/

    // Returns n, the number of rows and columns of this Matrix
    int getSize() {
        return rows.length;
    }

    // Returns the number of non-zero entries in this Matrix.
    int getNNZ() {
        // return nZ;
        int count = 0;
        for (int i = 0; i < rows.length; i++) {
            count += rows[i].length();
        }
        return count;
    }

    // overrides Object's equals() method
    public boolean equals(Object x) {
        if (x == null || !(x instanceof Matrix)) {
            throw new IllegalArgumentException("ERROR: equals() is not " +
                "an instance of Matrix.");
        }
        Matrix matrixEquals = (Matrix) x;
        if (getSize() != matrixEquals.getSize()) {
            return false;
        }

        //comparing the entries
        for (int i = 0; i < getSize(); i++) {
            if (!(rows[i].equals(matrixEquals.rows[i]))) {
                return false;
            }
        }
        return true;
    }

/* ************************************************************************
*                                                                         *
*                         Manipulation procedures                         *
*                                                                         *
**************************************************************************/

    // sets this Matrix to the zero state
    void makeZero() {

        // Clearing the list
        for (int i = 0; i < getSize(); i++) {
            // rows[i] = new List();
            rows[i].clear();
        }
        nZ = 0;
    }

    // returns a new Matrix having the same entries as this Matrix
    Matrix copy() {
        Matrix matrixCopy = new Matrix(getSize());
        matrixCopy.nZ = this.nZ;
        // List list = rows[i];
        for (int i = 0; i < matrixCopy.getSize(); i++) {
            rows[i].moveFront();
            while (rows[i].index() >= 0) {
                Entry entry = (Entry) rows[i].get();
                matrixCopy.changeEntry(i + 1, entry.column, entry.value);
                rows[i].moveNext();
            }
        }
        return matrixCopy;
    }

    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    void changeEntry(int i, int j, double x) {
        if (i <= 0 || i > getSize()) {
            throw new IllegalArgumentException("Error: changeEntry " +
                "is called on invalid ith row");
        }
        if (j <= 0 || j > getSize()) {
            throw new IllegalArgumentException("Error: changeEntry " +
                "is called on invalid jth row");
        }

        // shift from 1 index to 0 index
        i--;

        List r = rows[i];
        r.moveFront();
        while (r.index() >= 0 && ((Entry) r.get()).column < j) {
            r.moveNext();
        }
        if (r.index() >= 0) {

            // we found an existing entry
            Entry existingEntry = (Entry) r.get();
            if (existingEntry.column == j) {

                // correct column
                if (x == 0) {
                    r.delete();
                    nZ--;
                    return;
                }
                Entry e = (Entry) r.get();
                e.value = x;
            } 
            else {

                // found column is too high
                if (x == 0) {
                    assert false;
                    return;
                }
                Entry entry = new Entry(j, x);
                r.insertBefore(entry);
                nZ++;
            }
        } 
        else {
            if (x == 0) {
                return;
            }
            
            // all the entries had too small of a column so we 
            // fell off the list
            Entry entry = new Entry(j, x);
            r.append(entry);
            nZ++;
        }
    }

    // returns a new Matrix that's the scalar product of
    // this Matrix with x
    Matrix scalarMult(double x) {
        Matrix multiply = new Matrix(getSize());
        Entry entry = null;
        double Ans = 0;
        for (int i = 0; i < multiply.getSize(); i++) {
            rows[i].moveFront();
            while (rows[i].index() >= 0) {
                entry = (Entry) rows[i].get();
                Ans = entry.value * x;
                multiply.changeEntry(i + 1, entry.column, Ans);
                rows[i].moveNext();
            }
        }
        return multiply;
    }

    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix add(Matrix M) {
        if (M == null) {
            throw new IllegalArgumentException("M doesnt exist");
        }
        if (getSize() != M.getSize()) {
            throw new IllegalArgumentException("ERROR: add() called on" +
                "matricies with two different sizes");
        }
        Matrix sum = new Matrix(getSize());
        Matrix m1 = copy();
        Matrix addend = M.copy();
        Entry entry1 = null;
        Entry entry2 = null;

        for (int i = 0; i < sum.getSize(); i++) {
            List row1 = m1.rows[i], row2 = addend.rows[i];
            row1.moveFront();
            row2.moveFront();
            while (row1.index() >= 0 && row2.index() >= 0) {
                entry1 = (Entry) row1.get();
                entry2 = (Entry) row2.get();

                if (entry1.column == entry2.column) {
                    sum.changeEntry(i + 1, entry1.column, entry1.value + entry2.value);
                    row1.moveNext();
                    row2.moveNext();
                } else if (entry1.column > entry2.column) {
                    sum.changeEntry(i + 1, entry2.column, entry2.value);
                    row2.moveNext();
                } else {
                    sum.changeEntry(i + 1, entry1.column, entry1.value);
                    row1.moveNext();
                }
            }
            if (row1.index() != -1) {
                while (row1.index() >= 0) {
                    entry1 = (Entry) row1.get();
                    sum.changeEntry(i + 1, entry1.column, entry1.value);
                    row1.moveNext();
                }
            } else if (row2.index() != -1) {
                while (row2.index() >= 0) {
                    entry2 = (Entry) row2.get();
                    sum.changeEntry(i + 1, entry2.column, entry2.value);
                    row2.moveNext();
                }
            }
        }
        return sum;
    }

    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M) {
        if (M == null) {
            throw new IllegalArgumentException("M doesnt exist");
        }
        if (getSize() != M.getSize()) {
            throw new IllegalArgumentException("ERROR: sub() called on" +
                "matricies with two different sizes");
        }
        Matrix sum = new Matrix(getSize());
        Matrix m1 = copy();
        Matrix addend = M.copy();
        Entry entry1 = null;
        Entry entry2 = null;

        for (int i = 0; i < sum.getSize(); i++) {
            List row1 = m1.rows[i], row2 = addend.rows[i];
            row1.moveFront();
            row2.moveFront();
            while (row1.index() >= 0 && row2.index() >= 0) {
                entry1 = (Entry) row1.get();
                entry2 = (Entry) row2.get();

                if (entry1.column == entry2.column) {
                    sum.changeEntry(i + 1, entry1.column, entry1.value - entry2.value);
                    row1.moveNext();
                    row2.moveNext();
                } else if (entry1.column > entry2.column) {
                    sum.changeEntry(i + 1, entry2.column, (entry2.value * -1));
                    row2.moveNext();
                } else {
                    sum.changeEntry(i + 1, entry1.column, entry1.value);
                    row1.moveNext();
                }
            }
            if (row1.index() != -1) {
                while (row1.index() >= 0) {
                    entry1 = (Entry) row1.get();
                    sum.changeEntry(i + 1, entry1.column, entry1.value);
                    row1.moveNext();
                }
            } else if (row2.index() != -1) {
                while (row2.index() >= 0) {
                    entry2 = (Entry) row2.get();
                    sum.changeEntry(i + 1, entry2.column, (entry2.value * -1));
                    row2.moveNext();
                }
            }
        }
        return sum;
    }

    // returns a new Matrix that is the transpose of this Matrix
    Matrix transpose() {
        Matrix matrixTranspose = new Matrix(getSize());
        for (int i = 0; i < matrixTranspose.getSize(); i++) {
            rows[i].moveFront();
            while (rows[i].index() != -1) {
                Entry E = (Entry) rows[i].get();
                matrixTranspose.changeEntry(E.column, i + 1, E.value);
                rows[i].moveNext();
            }
        }
        return matrixTranspose;
    }

    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix mult(Matrix M) {
        if (M == null) {
            throw new IllegalArgumentException("M doesnt exist");
        }
        if (getSize() != M.getSize()) {
            throw new IllegalArgumentException("ERROR: mult() called on" +
                "matricies with two different sizes");
        }
        Matrix matrixMult = new Matrix(getSize());
        Matrix T = M.transpose();
        double dotProd;
        for (int i = 0; i < matrixMult.getSize(); i++) {
            if (rows[i].length() > 0) {
                for (int j = 0; j < matrixMult.getSize(); j++) {
                    if (T.rows[j].length() > 0) {
                        dotProd = dotProduct(rows[i], T.rows[j]);
                        matrixMult.changeEntry(i + 1, j + 1, dotProd);
                    }
                }
            }
        }
        return matrixMult;
    }


/* ************************************************************************
*                                                                         *
*                              Other Methods                              *
*                                                                         *
**************************************************************************/

    // overrides Object's toString() method
    public String toString() {
        String string = "";
        for (int i = 0; i < this.getSize(); i++) {
            if (rows[i].length() > 0) {
                string = string + (i + 1) + ": " + rows[i].toString();
                string += "\n";
            }
        }
        return string;
    }

    // Helper function for finding the dot product of two lists
    private static double dotProduct(List A, List B) {
        A.moveFront();
        B.moveFront();
        double Ans = 0;
        while (A.index() >= 0 && B.index() >= 0) {
            Entry entry1 = (Entry) A.get();
            Entry entry2 = (Entry) B.get();
            if (entry1.column == entry2.column) {
                Ans += entry1.value * entry2.value;
                A.moveNext();
                B.moveNext();
            } else if (entry1.column < entry2.column) {
                A.moveNext();
            } else {
                B.moveNext();
            }
        }
        return Ans;
    }

}