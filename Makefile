all: det prob

test: test_det test_prob

det: greedy_det.cpp
	g++ $^ -o det.out

prob: greedy_prob.cpp
	g++ $^ -o prob.out

test_det: det |
	./test_det.sh

test_prob: prob |
	./test_prob.sh
