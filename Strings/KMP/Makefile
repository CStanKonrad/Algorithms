all: KMP KMP.2 KMP.3 gen/genRand brute-force train

KMP: KMP.cpp
	./DbgCompile.sh KMP

KMP.2: KMP.2.cpp
	./DbgCompile.sh KMP.2
	
KMP.3: KMP.3.cpp
	./DbgCompile.sh KMP.3

brute-force: brute-force.cpp
	./DbgCompile.sh brute-force

gen/genRand: gen/genRand.cpp
	./DbgCompile.sh gen/genRand
	
train: train.cpp
	./DbgCompile.sh train