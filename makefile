CFLAGS = -fPIC -shared  -g
dynamicLoad: dynamicLoad.cpp	 	
	g++ dynamicLoad.cpp -std=c++11 -ldl -g -o dl 

so: add mul
add:soMaker1.cpp
	g++ ${CFLAGS} soMaker1.cpp -o add.so
mul:soMaker2.cpp
	g++ ${CFLAGS} soMaker2.cpp -o mul.so

login:soLogin.cpp
	g++ ${CFLAGS} soLogin.cpp -o login.so
clean:
	rm -r -f *.so

