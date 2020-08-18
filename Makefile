all: search-shell

search-shell: combiners.cpp search-shell.cpp md_parser.o util.o webpage.o cmdhandler.o handler.o searcheng.o searchui.o txt_parser.o
	g++ -g -Wall -std=c++11 combiners.cpp search-shell.cpp md_parser.o util.o webpage.o cmdhandler.o handler.o searcheng.o searchui.o txt_parser.o -o search-shell

md_parser.o: util.h md_parser.h md_parser.cpp
	g++ -g -Wall -c -std=c++11 md_parser.cpp -o md_parser.o

util.o: util.h util.cpp webpage.h
	g++ -g -Wall -c -std=c++11 util.cpp -o util.o

webpage.o: webpage.h webpage.cpp util.h
	g++ -g -Wall -c -std=c++11 webpage.cpp -o webpage.o

cmdhandler.o: cmdhandler.h util.h handler.h searcheng.h cmdhandler.cpp
	g++ -g -Wall -c -std=c++11 cmdhandler.cpp -o cmdhandler.o

handler.o: handler.cpp handler.h searcheng.h
	g++ -g -Wall -c -std=c++11 handler.cpp -o handler.o

searcheng.o: searcheng.cpp searcheng.h webpage.h pageparser.h
	g++ -g -Wall -c -std=c++11 searcheng.cpp -o searcheng.o

searchui.o: searchui.cpp searchui.h util.h
	g++ -g -Wall -c -std=c++11 searchui.cpp -o searchui.o

txt_parser.o: txt_parser.cpp txt_parser.h util.h 
	g++ -g -Wall -c -std=c++11 txt_parser.cpp -o txt_parser.o



clean:
	rm -f search-shell *.o 