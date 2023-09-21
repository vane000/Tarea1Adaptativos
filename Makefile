all: det prob

test: test_det test_prob

det: greedy_det.cpp
	g++ $^ -o det.out

prob: greedy_prob.cpp
	g++ $^ -o prob.out

test_det: det.out
	./test_det.sh