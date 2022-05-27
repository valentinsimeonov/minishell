**Research:**

1. https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

2. Eval Sheet: https://github.com/3Brainz/school21-checklists/blob/master/ng_3_minishell.pdf

3. 


**Architecture:**

1. Module 1:
	- Lexar
	- Parser
	- Command List

2. Executor


**Investigate:**

1. Subshells: Arguments between `` (backticks) are executed and the output is sent as 
input to the shell. 

2. You need to implement the below grammar in shell.l and shell.y to make our parser interpret 
the command lines and provide our executor with the correct information. 
cmd [arg]* [ | cmd [arg]* ]*
          [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
Fig 4: Shell Grammar in Backus­Naur Form 

3. Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).

4. Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

5. E-Nums



**TODO:**

1. Test out the Shell in order to To Learn about Character Behaviour

2. Find out from Daniel how to Push to the Same Repo