all:
	g++ -O3 -Wall -Werror -lm -o lab1-seq main.cpp

	g++ -O3 -Wall -Werror -lm -floop-parallelize-all -ftree-parallelize-loops=1 main.cpp -o lab1-par-1
	g++ -O3 -Wall -Werror -lm -floop-parallelize-all -ftree-parallelize-loops=10 main.cpp -o lab1-par-10
	g++ -O3 -Wall -Werror -lm -floop-parallelize-all -ftree-parallelize-loops=20 main.cpp -o lab1-par-20
	g++ -O3 -Wall -Werror -lm -floop-parallelize-all -ftree-parallelize-loops=40 main.cpp -o lab1-par-40

install_python_deps:
	pip install pandas matplotlib Jinja2