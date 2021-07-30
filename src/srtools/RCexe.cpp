#include <stdio.h>
#include <iostream>
#include <fstream>
#include "timers/hr_time.h"
#include "triangulations/RobustCrust.h"

#include <stdint.h>
#include "util/shell_io.h"


using namespace std;

//char for the header
char algoname[256] = "Robust Crust";
char version[256] = "v0.2";
char author[256] = "Luigi Giaccari";
char user[256] = "WhoEver";

double* ptemp; //points coordinates as imported from file manager
int N;//number of points
vector<double> p;
int main(int argc, char* argv[])
{
	//std::ifstream ifs("car1.dat");
	//std::ofstream("car1.dat", std::ios::binary) << ifs.rdbuf();
	////return 0;

	//FILE *stream;
	//char list[30];
	//int i, numread, numwritten;
	//// 以文本方式打开文件
	//if ((stream = fopen("fread.out", "w+t")) != NULL)  // 如果读取无误
	//{
	//	for (i = 0; i < 25; i++)
	//		list[i] = (char)('z' - i);
	//	numwritten = fwrite(list, sizeof(char), 25, stream);
	//	printf("Wrote %d items\n", numwritten);
	//	fclose(stream);
	//}
	//else
	//{
	//	printf("Problem opening the file\n");
	//}
	//if ((stream = fopen("fread.out", "r+t")) != NULL)  // 文件读取
	//{
	//	numread = fread(list, sizeof(char), 21, stream);
	//	printf("Number of items read = %d\n", numread);
	//	printf("Contents of buffer = %.25s\n", list);
	//	fclose(stream);
	//}
	//else
	//{
	//	printf("File could not be opened\n");
	//}



	int flag;

	CStopWatch Timer;

	RCRUST Surface;//Power Crust class
	PrintHeader(algoname, version, author, user);


	cout << endl << "PROGRAM STARTED!" << endl;


	if (argc > 1) //read input when provided
	{
		cout << "Reading input!" << endl;
		ReadInputs(argc, argv);
	}
	else//otherwise asks for inputs/output
	{
		AskForInputs();
	}

	cout << "Importing points...";
	FileManager.Read_Points(&ptemp, &N, inputfile);

	p.resize(N * 3);
	Copy(&p[0], &ptemp[0], N * 3);
	Deallocate(&ptemp);


	cout << N << " Points imported" << endl;
	Timer.startTimer();
	if (N < 4)
	{
		Error("Not enough points to launch the algorithm");
	}

	cout << endl << "LAUNCHING MyRobustCrust" << endl;
	Surface.TriangulatePowerCrust(&p, N);
	//Surface.TriangulateABPA(&p, N);
	//Surface.TriangulateSpectral(&p, N);


	int nt = Surface.t.size();

	Timer.stopTimer();
	cout << "Total Time: " << Timer.getElapsedTime() / 1000 << " s" << endl;


	cout << endl << "OUTPUT!" << endl;
	//cout << "Writing stl file...";
	//FileManager.Write_stl(&p[0], &Surface.t[0].p1, nt, outputfile);

#if 0 
	{
		cout << "Writing matlab file...";
		FileManager.Write_m(&p[0], N, &Surface.t[0].p1, nt, outputfile);
	}
#else
	{
		cout << "Writing obj file...";
		FileManager.Write_obj(&p[0], N, &Surface.t[0].p1, nt, outputfile);
	}
#endif	

	

    cout << "Done" << endl;


    //if(ShowSurface){
    //     cout<<endl<<"PROGRAM ENDED!"<<endl<<endl;
    //    VIEWER::StartViewer(p,N,&Surface.t[0].p1,nt);
    //    }
    //memory deallocation
    Surface.FreeMemory();


    cout << endl << "PROGRAM ENDED!" << endl << endl;
    cout << endl << "UNMESHABLE IS NOTHING!" << endl << endl;

    ExitProgram(0);
}
