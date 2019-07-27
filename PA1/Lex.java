/* ************************************************************************
*                                                                         *
*                   Kiran Gunasekaran, kgunase@ucsc.edu                   *
*                                                                         *
*                              CMPS 101: PA1                              *
*                                                                         *
*                             October 10, 2017                            *
*                                                                         *
*  _____________________________________________________________________  *
*                                                                         *
*                                 Lex .java                               *
*                                                                         *
**************************************************************************/

// package thisoneguy;

import java.io.*;
import java.util.Scanner;

public class Lex {
    public static void main(String[] args) throws IOException {
        Scanner in = null;
        Scanner read = null;
        PrintWriter out = null;
        String line = null;
        int i, n, lineCount = 0;

        if(args.length < 2){
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }

        in = new Scanner(new File(args[0]));
        read = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));
        String lines[] = new String[lineCount];
        List list = new List();

        while (in.hasNextLine()){
            lineCount++;
            in.nextLine();
        }

        for(i = 0; in.hasNextLine(); i++) {
            lines[i] = in.nextLine();
        }

        for (n = 1; in.hasNextLine(); n++) {
            line = lines[n];
            i = n -1;
            while (i >= 0 && line.compareTo(lines[i]) < 0) {
                lines[i+1] = lines[i];
                i--;
            }
            lines[i+1] = lines[i];
        }

        for(i = 0; in.hasNextLine(); i++){
            list.append(i);
        }

        for(i = 0; in.hasNextLine(); i++) {
            list.moveFront();
            out.println(lines[list.get()]);

        }
        in.close();
        out.close();
    }
}
