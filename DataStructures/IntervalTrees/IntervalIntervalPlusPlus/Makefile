all: IntervalIntervalPlusPlus IntervalIntervalPlusPlus.recursive brute-force gen/genRand train

IntervalIntervalPlusPlus: IntervalIntervalPlusPlus.cpp
	./DbgCompile.sh IntervalIntervalPlusPlus

IntervalIntervalPlusPlus.recursive: IntervalIntervalPlusPlus.recursive.cpp
	./DbgCompile.sh IntervalIntervalPlusPlus.recursive

brute-force: brute-force.cpp
	./DbgCompile.sh brute-force

gen/genRand: gen/genRand.cpp
	./DbgCompile.sh gen/genRand

train: train.cpp
	./DbgCompile.sh train