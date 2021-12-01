***How To Run .cpp FILE***

Pre-Requisites: 

Please ensure that "214101020_Treap.cpp","214101020_TestFileGenerationAndParametersCalc" Files are placed in easily accessible location.

Running commands:

1. On Linux Machine use-
			(i) For Treap	

				>g++ 214101020_Treap.cpp
				>./a.out

			(ii)For Test File And Parameter Calculation

				>g++ 214101020_TestFileGenerationAndParametersCalc.cpp
				>./a.out

2. On Windows you may use IDE to directly run or use Cygwin to simulate Linux like environment, And then use above commands.

3. You will be shown following outputs-

		i) For Treap:- 
				*** MENU DRIVEN MODE ***

				You can insert, delete, search, print in the Treap by choosing respective option.

  		ii) For Test File Generation And Parameter Calculation:-
				
				(a) This Program will generate 5 Test Files.

				(b) You need to specify total number of operations in all 5 files. Enter large no. Say 5000-10000 in each file.
  				
				(c) Program will randomly generate insert & delete sequences.

				(d) Program will save ALL the TEST FILES for your reference in same directory.
					
				(e) Please wait for a while, to see Final_Analysis Compilation file to be generated in same directory.

				(f) File will be stored in same directory as of program. Please Check. Also Output will be shown on screen.
	
			
4. IMPORTANT NOTE: For printing the .gv file of TREAP program, Please take absolute precautions. Note that after print function call, a DOT file will be generated in same location.
    

    This DOT file will be generated once you try printing.


Steps to visualize "myfile.gv" in windows:

     A) Ensure that graphviz is installed in your machine.

     B) Go to cmd. And then to "myfile.gv" file location. In above example(through cmd) go to 
                                                          ---------->    D:\        

                                                         

      C) Write command in following format-

                                    D:\> "dot executable location in your computer" -Tpng <filename.gv> -o <newfilename.png>

   For above example in my pc :

                            -----> D:\> "C:\Program Files\Graphviz2.38\bin\dot.exe" -Tpng myfile.gv -o myfile.png  

D) Open png image to see output.