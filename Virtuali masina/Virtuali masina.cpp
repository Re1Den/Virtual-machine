#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	bool loop = true;
	while (loop)
	{
		unsigned char regs[16] = { 0 };
		char prog_mem[256] = { 0 };
		int EOF_flag = 0;
		int zero_flag = 0;
	
		string txt_name;
		cout << '\n' << "Enter txt input file name: ";
		cin >> txt_name;
		ifstream tin;
		tin.open(txt_name);

		string bin_name;
		cout << '\n' << "Enter bin input file name: ";
		cin >> bin_name;
		ifstream bin;
		bin.open(bin_name, ios_base::in | ios_base::binary);

		ofstream tout("trez.txt");
		system("CLS");

		//ifstream tin("q1_encr.txt");
		//ifstream tin("TekstinisFailas.txt");

		//fstream bin;
		//bin.open("decryptor.bin", ios_base::in | ios_base::binary);
		//bin.open("VM-reiskinys.bin", ios_base::in | ios_base::binary);

		int n = 0;

		while (true)
		{
			bin.read(&prog_mem[n], 1);
			bin.read(&prog_mem[n + 1], 1);
			if (prog_mem[n] == 0x0B)
			{
				n += 2;
				break;
			}
			n += 2;
		}

		int i = 0;
		while (true)
		{
			
			if (prog_mem[i] == 0x01)
			{
				regs[prog_mem[i + 1] & 0x0F] += 1;

				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;

			}
			else if (prog_mem[i] == 0x02)
			{
				regs[prog_mem[i + 1] & 0x0F] -= 1;
				
				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x03)
			{
				regs[prog_mem[i + 1] & 0x0F] = regs[prog_mem[i + 1] >> 4];
			}
			else if (prog_mem[i] == 0x04)
			{
				regs[0] = prog_mem[i + 1];
			}
			else if (prog_mem[i] == 0x05)
			{
				regs[prog_mem[i + 1] & 0x0F] <<= 1; 
				
				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x06)
			{
				regs[prog_mem[i + 1] & 0x0F] >>= 1;

				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x07)
			{
				if (prog_mem[i + 1] > n)
				{
					i = (i + ((unsigned char)prog_mem[i + 1] - (((unsigned char)prog_mem[i + 1] / n) * n)) - n) - 2;
				//      28 + (            230                -        (     (230 / 32)                *32)  - 32) - 2;
					cout << "a";
				}
				else
				{
					i += prog_mem[i + 1] - 2;
				}
			}
			else if (prog_mem[i] == 0x08 && zero_flag == 1)
			{
				if (prog_mem[i + 1] > n)
				{
					i = (i + ((unsigned char)prog_mem[i + 1] - (((unsigned char)prog_mem[i + 1] / n) * n)) - n) - 2;
				}
				else
				{
					i += prog_mem[i + 1] - 2;
				}
			}
			else if (prog_mem[i] == 0x09 && zero_flag == 0)
			{
				if (prog_mem[i + 1] > n)
				{
					i = (i + ((unsigned char)prog_mem[i + 1] - (((unsigned char)prog_mem[i + 1] / n) * n)) - n) - 2;
				}
				else
				{
					i += prog_mem[i + 1] - 2;
				}
			}
			else if (prog_mem[i] == 0x0A && EOF_flag == 1)
			{
				if (prog_mem[i + 1] > n)
				{
					i = (i + ((unsigned char)prog_mem[i + 1] - (((unsigned char)prog_mem[i + 1] / n) * n)) - n) - 2;
				}
				else
				{
					i += prog_mem[i + 1] - 2;
				}
				
			}
			else if (prog_mem[i] == 0x0B)
			{
				break;
			}
			else if (prog_mem[i] == 0x0C)
			{
				regs[prog_mem[i + 1] & 0x0F] += regs[prog_mem[i + 1] >> 4];

				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x0D)
			{
				regs[prog_mem[i + 1] & 0x0F] -= regs[prog_mem[i + 1] >> 4];

				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x0E)
			{
				regs[prog_mem[i + 1] & 0x0F] ^= regs[prog_mem[i + 1] >> 4];

				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x0F)
			{
				regs[prog_mem[i + 1] & 0x0F] |= regs[prog_mem[i + 1] >> 4];

				if (regs[prog_mem[i + 1] & 0x0F] == 0)
					zero_flag == 1;
				else
					zero_flag == 0;
			}
			else if (prog_mem[i] == 0x10)
			{
				tin >> regs[prog_mem[i + 1] & 0x0F];
				if (tin.eof())
					EOF_flag = 1;
			}
			else if (prog_mem[i] == 0x11)
			{
				tout << regs[prog_mem[i + 1] & 0x0F];
			}

			i+=2;
		}

		tin.close();
		tout.close();
		bin.close();

		while (true)
		{
			int opt;
			cout <<"Check trez.txt for answer \n \n \t " << "_OPTIONS_" << '\n' << '\n';
			cout << "(1) |ONE MORE TIME!|" << '\n';
			cout << "(2) |TERMINTATE|" << '\n';
			cin >> opt;
			if (opt == 1)
			{
				system("CLS");
				//remove("trez.txt");
				break;
			}
			else if (opt == 2)
			{
				system("CLS");
				loop = false;
				break;
			}
			else
			{
				system("CLS");
				cout << "Invalid input";
			}

		}

	}

	return 0;
}