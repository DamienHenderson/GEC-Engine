Version 1.0 12/10/2017

This batch script will generate a submissible folder for the GEC milestones.
To use this batch script you should place the included file "MakeMilestone.bat" into the solution directory (the folder containing the .sln file).
Please note that if this readme is copied alongside the "MakeMilestone.bat" file then it will be included in the generated milestone folder.

Usage:
To generate a submissible milestone folder you should 
- firstly, run a cmd.exe instance in the solution directory (this can be achieved by shift right clicking windows explorer and choosing open command window here).
- secondly, type MakeMilestone.bat into the cmd window (if you press tab after typing "MakeM" the filename should be autocompleted) followed by the desired name of the folder such as GEC_Milestone1
- finally, check the folder which has been outputted it should contain a Source folder which contains all .cpp, .hpp and .h files from your VS project, all .txt files from the project directory and all .txt files from the solution directory

Report any bugs, issues or feature requests to s6062610@live.tees.ac.uk