all: MonotoneChain gen/genRand train 

MonotoneChain: MonotoneChain.cpp
	./DbgCompile.sh MonotoneChain

gen/genRand: gen/genRand.cpp
	./DbgCompile.sh gen/genRand
	
train: train.cpp
	./DbgCompile.sh train