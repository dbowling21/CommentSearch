import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;
import java.util.Scanner;

public class CommentSearch {
	
	// toggle whether to display GUI file explorer or hardcode
	private static boolean chooseFile = false;
	private static File cFile;
	
	public static void main(String[] args) throws IOException {
		
		if (chooseFile){
			JFileChooser fileGUI = new JFileChooser();
			FileNameExtensionFilter cFilter = new FileNameExtensionFilter("c files", "c");
			fileGUI.setFileFilter(cFilter);
			fileGUI.showSaveDialog(null);
			
			cFile = fileGUI.getSelectedFile();
		}
		else {
			cFile = new File("src/Sudoku-Validator.c");
		}
		
		Scanner br = new Scanner(new FileReader(cFile));
		int counter = 0;
		boolean comOpen;
		String line;
		String comment;
		
		while (br.hasNextLine()){
			line = br.nextLine();
			if (line.contains("/*")	&& line.contains("*/")){
				counter ++;
				comment = line.substring(line.indexOf("/*"), line.indexOf("*/") + 2);
				
				System.out.println("Comment " + counter);
				System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				System.out.println(comment + "\n");
			}
			else if (line.contains("/*")){
				comOpen = true;
				comment = line.substring(line.indexOf("/*"));
				do {
					line = br.nextLine();
					if (line.contains("*/")){
						comment = comment + "\n" + line;
						comOpen = false;
						
						counter ++;
						System.out.println("Comment " + counter);
						System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
						System.out.println(comment + "\n");
					}
					else {
						comment = comment + "\n" + line;
					}
				}while (comOpen);
			}
		}
	}
	
}
