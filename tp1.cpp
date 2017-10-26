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
	if(entrada[py][px] >= 0)
		for(int i = -1; i <=1;i++)
			if((py+i >= 0) && (py+i < l))
				for(int j = -1; j <= 1; j++)
					if((px+j >= 0) && (px +j < c))
						if(saida[py+i][px+j] == 1)//se o quadrado estiver pintado
							preto++;//adiciona ele ao contador
	else
		return true; // quadrado não possui informação útil
					

	//retorna false se quadrados pintados for maior que o permitido retorna true
	//se não retorna true;
	if(preto > entrada[py][px])
		return false;
	else
		true;
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
		return true; // quadrado não possui informação útil
				
	//retorna false se o número de quadrados pintados for maior que o permitido retorna true
	//se não retorna false;
	if(X > (quadrados - entrada[py][px]))
		return false;
	else
		true;
}

bool verificaSaida(int ** entrada,int **saida, int c, int l, int py, int px)
{
	//verifica a saida do programa
	for(int y = 0; y <= py; y++)
		for(int x = 0; x <= px; x++)
		{
			if(entrada[y][x] >= 0)
				if(!verificaQuadradosPintados(entrada,saida,c,l,y,x) || !verificaQuadradosX(entrada,saida,c,l,y,x))
					return false;
		}

	return true;
}


void fill_a_pix(int **entrada, int **saida, int c, int l, int posPreencher)
{
	if(posPreencher == c * l)
	{
		int py = l - 1;
		int px = c - 1;
		if(!verificaSaida(entrada,saida,c,l,py,px))	
			return;
		
		return;
	}

	int py = posPreencher / l; // posição y
	int px = posPreencher % c; //posição x

	saida[py][px] = 1; // preenche a posição 
	if(verificaQuadradosPintados(entrada,saida,c,l,py,px)) // verifica se é valido
		fill_a_pix(entrada,saida,c,l,posPreencher+1);//continua
	else//se não
	{
		saida[py][px] = 0;//tenta preencher com X
		if(verificaQuadradosX(entrada,saida,c,l,py,px)) // verifica se o n de X marcado é permitido
			fill_a_pix(entrada,saida,c,l,posPreencher+1);
		//se não, backtrack, a função termina o escopo e o programa volta pra chamada anterior 	
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
	for(int i = 0; i < l; i++)
		for(int j = 0; j < c; j++)
			saida[i][j] = -1;

	for(int y = 0; y < l; y++)
		for(int x = 0; x < c; x++)
			cin >> entrada[y][x];

	clock_t t0 = clock();
	fill_a_pix(entrada,saida,c,l,0);
	cerr << "Tempo de resolução do problema (ms): " << ((clock()-t0)*1.0/CLOCKS_PER_SEC)*1000 << endl;
	printImagem(saida,c,l);
	for(int i = 0; i < l; i++)
	{
		delete [] entrada[c];
		delete [] saida[c];
	}

	delete [] entrada;
	delete [] saida;
	cerr << "Tempo total de execução (ms): " << ((clock()-t0)*1.0/CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}
