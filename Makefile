all: det prob

det: greedy_det.cpp
	g++ $^ -o det.out

prob: greedy_prob.cpp
	g++ $^ -o prob.out