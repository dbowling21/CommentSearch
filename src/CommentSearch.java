import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;
import java.util.Scanner;

public class CommentSearch {
	
	// toggle whether to display GUI file explorer or hardcode
	private static boolean chooseFile = true;
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
			cFile = new File("src/inputTestFile.c");
		}
		
		Scanner br = new Scanner(new FileReader(cFile));
		int counter = 0;
		boolean comOpen;
		String line;
		String comment;
		
		while (br.hasNextLine()){
			line = br.nextLine();
			if (line.contains("/*")	&& line.contains("*/")){
				while (line.contains("/*")	&& line.contains("*/")){
					counter ++;
					comment = line.substring(line.indexOf("/*"), line.indexOf("*/") + 2);
					line = line.substring(line.indexOf("*/") + 2, line.length());;
					System.out.println("Comment " + counter);
					System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
					System.out.println(comment + "\n");
				}
				
			}
			if (line.contains("/*")){
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
