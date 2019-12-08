CFLAGS = -fPIC -shared  -g
dynamicLoad: dynamicLoad.cpp	 	
	g++ dynamicLoad.cpp -std=c++11 -ldl -g -o dl 

so: so1 so2
so1:soMaker1.cpp
	g++ ${CFLAGS} soMaker1.cpp -o so1.so
so2:soMaker2.cpp
	g++ ${CFLAGS} soMaker2.cpp -o so2.so
clean:
	rm -r -f *.so

