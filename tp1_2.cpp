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
}

bool verificaQuadradosX(int **entrada,int **saida, int c, int l, int py, int px)
{
	int quadrados = 0, nX=0;
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
				{
					quadrados++;
					if(saida[py+i][px+j] == 0)
						nX++;
				}
	return nX > (quadrados - entrada[py][px]);
}

bool verificaQuadradosPintados(int **entrada,int **saida, int c, int l, int py, int px)
{
	int quadrados = 0;
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] == 1)
						quadrados++;

	return quadrados > entrada[py][px];
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

	return quadrados ;
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
	//preenche os quadrados de preto
	for(int i = -1; i <=1;i++)
		if((py+i >= 0) && (py+i < l))
			for(int j = -1; j <= 1; j++)
				if((px+j >= 0) && (px +j < c))
					if(saida[py+i][px+j] != 0)//onde tem X não pode pintar de preto
						saida[py+i][px+j] = 1;
}


void preencheX(int **entrada,int **saida, int c,int l, int py, int px)
{
	//preenchendo os ponto
	for(int y = 0; y <= py; y++)
		for(int x = 0; x <= px; x++)
		{
			if(entrada[y][x]>0)
			{
				if(numQuadradosPintados(saida,c,l,py,px) == entrada[y][x])
					for(int i = -1; i <=1;i++)
						if((py+i >= 0) && (py+i < l))
							for(int j = -1; j <= 1; j++)
								if((px+j >= 0) && (px +j < c))
									if(saida[py+i][px+j] != 1)
										saida[py+i][px+j] = 0;
				
			}
		}
}

bool valida(int **entrada, int **saida, int c, int l, int py, int px)
{
	bool verificaPintados, verificaX = 0;
	
}


void sol_fill_a_pix(int **entrada, int **saida, int c, int l, int posPreencher)
{
	if(posPreencher == c * l) //imagem já foi preenchida
	{
		//valida a imagem gerada
		for(int y = 0; y < l; y++)
			for(int x = 0; x < c; x++)
				if(!valida(entrada,saida,c,l,y,x))
					return;		
			
		printImagem(saida,c,l); //se for valida, imprime
		return;
	}

	int py = posPreencher / l;
	int px = posPreencher % c;

	if(entrada[py][px] <=0)
	{	
		if(entrada[py][px] == 0)
		{
			for(int i = -1; i <=1;i++)
				if((py+i >= 0) && (py+i < l))
					for(int j = -1; j <= 1; j++)
						if((px+j >= 0) && (px +j < c))
							saida[py + i][px + j] = 0;

			sol_fill_a_pix(entrada,saida,c,l,posPreencher + 2);
		}
		else
			sol_fill_a_pix(entrada,saida,c,l,posPreencher + 1);
	}
	else
	{
		for(int i = -1; i <=1;i++)
			if((py+i >= 0) && (py+i < l))
				for(int j = -1; j <= 1; j++)
					if((px+j >= 0) && (px +j < c))
					{
						if(saida[py + i][px + j] == -1)
							saida[py + i][px + j] = 1;
						preencheX(entrada,saida,c,l,py,px);
						if(valida(entrada,saida,c,l,py,px))
							sol_fill_a_pix(entrada,saida,c,l,posPreencher + 1);
						saida[py + i][px + j] = 0;
					}
	}
		
	return;

}

void fill_a_pix(int **entrada, int **saida, int c, int l)
{
	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)	
		{
			if(entrada[y][x] == 0)
				preencheX(entrada,saida,c,l,y,x);
			if(entrada[y][x] > 0)
				if(entrada[y][x] == numQuadradosSemX(saida,c,l,y,x))
					preenchePreto(saida,c,l,y,x);
		}
	
	sol_fill_a_pix(entrada,saida,c,l,0);

	printImagem(saida,c,l);

}

int main()
{
	int c,l;
	cin >> c >> l; //m = nº de colunas e n = nº de linhass

	int **entrada = new int *[l]; //matriz que recebe o jogo
	int **saida = new int *[l]; //matriz que recebe a imagem final

	//aloca-se mais duas linhas e duas colunas para preencher de zeros as bordas
	//isso facilita a comparação dos quadrados
	for(int i = 0; i < l; i++)
	{
		entrada[i] = new int[c];
		saida[i] = new int[c];
	}

	//preenchendo as matrizes com -1, inclusive as bordas
	for(int i = 0; i < l ; i++)
		for(int j = 0; j < c ; j++)
		{
			saida[i][j] = -1;
		}

	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
		{
			cin >> entrada[y][x];
		}

	fill_a_pix(entrada,saida,c,l);

	return 0;
}
