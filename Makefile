test: webserver
	./webserver 8080

webserver: webserver1.cpp
	g++ webserver1.cpp -o $@

clean: 
	rm -f webserver