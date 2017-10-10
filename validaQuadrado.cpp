#include <iostream>

using namespace std;

int main()
{
	int quadrado[3][3];

	for(int y = 0; y < 3; y++)
		for(int x = 0; x < 3; x++)
		 quadrado[y][x] = 3;

	for(int y = 0; y < 3; y++)
		for(int x = 0; x < 3; x++)
		{
			int conta = 0;
			for(int i = -1; i <=1;i++)
			{
				if((y+i >= 0) && (y+i < 3))
				{
					for(int j = -1; j <= 1; j++)
						if((x+j >= 0) && (x +j < 3))
							if(quadrado[y+i][x+j]==3)
								conta++;
				}
			}

			cout<<"Qtd de 3 envolta da posição ("<<y<<","<<x<<") : "<<conta<<endl;
		}

	return 0;


}
