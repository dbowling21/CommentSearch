import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;

public class CommentSearch {
	
	public static void main(String[] args) throws IOException {
		
		boolean chooseFile = true; // toggle whether to display GUI file explorer or hardcode
		File cFile;
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
		
		FileReader fr = new FileReader(cFile);
		BufferedReader br = new BufferedReader(fr);
		
		int c;
		int count = 0; // counter for # of comments
		char character;
		StringBuilder comment = new StringBuilder(); //stores the current comment
		while((c = br.read()) != -1) //loop until end of file
		{
			character = (char) c;
			if (String.valueOf(character).equals("/")){ //potential start of comment
				character = (char) br.read();
				if (String.valueOf(character).equals("*")){ //start of comment
					comment.append("/*");
					count ++;
					do{
						character =(char) br.read();
						comment.append(character); //add chars to comment until comment escape
						
						//checks if length of comment is greater than 3 for a case where "/*/" would
						// otherwise be recognized as a comment
					} while (!(String.valueOf(comment.charAt(comment.length() -2)).equals("*")
							   && String.valueOf(character).equals("/") && comment.length() > 3));
								
					System.out.println("Comment " + count);
					System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
					System.out.println(comment + "\n");
					comment.delete(0, comment.length()); //reset comment
				}
			}
		}
	}
}
