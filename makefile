CC=g++
CFLAGS=-Wall -pedantic -g

build: obj simEDF-k simGlobalEDF taskGenerator GlobalEDFvsEDF-k

rebuild: clean build

obj:
	mkdir obj

simEDF-k: obj/mainedfk.o obj/stask.o obj/simulator.o obj/helper.o obj/edfktool.o
	$(CC) obj/mainedfk.o obj/stask.o obj/simulator.o obj/helper.o obj/edfktool.o -o simEDF-k $(CFLAGS)

obj/mainedfk.o: src/sim/EDFK/main.cpp src/STask.hpp src/sim/CSimulator.hpp src/sim/SJob.hpp src/sim/EDFK/EDFKTool.hpp
	$(CC) -c src/sim/EDFK/main.cpp -o obj/mainedfk.o $(CFLAGS)

obj/edfktool.o: src/STask.hpp src/sim/helper.hpp src/sim/EDFK/EDFKTool.hpp src/sim/EDFK/EDFKTool.cpp
	$(CC) -c src/sim/EDFK/EDFKTool.cpp -o obj/edfktool.o $(CFLAGS)



simGlobalEDF: obj/mainglobaledf.o obj/stask.o obj/simulator.o obj/helper.o obj/globaledftool.o
	$(CC) obj/mainglobaledf.o obj/stask.o obj/simulator.o obj/helper.o obj/globaledftool.o -o simGlobalEDF $(CFLAGS)

obj/mainglobaledf.o: src/sim/GEDF/main.cpp src/STask.hpp src/sim/CSimulator.hpp src/sim/SJob.hpp src/sim/GEDF/GlobalEDFTool.hpp
	$(CC) -c src/sim/GEDF/main.cpp -o obj/mainglobaledf.o $(CFLAGS)

obj/globaledftool.o: src/STask.hpp src/sim/GEDF/GlobalEDFTool.hpp src/sim/GEDF/GlobalEDFTool.cpp
	$(CC) -c src/sim/GEDF/GlobalEDFTool.cpp -o obj/globaledftool.o $(CFLAGS)



taskGenerator: obj/taskGenerator.o obj/sgenerator.o obj/stask.o
	$(CC) obj/stask.o obj/sgenerator.o obj/taskGenerator.o obj/carganalyzer.o -o taskGenerator $(CFLAGS)

obj/taskGenerator.o: src/generator/main.cpp obj/carganalyzer.o src/STask.hpp
	$(CC) -c src/generator/main.cpp -o obj/taskGenerator.o $(CFLAGS)

obj/carganalyzer.o: src/generator/CArgAnalyzer.hpp src/generator/CArgAnalyzer.cpp
	$(CC) -c src/generator/CArgAnalyzer.cpp -o obj/carganalyzer.o $(CFLAGS)

obj/sgenerator.o: src/generator/SGenerator.cpp src/generator/SGenerator.hpp src/STask.hpp
	$(CC) -c src/generator/SGenerator.cpp -o obj/sgenerator.o $(CFLAGS)


GlobalEDFvsEDF-k: obj/maingedfvsedf-k.o obj/gedfvsedf-kcarganalyzer.o obj/sgenerator.o obj/edfktool.o obj/globaledftool.o obj/helper.o obj/simulator.o obj/stask.o obj/statistic.o
	$(CC) obj/maingedfvsedf-k.o obj/gedfvsedf-kcarganalyzer.o obj/sgenerator.o obj/edfktool.o obj/globaledftool.o obj/helper.o obj/simulator.o obj/stask.o obj/statistic.o -o GlobalEDFvsEDF-k $(CFLAGS)

obj/maingedfvsedf-k.o: src/sim/CMP/SStatistic.hpp src/sim/CMP/main.cpp src/sim/CMP/CArgAnalyzer.hpp src/STask.hpp src/sim/GEDF/GlobalEDFTool.hpp src/sim/helper.hpp src/sim/EDFK/EDFKTool.hpp src/generator/SGenerator.hpp src/sim/CSimulator.hpp
	$(CC) -c src/sim/CMP/main.cpp -o obj/maingedfvsedf-k.o $(CFLAGS)

obj/gedfvsedf-kcarganalyzer.o: src/sim/CMP/CArgAnalyzer.hpp src/sim/CMP/CArgAnalyzer.cpp
	$(CC) -c src/sim/CMP/CArgAnalyzer.cpp -o obj/gedfvsedf-kcarganalyzer.o $(CFLAGS)

obj/statistic.o: src/sim/CMP/SStatistic.hpp src/sim/CSimulator.hpp
	$(CC) -c src/sim/CMP/SStatistic.cpp -o obj/statistic.o $(CFLAGS)
	


obj/stask.o: src/STask.cpp src/STask.hpp
	$(CC) -c src/STask.cpp -o obj/stask.o $(CFLAGS)

obj/simulator.o: src/sim/CSimulator.cpp src/sim/CSimulator.hpp src/STask.hpp src/sim/SJob.hpp src/sim/helper.hpp src/sim/SProc.hpp
	$(CC) -c src/sim/CSimulator.cpp -o obj/simulator.o $(CFLAGS)

obj/helper.o: src/sim/SJob.hpp src/STask.hpp src/sim/helper.cpp src/sim/helper.hpp src/sim/SProc.hpp
	$(CC) -c src/sim/helper.cpp -o obj/helper.o $(CFLAGS)


clean:
	rm -fr obj
	rm simEDF-k simGlobalEDF taskGenerator GlobalEDFvsEDF-k
