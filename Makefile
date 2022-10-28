all: DIS_ASM/DIS_ASM.cpp DIS_ASM/main.cpp ASM/ASM.cpp ASM/common.cpp ASM/main.cpp CPU/CPU.cpp CPU/main.cpp FileProcessing/FileProcessing.cpp Stack/stack_common.cpp Stack/stack.cpp
	g++ ASM/ASM.cpp ASM/common.cpp ASM/main.cpp FileProcessing/FileProcessing.cpp -o MY_ASM
	g++ CPU/CPU.cpp CPU/main.cpp FileProcessing/FileProcessing.cpp Stack/stack_common.cpp Stack/stack.cpp -o MY_CPU
	g++ DIS_ASM/DIS_ASM.cpp DIS_ASM/main.cpp FileProcessing/FileProcessing.cpp -o MY_DIS_ASM

CPU: CPU/CPU.cpp CPU/main.cpp FileProcessing/FileProcessing.cpp Stack/stack_common.cpp Stack/stack.cpp
	g++ CPU/CPU.cpp CPU/main.cpp FileProcessing/FileProcessing.cpp Stack/stack_common.cpp Stack/stack.cpp -o MY_CPU

ASM: ASM/ASM.cpp ASM/common.cpp ASM/main.cpp FileProcessing/FileProcessing.cpp
	g++ ASM/ASM.cpp ASM/common.cpp ASM/main.cpp FileProcessing/FileProcessing.cpp -o MY_ASM

DIS_ASM: DIS_ASM/DIS_ASM.cpp DIS_ASM/main.cpp FileProcessing/FileProcessing.cpp -o MY_DIS_ASM
	g++ DIS_ASM/DIS_ASM.cpp DIS_ASM/main.cpp FileProcessing/FileProcessing.cpp -o MY_DIS_ASM