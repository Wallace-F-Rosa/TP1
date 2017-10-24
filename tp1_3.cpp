#include <iostream>

using namespace std;

void printImagem(int ** imagem, int c, int l)
{
	//imprime a imagem de saida
	cout << "P1"<<endl;
	cout << c<< " " <<l<<endl;
	for(int y = 0 ; y < l; y++)
	{
		for(int x = 0 ; x < c; x++)
			 cout<< imagem[y][x]<< " ";
		cout <<endl;
	}
	cout <<endl;
}

int numQuadradosPintados(int **saida, int c, int l, int py, int px)
{
	int quadrados = 0;
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] == 1)
						quadrados++;

	return quadrados;
}

int numQuadradosSemX(int **saida, int c, int l, int py, int px)
{
	int quadrados = 0;
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 0)
						quadrados++;

	return quadrados;
}

void preenchePreto(int **saida, int c,int l, int py, int px)
{
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 0)
						saida[py+i][px+j] = 1;
}


void preencheX(int **saida, int c,int l, int py, int px)
{
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 1)
						saida[py+i][px+j] = 0;
}

void fill_a_pix(int **entrada, int **saida, int c, int l)
{
	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)	
		{
			if(entrada[y][x] == 0)
				preencheX(saida,c,l,y,x);
			if(entrada[y][x] > 0)
				if(entrada[y][x] == numQuadradosSemX(saida,c,l,y,x))
					preenchePreto(saida,c,l,y,x);
		}	
	bool preencher = true;

	while(preencher)
	{
		preencher = false;
		for(int y = 0; y < l; y++)
			for(int x = 0; x < c; x++)	
			{
				if(saida[y][x] == -1)
					preencher = true;

				if(entrada[y][x] > 0)
				{
					if(entrada[y][x] == numQuadradosSemX(saida,c,l,y,x))
						preenchePreto(saida,c,l,y,x);

					if(numQuadradosPintados(saida,c,l,y,x) == entrada[y][x])
						preencheX(saida,c,l,y,x);
				}
			}
	}
	return;
}

int main()
{
	int c,l;
	cin >> c >> l; //m = nº de colunas e n = nº de linhass

	int **entrada = new int *[l]; //matriz que recebe o jogo
	int **saida = new int *[l]; //matriz que recebe a imagem final
	bool **visitada = new bool*[l];//matriz que grava quais celulas já foram vizitadas

	//aloca-se mais duas linhas e duas colunas para preencher de zeros as bordas
	//isso facilita a comparação dos quadrados
	for(int i = 0; i < l; i++)
	{
		entrada[i] = new int[c];
		saida[i] = new int[c];
		visitada[i] = new bool[c];
	}

	//preenchendo as matrizes com -1, inclusive as bordas
	for(int i = 0; i < l ; i++)
		for(int j = 0; j < c ; j++)
			saida[i][j] = -1;

	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
		{
			cin >> entrada[y][x];
		}

	fill_a_pix(entrada,saida,c,l);

	printImagem(saida,c,l);

	return 0;
}