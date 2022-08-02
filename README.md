**Architecture:**
1. Module 1:
	- ENV List **DONE**

2. Module 2:
	- Lexar   **DONE**

	- Parser  **DONE**
		- ordinary token recognition
		- processing of here-documents
	- Command Table List  **DONE**
		- Need to Build a Struct that has:

/*     Parsed Command List      */
typedef struct s_parser
{
	t_list	**sections;
	int		input_fd;
	int		output_fd;
	char	**paths;
	char	**command;
}			t_parser;

3. Module 3:
	- Builtin Commands:
		◦ echo with option -n
		◦ cd with only a relative or absolute path
		◦ pwd with no options
		◦ export with no options
		◦ unset with no options
		◦ env with no options or arguments
		◦ exit with no options

4. Module 4:
	- Executor

5. Module 5:
	- Signal Handling  **Work in Progress**
	Signal Translation:
		- Ctrl + C = SIGINT
		- Ctrl + \ = SIGQUIT
		- Ctrl + D = EOF

	In Parent Process:
		- Ctrl + C = Displays a New Prompt on a New Line
		- Ctrl + \ = Does Nothing
		- Ctrl + D = Exits the Shell
	In Child Process:
		- Ctrl + C = Exits the Child and Goes to Parent
		- Ctrl + \ = Exits the Child and Goes to Parent
		- Ctrl + D = Exits the Child and Goes to Parent

6. Module 6:
	- Terminate: After the Commands are Executed, the Shell executes any Shutdown Commands, Frees up any Memory, and Terminates.


**Compile in Linux**
Run
	sudo apt-get install libreadline-dev
	
And then
	make


**Research:**

1. Shell Introduction: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

2. Write your Own Shell Tutorial: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

3. Write a Shell in C Tutorial: https://brennan.io/2015/01/16/write-a-shell-in-c/

4. Mini-Guide for Minishell: https://harm-smits.github.io/42docs/projects/minishell

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

	<stdio.h>
 	- printf

	<stdlib.h>
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


	<signal.h>:
 	- signal
 	- sigaction
 	- sigemptyset -> not used
 	- sigaddset -> not used
 	- kill


 	- exit
 	- getcwd
 	- chdir

	<sys/stat.h> : https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html
 	- stat
 	- lstat
 	- fstat


 	- unlink
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

1. Test out the Shell in order to Learn about Character Behaviour  **DONE**

2. Find out from Daniel how to Push to the Same Repo  **DONE**
	- Best Solution that will Help us in a Normal Flow in a Compay as well is to Branch, Pull and then Merge
	- Workaround would be to Git Add only one File at a Time and we Would have to Work on Separate Files (I guess it's a Waste of Time and we Don't Learn Anything)

3. Check out the Repos that have Completed Strictly what is Demanded  **DONE**

4. Install the Latest Version of Readline() on the Schools Imacs and Using it rather than the Old One: https://github.com/c8p2d01/minishell_42_WOB_fix **DONE**


**Git Professional WorkFlow"**

1. Create 3 Branches
	- Main Branch
	- Saskia's Branch
	- Valentin's Branch

	Commands to Create Branch:
		- git branch "name" = to Create the Branch
		- git checkout "name"  = To Switch to Branch
		- git add .  = to Add All your Files
		- git commit -m "message"  = to Commit Files
		- git push --set-upstream origin name  = To Push, Just the First Time !!
		- git push

2. Work in Own Branch and Merge

3. how-to-clone-a-specific-branch
https://www.freecodecamp.org/news/git-clone-branch-how-to-clone-a-specific-branch/



**Temporary WorkSpace:**

Pseude Code:

if (var == PIPE)
if (var == 23)

return(something)


Linked Lists Functions from GeektoGeek:
https://www.geeksforgeeks.org/write-a-function-to-delete-a-linked-list/


![alt text](https://github.com/garadraw/minishell/blob/Siramis/Minishell_Edge_Case_1_and_2.jpg?raw=true)

![alt text](https://github.com/garadraw/minishell/blob/Siramis/Minishell_Edge_Case_3.jpg?raw=true)

![alt text](https://github.com/garadraw/minishell/blob/Siramis/Minishell_Edge_Case_4.jpg?raw=true)
