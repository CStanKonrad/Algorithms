all: IntervalIntervalPlusMax IntervalIntervalPlusMax.recursive brute-force gen/genRand train

IntervalIntervalPlusMax: IntervalIntervalPlusMax.cpp
	./DbgCompile.sh IntervalIntervalPlusMax
	
IntervalIntervalPlusMax.recursive: IntervalIntervalPlusMax.recursive.cpp
	./DbgCompile.sh IntervalIntervalPlusMax.recursive

brute-force: brute-force.cpp
	./DbgCompile.sh brute-force

gen/genRand: gen/genRand.cpp
	./DbgCompile.sh gen/genRand

train: train.cpp
	./DbgCompile.sh train