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

bool verificaQuadradosPintados(int **entrada,int **saida, int c, int l, int py, int px)
{
	/*Função que verifica se o número de quadrados preenchido (quadrados com 1) é maior que o permitido*/
	int preto = 0;
	if(entrada[py][px]>=0)
		for(int i = -1; i <=1;i++)
			if((py+i >= 0) && (py+i < l))
				for(int j = -1; j <= 1; j++)
					if((px+j >= 0) && (px +j < c))
						if(saida[py+i][px+j] == 1)//se o quadrado estiver pintado
							preto++;//adiciona ele ao contador
	else
		return true;
	
	//retorna false se quadrados pintados for maior que o permitido retorna true
	//se não retorna true;

	if(preto > entrada[py][px])
		return false;
	else
		return true;
}

bool verificaQuadradosX(int ** entrada,int **saida, int c, int l, int py, int px)
{

	/*Função que verifica se o número de X's (quadrados com 0) é maior que o permitido*/
	int quadrados = 0,X = 0;
	if(entrada[py][px] >= 0)
		for(int i = -1; i <=1;i++)
			if((py+i >= 0) && (py+i < l))
				for(int j = -1; j <= 1; j++)
					if((px+j >= 0) && (px +j < c))
					{
						quadrados++;
						if(saida[py+i][px+j] == 0) //se o quadrado não estiver com X (=0))
							X++;//adiciona ele ao contador
					}
	else
		return true;
	
				
	//retorna false se o número de quadrados pintados for maior que o permitido retorna true
	//se não retorna false;

	if(X > (quadrados - entrada[py][px]))
		return false;
	else
		return true;

}

bool verificaSaida(int ** entrada,int **saida, int c, int l,int py, int px)
{

	for(int y = 0; y <= py; y++)
		for(int x = 0; x <= px; x++)
		{
			if(verificaQuadradosPintados(entrada,saida,c,l,y,x)) //verificaQuadradosX(entrada,saida,c,l,y,x))
				return false;
		}

	return true;
}


void fill_a_pix(int **entrada, int **saida, int c, int l, int posPreencher)
{
	if(posPreencher == c * l)//preencheu todas as posições
	{	
		if(verificaSaida(entrada,saida,c,l,l-1,c-1))//se for válida imprime
		{	
			printImagem(saida,c,l);//imprime imagem
			return;
		}
		return;
	}
	
	int py = posPreencher / l;//posição y
	int px = posPreencher % c;//posição x


	saida[py][px] = 1;
	if(verificaQuadradosPintados(entrada,saida,c,l,py,px)) // verifica se o número de quadrados pintados excede o permitido
		fill_a_pix(entrada,saida,c,l,posPreencher+1);//se não continua a preencher
	else
	{
		saida[py][px] = 0;
		//printImagem(saida,c,l);
		if(verificaQuadradosX(entrada,saida,c,l,py,px))// verifica se o número de quadrados com X excede o permitido
			fill_a_pix(entrada,saida,c,l,posPreencher+1);//se não continua o processo
		else
			return;
	}

	
}

int main()
{
	int c,l;
	cin >> c >> l; //m = nº de colunas e n = nº de linhass

	int **entrada = new int *[l]; //matriz que recebe o jogo
	int **saida = new int *[l]; //matriz que recebe a imagem final

	for(int i = 0; i < l; i++)
	{
		entrada[i] = new int[c];
		saida[i] = new int[c];
	}

	//preenchendo as matrizes com -1, inclusive as bordas
	for(int i = 0; i < l; i++)
		for(int j = 0; j < c; j++)
			saida[i][j] = -1;

	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
			cin >> entrada[y][x];

	
	fill_a_pix(entrada,saida,c,l,0);


	return 0;
}
