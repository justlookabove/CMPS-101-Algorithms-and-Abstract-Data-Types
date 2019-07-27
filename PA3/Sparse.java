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
*                                Sparse.java                              *
*                                                                         *
**************************************************************************/

// package thisoneguy;

import java.io.*;
import java.util.Scanner;


public class Sparse {
    public static void main(String[] args) throws IOException {

        if (args.length < 2) {
            System.err.println("Usage: Sparse infile outfile");
            System.exit(1);
        }

        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));

        int s = in .nextInt();
        int x = in .nextInt();
        int y = in .nextInt();

        Matrix M1 = new Matrix(s);
        Matrix M2 = new Matrix(s);

        while ( in .hasNextInt()) {
            for (int i = 0; i < x; i++) {
                int row = in .nextInt();
                int column = in .nextInt();;
                double value = in .nextDouble();
                M1.changeEntry(row, column, value);
            } in .nextLine();

            for (int i = 0; i < y; i++) {
                int row = in .nextInt();
                int column = in .nextInt();;
                double value = in .nextDouble();
                M2.changeEntry(row, column, value);

            }
        }

        // Printing A
        out.println("A has " + M1.getNNZ() + " non-zero entries:");
        out.println(M1);

        // Printing B
        out.println("B has " + M2.getNNZ() + " non-zero entries:");
        out.println(M2);

        // Printing (1.5) * A
        out.println("(1.5)*A = ");
        out.println(M1.scalarMult(1.5));

        // Printing A+B
        out.println("A+B = ");
        out.println(M1.add(M2));

        // Printing A+A
        out.println("A+A = ");
        out.println(M1.add(M1));

        // Printing B-A
        out.println("B-A = ");
        out.println(M2.sub(M1));

        // Printing A-A
        out.println("A-A = ");
        out.println(M1.sub(M1));

        // Printing transpose of A
        out.println("Transpose(A) = ");
        out.println(M1.transpose());

        // Printing A*B
        out.println("A*B = ");
        out.println(M1.mult(M2));

        // Printing B^2
        out.println("B*B = ");
        out.println(M2.mult(M2));


        in .close();
        out.flush();
        out.close();
    }
}