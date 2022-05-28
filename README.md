**Research:**

1. Shell Introduction: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

2. Write your Own Shell Tutorial: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

3. Write a Shell in C Tutorial: https://brennan.io/2015/01/16/write-a-shell-in-c/

3. Eval Sheet: https://github.com/3Brainz/school21-checklists/blob/master/ng_3_minishell.pdf

4. Search for the Functions Allowed to Use in this Project \n
	ReadLine(): https://web.mit.edu/gnu/doc/html/rlman_2.html 
				https://www.man7.org/linux/man-pages/man3/readline.3.html
	- readline
 	- rl_clear_history
 	- rl_on_new_line
		Function: int rl_on_new_line ()
		Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
 	- rl_replace_line
 	- rl_redisplay
	 	Function: int rl_redisplay ()
		Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
 	- add_history


 	- printf
 	- malloc
 	- free
 	- write
 	- access
 	- open
 	- read
 	- close
 	- fork
 	- wait
 	- waitpid
 	- wait3 -> not used
 	- wait4 -> not used


	Signal.h:
 	- signal
 	- sigaction
 	- sigemptyset -> not used
 	- sigaddset -> not used
 	- kill


 	- exit
 	- getcwd
 	- chdir
 	- stat -> not used
 	- lstat -> not used
 	- fstat -> not used
 	- unlink -> not used
 	- execve
 	- dup
 	- dup2
 	- pipe
 	- opendir -> not used
 	- readdir -> not used
 	- closedir -> not used
 	- strerror -> not used
 	- perror -> not used
 	- isatty -> not used
 	- ttyname -> not used
 	- ttyslot -> not used
 	- ioctl -> not used
 	- getenv -> not used

	Termcap database emulation:  https://pubs.opengroup.org/onlinepubs/7908799/xcurses/tgetent.html
 	- tcsetattr -> not used
 	- tcgetatt -> not used
 	- tgetent -> not used
 	- tgetflag -> not used
 	- tgetnum -> not used
 	- tgetst -> not used
 	- tgoto -> not used
 	- tputs -> not used



**Architecture:**

1. Module 1:
	- Builtin Commands:
		◦ echo with option -n
		◦ cd with only a relative or absolute path
		◦ pwd with no options
		◦ export with no options
		◦ unset with no options
		◦ env with no options or arguments
		◦ exit with no options

2. Module 2:
	- Lexar
		Tokens:
			- ordinary token recognition
			- processing of here-documents
	- Parser
	- Command List

3. Module 3:
	- Executor

4. Module 4:
	- Signal Handling
		◦ ctrl-C displays a new prompt on a new line.
		◦ ctrl-D exits the shell.
		◦ ctrl-\ does nothing.

5. Module 5:
	- Terminate: After the Commands are Executed, the Shell executes any Shutdown Commands, Frees up any Memory, and Terminates.


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



**TO DO:**

1. Test out the Shell in order to Learn about Character Behaviour

2. Find out from Daniel how to Push to the Same Repo

3. Check out the Repos that have Completed Strictly what is Demanded

4.
