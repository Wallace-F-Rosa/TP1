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


bool validaZero(int **entrada, int **saida, int c, int l, int py, int px)
{
	if(py > 0 && px > 0)
		for(int y = 0; y < py; y++)
			for(int x = 0; x < px; x++)
			{
				if(entrada[y][x] >= 0)
				{
					int conta = 0;
					for(int i = -1; i <=1;i++)
						if((y+i >= 0) && (y+i < l))
							for(int j = -1; j <= 1; j++)
								if((x+j >= 0) && (x +j < c))
									if(saida[y+i][x+j]==0)
										conta++;

					if(conta > 9-entrada[y][x])
						return false;
				}
			}

	return true;
	

}

bool validaQuadrados(int **entrada, int **saida, int c, int l)
{
	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
		{
			if(entrada[y][x] >= 0)
			{
				int conta = 0;
				for(int i = -1; i <=1;i++)
					if((y+i >= 0) && (y+i < l))
						for(int j = -1; j <= 1; j++)
							if((x+j >= 0) && (x +j < c))
								if(saida[y+i][x+j]==1)
									conta++;

				if(conta > entrada[y][x])
					return false;
			}
		}
	return true;
}

void fill0e9(int **entrada, int **saida, int c, int l)
{
	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
		{
			if(entrada[y][x] == 0)
			{
				for(int i = -1; i <=1;i++)
					if((y+i >= 0) && (y+i < l))
						for(int j = -1; j <= 1; j++)
							if((x+j >= 0) && (x +j < c))
								saida[y+i][x+j]=0;
			}
			if(entrada[y][x] == 9)
			{
				for(int i = -1; i <=1;i++)
					if((y+i >= 0) && (y+i < l))
						for(int j = -1; j <= 1; j++)
							if((x+j >= 0) && (x +j < c))
								saida[y+i][x+j]=1;
			}
		}

}

bool valida(int **entrada, int **saida, int c, int l, int py, int px)
{
	return validaQuadrados(entrada,saida,c,l) && validaZero(entrada,saida,c,l,py,px);
}

void fill_a_pix(int **entrada, int **saida, int c, int l, int posPreencher)
{
	if(posPreencher >= c * l) //imagem já foi preenchida
	{
		//valida a imagem gerada
		if(validaQuadrados(entrada,saida,c,l))
			printImagem(saida,c,l); //se for valida, imprime
		return;
	}

	int py = posPreencher / l;
	int px = posPreencher % l;

	if(entrada[py][px] <= 0 || saida[py][px] == 1) //posição já veio preenchida
	{
		if(entrada[py][px] == 0)
		{
			for(int i = -1; i <=1;i++)
					if((py+i >= 0) && (py+i < l))
						for(int j = -1; j <= 1; j++)
							if((px+j >= 0) && (px +j < c))
								saida[py+i][px+j]=0;

			fill_a_pix(entrada,saida,c,l,posPreencher+2);
		}
		else
			fill_a_pix(entrada,saida,c,l,posPreencher+1);
		
	}
	else
	{
	
		for(int i = -1; i <=1;i++)
			if((py+i >= 0) && (py+i < l))
				for(int j = -1; j <= 1; j++)
					if((px+j >= 0) && (px +j < c))
					{
						if(saida[py+i][px+j] != 1)
						{
							saida[py+i][px+j] = 1;
							printImagem(saida,c,l);
							if(valida(entrada,saida,c,l,py,px))
								fill_a_pix(entrada,saida,c,l,posPreencher + 1);
						}								
						saida[py+i][px+j] = 0;
								
						if(valida(entrada,saida,c,l,py,px))
							fill_a_pix(entrada,saida,c,l,posPreencher + 1);
						else
							return;
								
							
					}
			
	}


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
			entrada[i][j] = -1;
			saida[i][j] = 0;
		}

	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
		{
			cin >> entrada[y][x];
		}

	cout << "Entrada :" <<endl;
	for(int y = 0; y < l; y++)
	{
		for(int x = 0; x < c; x++)
			cout << entrada[y][x] << " ";
		cout<<endl;
	}
	cout << endl;

	fill0e9(entrada,saida,c,l);
	fill_a_pix(entrada,saida,c,l,0);

	return 0;
}
