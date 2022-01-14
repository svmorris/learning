#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <thread>
#include <future>

using std::string;
using std::cout;
//using std::thread;
//using st?d::future;
//using std::async;

string cInput(string prompt="",string mode="normal");

int main() {
	
	// initialize ncurses
	initscr();
	cbreak();
	noecho();
	
	// get return of cInput
	// async(fun,arg) should work
	std::future<string> fut = std::async(std::launch::async, cInput,"", "hey: ");
	string ret = fut.get();
	
	// print return
	move(0,0);
	refresh();
	cout << ret << std::endl;
	
	// give time to see return
	getch();

	// exit curses
	endwin();

	return 0;

}

string cInput(string prompt,string mode) {
	// get terminal dimensions
	int tWidth,tHeight;
	getmaxyx(stdscr,tHeight,tWidth);
	
	// set up variables
	bool keepgoing=true;
	string current="";
	
	while (keepgoing) {
		// get key
		int c;
		c = getch();

		// in debug mode show key code
		if (mode == "debug") {
			current = std::to_string(c);
		}
		
		// otherwise do whatever
		else {
			switch(c) {	
				// backspace
				case 127: {
					current.pop_back();
					break;
				}

				// enter
				case 10: {
					keepgoing = false;
					break;
				}

				// anything else
				default: {
					current += char(c);
				}

			}
		}
		
		// print to location
		mvprintw(tHeight-2,0,"%s",(prompt+current).c_str());
		
		// clr to end of line
		clrtoeol();
	}

	return current;

}
