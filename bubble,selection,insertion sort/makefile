all: test

test: Stress_ball.o Collection-test.o Jeans.o Stress_ball_test.o Jeans_test.o
	g++ -std=c++11 -Wall -g Stress_ball.o Collection-test.o Jeans.o Stress_ball_test.o Jeans_test.o -o test

Stress_ball.o: Stress_ball.cpp Stress_ball.h
	g++ -std=c++11 -c -g Stress_ball.cpp

Collection-test.o: Collection-test.cpp Collection.h
	g++ -std=c++11 -c -g Collection-test.cpp

Jeans.o: Jeans.cpp Jeans.h
	g++ -std=c++11 -c -g Jeans.cpp

Stress_ball_test.o: Stress_ball_test.cpp
	g++ -std=c++11 -c -g Stress_ball_test.cpp

Jeans_test.o: Jeans_test.cpp
	g++ -std=c++11 -c -g Jeans_test.cpp

clean:
	rm -f *.o test

run: test
	./test